/*  measurement.c --  process ASC measurement file
    Copyright (C) 2007-2009 Andreas Heitmann

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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "measurement.h"
#include "busAssignment.h"
#include "messageHash.h"
#include "signalFormat.h"
#include "../hashtable/hashtable.h"
#include "../hashtable/hashtable_itr.h"
#include "../libcanasc/ascReader.h"
#include "../libcanasc/messageDecoder.h"
#include <dbcModel.h>

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
static unsigned int signalName_computeHash( void *k)
{
  unsigned int hash = 0;
  int c;

  while ((c = *(unsigned char *)k++)) {
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
  uint32 rawValue,
  double physicalValue,
  void *cbData)
{
  /* recover callback data */
  signalProcCbData_t *signalProcCbData = (signalProcCbData_t *)cbData;
  char *outputSignalName =
    signalFormat_stringAppend(signalProcCbData->local_prefix, s->name);
  
  fprintf(stderr,"   %s\t=%f ~ raw=%ld\t~ %d|%d@%d%c (%f,%f)"
	  " [%f|%f] %d %ul \"%s\"\n",
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
	  (unsigned int)s->mux_value,
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
  /* realloc strategy:
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
static void canMessage_process(canMessage_t *canMessage, void *cbData)
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
	char *local_prefix;
	const char *const prefix = NULL;
	
	/* setup and forward message prefix */
	if(messageProcCbData->signalFormat & signalFormat_Message) {
	  local_prefix = signalFormat_stringAppend(prefix, dbcMessage->name);
	} else {
	  if(prefix != NULL) local_prefix = strdup(prefix);
	  else               local_prefix = NULL;
	}

	/* call message decoder with time series storage callback */
	{
	  signalProcCbData_t signalProcCbData = {
	    messageProcCbData->measurement->timeSeriesHash,
	    local_prefix,
	  };

	  canMessage_decode(dbcMessage,
			    canMessage,
			    messageProcCbData->timeResolution,
			    signalProc_timeSeries,
			    &signalProcCbData);
	}

	/* free local prefix */
	if(local_prefix != NULL) free(local_prefix);

        /* end search if message was found */
        break;
      }
    }
  }
}

/*
 * process ASC measurement file with given bus assignment and output
 * signal format
 */
measurement_t *measurement_read(busAssignment_t *busAssignment,
                                const char *asc_filename,
                                signalFormat_t signalFormat,
				sint32 timeResolution )
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
      if(asc_filename != NULL) {
        fp = fopen(asc_filename, "r");
      } else {
        fp = stdin;
      }
      if(fp != NULL) {
	/* call ASC file processor */
	messageProcCbData_t messageProcCbData = {
	  busAssignment,
	  measurement,
	  signalFormat,
	  timeResolution
	};

        ascReader_processFile(fp, canMessage_process, &messageProcCbData);

	/* close input file */
        if(asc_filename != NULL) {
          fclose(fp);
        }
      } else {
        fprintf(stderr, "measurement_read(): can't open ASC file\n");
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
        char         *signalName = hashtable_iterator_key(itr);
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
