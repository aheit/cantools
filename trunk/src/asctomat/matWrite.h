#ifndef INCLUDE_MATWRITE_H
#define INCLUDE_MATWRITE_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include "measurement.h"

int matWrite(measurement_t *measurement, const char *filename);

#endif
