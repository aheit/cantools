/*  clgreader.c --  parse CLG files
    Copyright (C) 2014-2020 Andreas Heitmann

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

#ifdef HAVE_INTTYPES_H
# include <inttypes.h>
#endif
#ifdef HAVE_STDINT_H
# include <stdint.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "clgreader.h"

/*
 * Parser for CLG files.
 *
 * fp       FILE pointer of input file
 * verbose_level  0: silent, 1: verbose, 2: debug
 * msgRxCb  callback function for received messages
 * cbData   pointer to opaque callback data
 */
void clgReader_processFile(FILE *fp, int verbose_level,
                           msgRxCb_t msgRxCb, void *cbData)
{
  uint8_t busmap[256];
  size_t ret;
  clg_header_t header;
  clg_message_t msg;
  uint32_t channelshift, id_mask;

  /* initialize */
  memset(busmap,0,sizeof(busmap));

  /* get header */
  ret = fread(&header, sizeof(header), 1, fp);
  if(ret != 1) goto read_error;

  /* diagnose header */
  if(0 != memcmp(header.identifier, "clg2", 4)) {
    fprintf(stderr, "unexpected file identifier, not \"clg2\", aborting.\n");
    return;
  }

  /* bus type determination */
  if(   ((header.channel_type1 == 255) && (header.channel_type2 == 7))
     || ((header.channel_type1 == 0) && (header.channel_type2 == 0))) {
    channelshift = 11; /* 11-bit CAN */
  } else if((header.channel_type1 == 255) && (header.channel_type2 == 255)) {
    channelshift = 29; /* 29-bit CAN */
  } else {
    fprintf(stderr, "unexpected bus type (%d, %d), aborting.\n",
            header.channel_type1, header.channel_type2 );
    return;
  }

  id_mask = (1u << channelshift)-1;

  /* loop for reading input lines */
  while(1) {
    canMessage_t message;
    uint8_t i;
    double dTime;
    uint32_t dTime32;
    uint32_t message_id;
    uint8_t channel;
    uint32_t id_channel;

    ret = fread(&msg, sizeof(msg), 1, fp);
    if(ret != 1) {
      break;
    }
    
    id_channel =  (msg.id_channel_array[3] << 24)
          | (msg.id_channel_array[2] << 16)
          | (msg.id_channel_array[1] << 8)
          |  msg.id_channel_array[0];

    message_id = id_channel & id_mask;
    channel    = (id_channel >> channelshift) & 3;

    // printf("%1d %08x\t",channel, message_id);

    /*
     * timestamp
     */
    dTime32 = (msg.log_time_array[3] << 24)
          | (msg.log_time_array[2] << 16)
          | (msg.log_time_array[1] << 8)
          |  msg.log_time_array[0];
    dTime = dTime32 * 0.001;
    // printf("%11.3lf\t",dTime);

    message.t.tv_sec  = dTime;
    message.t.tv_nsec = (dTime-message.t.tv_sec)*1e9;
    message.bus = channel;
    message.dlc = 8;
    
    /* get message bytes */
    for(i = 0; i < message.dlc; i++) {
      message.byte_arr[i] = msg.data_array[i];
      // printf("%02x ",message.byte_arr[i]);
    }
    message.id = message_id;
    // puts("");

    busmap[message.bus] = 1;

    /* invoke message receive callback function */
    msgRxCb(&message, cbData);
  } /* end message loop */
  goto done;

read_error:
  fprintf(stderr,"error reading CLG file, aborting\n");

done:
  /* close input file stream */
  fclose(fp);
}
