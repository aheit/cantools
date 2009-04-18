#ifndef INCLUDE_SIGNALFORMAT_H
#define INCLUDE_SIGNALFORMAT_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

typedef enum {
  signalFormat_Name     = 1<<1,
  signalFormat_Message  = 1<<2,
  signalFormat_Database = 1<<3,
} signalFormat_t;

char *signalFormat_stringAppend(const char *in, const char *app);

#endif
