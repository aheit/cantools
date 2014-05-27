/*  vsbReader.c --  parse VSB files
    Copyright (C) 2014 Andreas Heitmann

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
#include <stdlib.h>
#include <ctype.h>
#include "vsbReader.h"

/*
 * Parser for VSB files.
 *
 * fp       FILE pointer of input file
 * msgRxCb  callback function for received messages
 * cbData   pointer to opaque callback data
 */
void vsbReader_processFile(FILE *fp, msgRxCb_t msgRxCb, void *cbData)
{
  char busmap[256];
  char buffer[100];
  char *cp;
  size_t ret;
  vsb_header_t header;
  icsSpyMessage_t msg;

  /* initialize */
  memset(busmap,0,sizeof(busmap));

  /* get header */
  ret = fread(&header, sizeof(header), 1, fp);
  if(ret != 1) goto read_error;

  /* diagnose header */
  if(0 != memcmp(header.text_identifier, "icsbin", 6)) {
    fprintf(stderr, "unexpected file identifier, not \"icsbin\", aborting\n");
    return;
  }

  if(   (header.file_version != 0x0101)
     && (header.file_version != 0x0102)
     && (header.file_version != 0x0103)) {
    fprintf(stderr, "unexpected file version %x, aborting\n",
	    header.file_version);
  }
  printf("file version %x\n",header.file_version);
  
  /* loop for reading input lines */
  while(1) {
    canMessage_t message;
    uint8_t i;
    double dTime;

    ret = fread(&msg, sizeof(msg), 1, fp);
    // printf("fread %d %d\n", ret, feof(fp));
    if(ret != 1) {
      break;
    }
    
    if(msg.NumberBytesData > 8) {
      fprintf(stderr, "error: DLC > 8\n");
      goto read_error;
    }

    /*
     * timestamps: the fractional part has 1-9 decimal places,
     * depending on the setting of the recording SW.
     */
    const float NEOVI_TIMEHARDWARE2_SCALING = 0.1048576;
    const float NEOVI_TIMEHARDWARE_SCALING  = 1.6e-6;

    dTime = NEOVI_TIMEHARDWARE2_SCALING * msg.TimeHardware2
          + NEOVI_TIMEHARDWARE_SCALING  * msg.TimeHardware, 
    message.t.tv_sec  = dTime;
    message.t.tv_nsec = (dTime-message.t.tv_sec)*1e9;
    message.bus = msg.NetworkID;
    message.dlc = msg.NumberBytesData;
    
    /* get message bytes */
    for(i = 0; i < message.dlc; i++) {
      message.byte_arr[i] = msg.Data[i];
    }
    message.id = (uint32)msg.ArbIDOrHeader;

    busmap[message.bus] = 1;

    /* invoke message receive callback function */
    msgRxCb(&message, cbData);
  } /* end message loop */

  /* dump busmap */
  {
    uint8_t i;
    
    fputs("bus allocation: ",stdout);
    do {
      if(busmap[i]) printf("%d  ",i);
      i++;
    } while(i!=0);
    puts("");
  }
  return;

read_error:
  fprintf(stderr,"error reading vsb file, aborting\n");
  return;
}
