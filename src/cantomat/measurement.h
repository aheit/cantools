#ifndef INCLUDE_MEASUREMENT_H
#define INCLUDE_MEASUREMENT_H

/*  measurement.h -- declarations for measurement
    Copyright (C) 2016-2020 Andreas Heitmann

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

#include "hashtable.h"
#include "busassignment.h"
#include "signalformat.h"

/* CAN message type */
typedef struct {
  struct {
    time_t tv_sec;
    uint32_t tv_nsec;
  } t;                    /* time stamp */
  uint16_t  bus;          /* can bus */
  uint32_t  id;           /* numeric CAN-ID */
  uint8_t   dlc;          /* number of bytes */
  uint8_t   byte_arr[64]; /* 64 bytes for CAN-FD messages */
} canMessage_t;

/* message received callback function */
typedef void (* msgRxCb_t)(canMessage_t *message, void *cbData);

typedef struct {
  struct hashtable *timeSeriesHash;
} measurement_t;

typedef struct {
  unsigned int n;
  double *time;
  double *value;
} timeSeries_t;

typedef void (* parserFunction_t)(FILE *fp,
				  int verbose_level,
				  msgRxCb_t msgRxCb,
				  void *cbData);

measurement_t *measurement_read(busAssignment_t *busAssignment,
                                const char *filename,
                                signalFormat_t signalFormat,
                                sint32 timeResolution,
                                parserFunction_t parserFunction,
				int verbose_level);

void measurement_free(measurement_t *m);

#endif
