#ifndef INCLUDE_MEASUREMENT_H
#define INCLUDE_MEASUREMENT_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>

#include "../hashtable/hashtable.h"
#include "busAssignment.h"
#include "signalFormat.h"

typedef struct {
  struct hashtable *timeSeriesHash;
} measurement_t;

typedef struct {
  unsigned int n;
  double *time;
  double *value;
} timeSeries_t;

measurement_t *measurement_read(busAssignment_t *messageHash,
                                const char      *asc_filename,
                                signalFormat_t   signalFormat);

void measurement_free(measurement_t *m);

#endif
