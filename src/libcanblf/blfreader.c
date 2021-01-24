/*  blfReader.c -- parse BLF files
    Copyright (C) 2016-2021 Andreas Heitmann

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

#include "dbctypes.h"
#include "blfapi.h"
#include "measurement.h"

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

  printf("MSG %ld.%09" PRIu32 ": %d 0x%04x %d [ ",
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
blfVBLCANMessageParseTime(const VBLObjectHeader* header, time_t *sec,
                          uint32 *nsec)
{
  const uint64_t C_1E9  = 1000000000ULL;
  const uint64_t C_1E5  =     100000ULL;
  const uint64_t C_1E4  =      10000ULL;
  const uint32_t flags = header->mObjectFlags;
  
  if (flags & BL_OBJ_FLAG_TIME_TEN_MICS) {
    /* 10 microsecond increments */
    *sec   = header->mObjectTimeStamp / C_1E5;
    *nsec = (header->mObjectTimeStamp % C_1E5) * C_1E4;
  } else if (flags & BL_OBJ_FLAG_TIME_ONE_NANS) {
    /* 1 nanosecond increments */
    *sec  = header->mObjectTimeStamp / C_1E9;
    *nsec = header->mObjectTimeStamp % C_1E9;
  } else { /* unknown time format - emit zero time stamp */
    *sec = 0;
    *nsec = 0;
  }
}

/*
 * Parser for BLF files.
 *
 * mFile       FILE pointer of input file
 * verbose_level  0: silent, 1: verbose, 2: debug
 * msgRxCb  callback function for received messages
 * cbData   pointer to opaque callback data
 */
void blfReader_processFile(FILE *fp, int verbose_level,
                           msgRxCb_t msgRxCb, void *cbData)
{
  VBLObjectHeaderBase base;
  VBLFileStatisticsEx statistics;
  BLFHANDLE h;
  success_t success;

  /* get header */
  h = blfCreateFile(fp);
  if(h == NULL) {
    fprintf(stderr, "blfReader_processFile: cannot open file\n");
    goto read_error;
  }

  /* diagnose header */
  statistics.mStatisticsSize = sizeof(statistics);
  blfGetFileStatisticsEx(h, &statistics);

  /* print some file statistics */
  if(verbose_level >= 1) {
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
    case BL_OBJ_TYPE_CAN_MESSAGE2:
    case BL_OBJ_TYPE_CAN_FD_MESSAGE:
    case BL_OBJ_TYPE_CAN_FD_MESSAGE_64:
      {
        canMessage_t canMessage;

        /* select type-dependent data structure and setup pointers to
           the relevant elements for further processing */
        VBLCANMessage message;
        VBLCANMessage2 message2;
        VBLCANFDMessage fdmessage;
        VBLCANFDMessage64 fdmessage64;

        size_t messageSize;
        VBLObjectHeaderBase *headerBase;
        uint8_t  *data;
        VBLObjectHeader *header;
        uint8_t  *dlc;
        void     *channel;
        size_t    channelSize;
        uint8_t   maxDLC;

        switch(base.mObjectType) {
          case BL_OBJ_TYPE_CAN_MESSAGE:
            messageSize = sizeof(message);
            headerBase = &message.mHeader.mBase;
            data = message.mData;
            header = &message.mHeader;
            dlc = &message.mDLC;
            channel = &message.mChannel;
            channelSize = sizeof(message.mChannel);
            maxDLC = 8;
            break;
          case BL_OBJ_TYPE_CAN_MESSAGE2:
            messageSize = sizeof(message2);
            headerBase = &message2.mHeader.mBase;
            data = message2.mData;
            header = &message2.mHeader;
            dlc = &message2.mDLC;
            channel = &message2.mChannel;
            channelSize = sizeof(message2.mChannel);
            maxDLC = 8;
            break;
          case BL_OBJ_TYPE_CAN_FD_MESSAGE:
            messageSize = sizeof(fdmessage);
            headerBase = &fdmessage.mHeader.mBase;
            data = fdmessage.mData;
            header = &fdmessage.mHeader;
            dlc = &fdmessage.mDLC;
            channel = &fdmessage.mChannel;
            channelSize = sizeof(fdmessage.mChannel);
            maxDLC = 64;
            break;
          case BL_OBJ_TYPE_CAN_FD_MESSAGE_64:
            messageSize = sizeof(fdmessage64);
            headerBase = &fdmessage64.mHeader.mBase;
            data = fdmessage64.mData;
            header = &fdmessage64.mHeader;
            dlc = &fdmessage64.mDLC;
            channel = &fdmessage64.mChannel;
            channelSize = sizeof(fdmessage64.mChannel);
            maxDLC = 64;
            break;
          }
          
        *headerBase = base;
        success = blfReadObjectSecure(h, headerBase, messageSize);
        
        if(success) {
          /* diagnose data */
          if(*dlc > maxDLC) {
            fprintf(stderr, "invalid CAN message lenght: DLC > %d\n", maxDLC);
            goto read_error;
          }

          /* copy data */
          if(channelSize == 2) {
            canMessage.bus = *(uint16_t *)channel;
          } else {
            canMessage.bus = *(uint8_t *)channel;
          }
          canMessage.dlc = *dlc;
          memcpy(canMessage.byte_arr, data, *dlc);

          /* direct copy of message id required due to packed alignment */
          switch(base.mObjectType) {
          case BL_OBJ_TYPE_CAN_MESSAGE:
            canMessage.id = message.mID;
            break;
          case BL_OBJ_TYPE_CAN_MESSAGE2:
            canMessage.id = message2.mID;
            break;
          case BL_OBJ_TYPE_CAN_FD_MESSAGE:
            canMessage.id = fdmessage.mID;
            break;
          case BL_OBJ_TYPE_CAN_FD_MESSAGE_64:
            canMessage.id = fdmessage64.mID;
            break;
          }

          /* parse time */
          blfVBLCANMessageParseTime(header, &(canMessage.t.tv_sec),
                                    &(canMessage.t.tv_nsec));

          /* debug: dump message */
          if(verbose_level >= 2) {
            blfCANMessageDump(&canMessage);
          }
          
          /* invoke canMessage receive callback function */
          msgRxCb(&canMessage, cbData);

          /* free allocated memory */
          blfFreeObject(h, headerBase);
        }
      }
      break;
    default:
      /* skip all other objects */
      if(verbose_level >= 2) {
        printf("skipping object type = 0x%" PRIx32 "\n", base.mObjectType);
      }
      success = blfSkipObject(h, &base);
      break;
    }
  }
  blfCloseHandle(h);
  return;

read_error:
  fprintf(stderr,"error reading BLF file, aborting\n");
  return;
}
