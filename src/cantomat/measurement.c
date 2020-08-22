/*  measurement.c -- process CAN trace file
    Copyright (C) 2007-2020 Andreas Heitmann

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include "cantools_config.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>
#include <libgen.h> /* basename() */

#include "measurement.h"
#include "busassignment.h"
#include "messagehash.h"
#include "signalformat.h"
#include "hashtable.h"
#include "hashtable_itr.h"
#include "ascreader.h"
#include "messagedecoder.h"
#include "vsbreader.h"
#include "dbcmodel.h"

/* callback structure for timeSeries signal handler */
typedef struct {
  struct hashtable *timeSeriesHash;
  char             *local_prefix;
} signalProcCbData_t;

/* callback structure for timeSeries message handler */
typedef struct {
  busAssignment_t *busAssignment;
  measurement_t   *measurement;
  signalFormat_t   signalFormat;
  sint32           timeResolution;
} messageProcCbData_t;

/* simple string hash function for signal names */
static unsigned int signalName_computeHash(void *k)
{
  uint8_t *cp;
  unsigned int hash = 0;
  int c;

  for(cp = k; (c = *cp) != '\0'; cp++) {
    hash = c + (hash << 6) + (hash << 16) - hash;
  }

  return hash;
}

/* string comparison function for signal names */
static int signalNames_equal ( void *key1, void *key2 )
{
  return strcmp((char *)key1, (char *)key2) == 0;
}

/* used only for debugging: print data to stderr */
static void signalProc_print(
  const signal_t *s,
  const canMessage_t *canMessage,
  uint32_t rawValue,
  double physicalValue,
  void *cbData)
{
  /* recover callback data */
  signalProcCbData_t *signalProcCbData = (signalProcCbData_t *)cbData;
  char *outputSignalName =
    signalFormat_stringAppend(signalProcCbData->local_prefix, s->name);
  
  fprintf(stderr,"   %s\t=%f ~ raw=%" PRIu32 "\t~ %d|%d@%d%c (%f,%f)"
          " [%f|%f] %" PRIu32 " %" PRIu32 " \"%s\"\n",
          outputSignalName,
          physicalValue,
          rawValue,
          s->bit_start,
          s->bit_len,
          s->endianess,
          s->signedness?'-':'+',
          s->scale,
          s->offset,
          s->min,
          s->max,
          s->mux_type,
          s->mux_value,
          s->comment!=NULL?s->comment:"");

  /* free temp. signal name */
  if(outputSignalName != NULL) free(outputSignalName);
}

/*
 * Add signal value to time series array
 *
 * For large measurements, this code should eventually be replaced by
 * a file based storage.
 */
static void signalProc_timeSeries(
  const signal_t *s,
  double          dtime,
  uint32          rawValue,
  double          physicalValue,
  void           *cbData)
{
  /*
   * realloc strategy:
   *
   * reallocate in 1kByte (128*sizeof(double)) blocks.
   *
   * Increasing realloc step size improves performance only marginally
   * (tested on x86-32), but increases memory waste.
   *
   * realloc_count must be a power of 2.
   */
  const unsigned int realloc_count = (1u<<7u);

  /* recover callback data */
  signalProcCbData_t *signalProcCbData = (signalProcCbData_t *)cbData;

  /* assemble final signal name */
  char *outputSignalName = 
    signalFormat_stringAppend(signalProcCbData->local_prefix, s->name);
  
  /* look for signal in time series hash */
  timeSeries_t *timeSeries = hashtable_search(signalProcCbData->timeSeriesHash,
                                              (void *)outputSignalName);

  /* allocate new time series structure on first value */
  if(NULL == timeSeries) {
    timeSeries = (timeSeries_t *)malloc(sizeof(*timeSeries));
    timeSeries->n = 0;
    timeSeries->time = NULL;
    timeSeries->value = NULL;
    hashtable_insert(signalProcCbData->timeSeriesHash,
                     (void *)strdup(outputSignalName),
                     (void *)timeSeries);
  }

  /* perform reallocation if allocated buffer would be exceeded */
  if((timeSeries->n & (realloc_count-1)) == 0) {
    unsigned int newsize = (timeSeries->n & ~(realloc_count-1)) + realloc_count;
    timeSeries->time  = realloc(timeSeries->time, sizeof(double)*newsize);
    timeSeries->value = realloc(timeSeries->value, sizeof(double)*newsize);
  }

  /* append entry to time series */
  timeSeries->time [timeSeries->n] = dtime;
  timeSeries->value[timeSeries->n] = physicalValue;
  timeSeries->n++;

  /* free temp. signal name */
  if(outputSignalName != NULL) free(outputSignalName);
}

/*
 * callback function for processing a CAN message
 */
static void
canMessage_process(canMessage_t *canMessage, void *cbData)
{
  messageProcCbData_t *messageProcCbData = (messageProcCbData_t *)cbData;

  /* lookup canMessage in message hash */
  messageHashKey_t key = canMessage->id;
  message_t *dbcMessage;
  int i;

  /* loop over all bus assigments */
  for(i = 0; i < messageProcCbData->busAssignment->n ; i++) {
    busAssignmentEntry_t *entry = &messageProcCbData->busAssignment->list[i];

    /* check if bus matches */
    if((entry->bus == -1) || (entry->bus == canMessage->bus)) {
      if(NULL != (dbcMessage = hashtable_search(entry->messageHash, &key))) {

        /* found the message in the database */
        char *prefix = NULL;
        
	/* prefix with bus number */
	if(messageProcCbData->signalFormat & signalFormat_Bus) {
	  char *ch_str;
	  char len;
	  
	  len = snprintf(NULL, 0, "Ch%" PRIu16, entry->bus);
	  ch_str = malloc(len);
	  assert(ch_str != NULL);
	  len = sprintf(ch_str, "Ch%" PRIu16, entry->bus);
          prefix = signalFormat_stringAppend(prefix, ch_str);
	  free(ch_str);
	}

	/* prefix with dbc name */
	if(messageProcCbData->signalFormat & signalFormat_dbcName) {
	  char *fullname = strdup(entry->filename);
	  char *base;
	  
	  /* select just the basename */
	  assert(fullname != NULL);
	  base = basename(fullname);
          prefix = signalFormat_stringAppend(prefix, base);
	  free(fullname);
	}
	
	/* prefix with message name */
        if(messageProcCbData->signalFormat & signalFormat_Message) {
	  char *tmp_prefix = prefix;

          prefix = signalFormat_stringAppend(prefix, dbcMessage->name);
	  if(tmp_prefix) free(tmp_prefix);
        }

        /* call message decoder with time series storage callback */
        {
          signalProcCbData_t signalProcCbData = {
            messageProcCbData->measurement->timeSeriesHash,
            prefix,
          };

          canMessage_decode(dbcMessage,
                            canMessage,
                            messageProcCbData->timeResolution,
                            signalProc_timeSeries,
                            &signalProcCbData);
        }

        /* free signal prefix */
        if(prefix != NULL) free(prefix);

        /* end search if message was found */
        break;
      }
    }
  }
}

/*
 * process CAN trace file with given bus assignment and output
 * signal format
 */
measurement_t *measurement_read(busAssignment_t *busAssignment,
                                const char *filename,
                                signalFormat_t signalFormat,
                                sint32 timeResolution,
                                parserFunction_t parserFunction,
                                int verbose_level)
{
  FILE *fp;
  measurement_t *measurement;

  measurement = malloc(sizeof(measurement_t));
  if(measurement!= NULL) {
    /* create time series hash */
    measurement->timeSeriesHash = create_hashtable(
        16,
        signalName_computeHash,
        signalNames_equal);
    if(measurement->timeSeriesHash != NULL) {

      /* open input file */
      if(filename != NULL) {
        fp = fopen(filename, "rb");
      } else {
        fp = stdin;
      }
      if(fp != NULL) {
        /* call file processor */
        messageProcCbData_t messageProcCbData = {
          busAssignment,
          measurement,
          signalFormat,
          timeResolution
        };

        /*
         * invoke the file format parser on file pointer fp
         * the parser function is responsible for closing the input
         * file stream
         */
        parserFunction(fp, verbose_level,
		       canMessage_process, &messageProcCbData);

      } else {
        fprintf(stderr, "measurement_read(): can't open input file\n");
        hashtable_destroy(measurement->timeSeriesHash, 0);
        free(measurement);
        measurement = NULL;
      }
    } else {
      fprintf(stderr,
              "measurement_read(): can't create time series hash table\n");
      free(measurement);
      measurement = NULL;
    }
  } else {
    fprintf(stderr,
            "measurement_read(): can't allocate measurement structure\n");
  }
  return measurement;
}

/* free measurement structure */
void measurement_free(measurement_t *m)
{
  // fprintf(stderr,"freeing %p (measurement)\n",m);
  if(m != NULL) {

    /* free time series */
    struct hashtable *timeSeriesHash = m->timeSeriesHash;
    struct hashtable_itr *itr;

    /* loop over all time series in hash */
    if (hashtable_count(timeSeriesHash) > 0) {
      itr = hashtable_iterator(timeSeriesHash);
      do {
        timeSeries_t *timeSeries = hashtable_iterator_value(itr);

        free(timeSeries->time);
        free(timeSeries->value);
      } while (hashtable_iterator_advance(itr));
      free(itr);
    }

    /* free key and value (timeSeries_t) and hashTable */
    hashtable_destroy(m->timeSeriesHash, 1);
    free(m);
  }
}
