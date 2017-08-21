/*  blfReader.c -- parse BLF files
    Copyright (C) 2017 Andreas Heitmann

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
# include "config.h"
#endif

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "dbctypes.h"
#include "blfapi.h"
#include "measurement.h"

extern int verbose_flag;
extern int debug_flag;

static void
blfSystemTimePrint(SYSTEMTIME *const s)
{
  char *dow[] = {
      "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
  };
  printf("%s %04d-%02d-%02d %02d:%02d:%02d.%03d",
   (s->wDayOfWeek < 7) ? dow[s->wDayOfWeek < 7 ]: "???",
   s->wYear,
   s->wMonth,
   s->wDay,
   s->wHour,
   s->wMinute,
   s->wSecond,
   s->wMilliseconds);
}

static void
blfCANMessageDump(const canMessage_t* canMessage)
{
  uint8_t i;

  printf("MSG %ld.%09ld: %d 0x%04x %d [ ",
          canMessage->t.tv_sec,
          canMessage->t.tv_nsec,
          canMessage->bus,
          canMessage->id,
          canMessage->dlc);
  for(i = 0; i < canMessage->dlc; i++) {
    printf("%02x ", canMessage->byte_arr[i]);
  }
  puts("]");
}

static void
blfCANMessageFromVBLCANMessage (canMessage_t* canMessage,
                                const VBLCANMessage* message)
{
  /* copy data */
  canMessage->bus = message->mChannel;
  canMessage->dlc = message->mDLC;
  memcpy(canMessage->byte_arr, message->mData, canMessage->dlc);
  canMessage->id = (uint32)message->mID;
}

static void
blfVBLCANMessageParseTime(const VBLCANMessage* message, time_t *sec,
                          uint32 *nsec)
{
  const uint64_t C_1E9  = 1000000000ULL;
  const uint64_t C_1E5  =     100000ULL;
  const uint64_t C_1E4  =      10000ULL;
  const uint32_t flags = message->mHeader.mObjectFlags;
  
  if (flags & BL_OBJ_FLAG_TIME_TEN_MICS) {
    /* 10 microsecond increments */
    *sec   = message->mHeader.mObjectTimeStamp / C_1E5;
    *nsec = (message->mHeader.mObjectTimeStamp % C_1E5) * C_1E4;
  } else if (flags & BL_OBJ_FLAG_TIME_ONE_NANS) {
    /* 1 nanosecond increments */
    *sec  = message->mHeader.mObjectTimeStamp / C_1E9;
    *nsec = message->mHeader.mObjectTimeStamp % C_1E9;
  } else { /* unknown time format - emit zero time stamp */
    *sec = 0;
    *nsec = 0;
  }
}

/*
 * Parser for BLF files.
 *
 * mFile       FILE pointer of input file
 * msgRxCb  callback function for received messages
 * cbData   pointer to opaque callback data
 */
void blfReader_processFile(FILE *fp, msgRxCb_t msgRxCb, void *cbData)
{
  VBLObjectHeaderBase base;
  VBLCANMessage message;
  VBLFileStatisticsEx statistics = { sizeof(statistics) };
  canMessage_t canMessage;
  BLFHANDLE h;
  success_t success;

  /* get header */
  h = blfCreateFile(fp);
  if(h == NULL) {
    fprintf(stderr, "blfReader_processFile: cannot open file\n");
    goto read_error;
  }

  /* diagnose header */
  blfGetFileStatisticsEx(h, &statistics);

  /* print some file statistics */
  if(verbose_flag) {
    printf("BLF Start  : ");
    blfSystemTimePrint(&statistics.mMeasurementStartTime);
    printf("\nBLF End    : ");
    blfSystemTimePrint(&statistics.mLastObjectTime);
    printf("\nObject Count: %u\n", statistics.mObjectCount);
  }

  success = 1;
  while(success && blfPeekObject(h, &base)) {
    switch(base.mObjectType) {
      case BL_OBJ_TYPE_CAN_MESSAGE:
        message.mHeader.mBase = base;
        success = blfReadObjectSecure(h, &message.mHeader.mBase,
                                      sizeof(message));
        if(success) {
          /* diagnose data */
          if(message.mDLC > 8) {
            fprintf(stderr, "invalid CAN message: DLC > 8\n");
            goto read_error;
          }

          /* translate VBLCANMessage to message structure */
          blfCANMessageFromVBLCANMessage(&canMessage, &message);
          blfVBLCANMessageParseTime(&message, &canMessage.t.tv_sec,
                                    &canMessage.t.tv_nsec);

          if(debug_flag) {
            blfCANMessageDump(&canMessage);
          }

          /* invoke canMessage receive callback function */
          msgRxCb(&canMessage, cbData);

          /* free allocated memory */
          blfFreeObject(h, &message.mHeader.mBase);
        }
        break;
      default:
        /* skip all other objects */
        success = blfSkipObject(h, &base);
        if(debug_flag) {
          printf("skipping object type = %d\n", base.mObjectType);
        }
        break;
    }
  }
  blfCloseHandle(h);
  return;

read_error:
  fprintf(stderr,"error reading BLF file, aborting\n");
  return;
}
