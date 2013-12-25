/*  matWrite.c -- write out MAT files
    Copyright (C) 2007-2009, 2013 Andreas Heitmann

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

#include "config.h"

#if WITH_DMALLOC
#include <dmalloc.h>
#endif

#include <stdio.h>
#include <matio.h>
#include "measurement.h"
#include "../hashtable/hashtable_itr.h"

/*
 * matWrite - write signals from measurement structure to MAT file
 */
int matWrite(measurement_t *measurement, const char *outFileName)
{
  size_t dims[2];
  int err = 0;
  mat_t *mat;
  matvar_t *matvar;

  mat = Mat_Create(outFileName, NULL);
  if (mat != NULL) {

    /* loop over all time series */
    struct hashtable *timeSeriesHash = measurement->timeSeriesHash;

    /* Iterator constructor only returns a valid iterator if
     * the hashtable is not empty */
    if (hashtable_count(timeSeriesHash) > 0) {

      struct hashtable_itr *itr = hashtable_iterator(timeSeriesHash);
      do {
        char         *signalName = hashtable_iterator_key(itr);
        timeSeries_t *timeSeries = hashtable_iterator_value(itr);
        double *timeValue = (double *)malloc(sizeof(double)*2*timeSeries->n);
        unsigned int i;

        /*
         * build up a 1x2n array with time stamps in [0..n-1] and
         * values in [n..2n-1].
         */
        for(i=0;i<timeSeries->n;i++) {
          timeValue[i] = timeSeries->time[i];
        }
        for(i=0;i<timeSeries->n;i++) {
          timeValue[timeSeries->n + i] = timeSeries->value[i];
        }
        dims[0] = timeSeries->n;
        dims[1] = 2;

        /* output signal to mat structure and free up temp array. */
        matvar = Mat_VarCreate(signalName, MAT_C_DOUBLE, MAT_T_DOUBLE,
                               2, dims, timeValue, 0);
        Mat_VarWrite(mat, matvar, 0);
        Mat_VarFree(matvar);

        free(timeValue);
      } while (hashtable_iterator_advance(itr));
      free(itr);
    }

    Mat_Close(mat);
  } else {
    fprintf(stderr, "error: could not create MAT file %s\n", outFileName);
    err = 1;
  }

  return err;
}

