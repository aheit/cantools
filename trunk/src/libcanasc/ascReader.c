/*  ascReader.c --  parse ASC files
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
#include <stdlib.h>
#include "ascReader.h"

typedef enum {
  unset,
  decimal = 10,
  hexadecimal = 16
} numBase_t;

/*
 * Parser for ASC files.
 *
 * fp       FILE pointer of input file
 * msgRxCb  callback function for received messages
 * cbData   pointer to opaque callback data
 */
void ascReader_processFile(FILE *fp, msgRxCb_t msgRxCb, void *cbData)
{
  char buffer[100];
  char *cp;
  numBase_t numbase = unset;

  /* loop for reading input lines */
  while(1) {
    char *buffer_lasts; /* reentrancy structure for strtok on buffer */
    fgets(buffer,sizeof(buffer)-1,fp);
    if(feof(fp)) break;                         /* EOF... stop loop */
    cp = strtok_r (buffer," ", &buffer_lasts);  /* get first token */
    if(!strcmp(cp,"date")) {
      ;                                         /* skip date info */
    } else if(!strcmp(cp,"base")) {             /* parse numeric base */
      cp = strtok_r(NULL," ", &buffer_lasts);    /* dec/hex */
      if(!strcmp(cp,"dec")) {
        numbase = decimal;
      } else if(!strcmp(cp,"hex")) {
        numbase = hexadecimal;
      } else {
        fprintf(stderr,
                "ascReader_processFile(): unknown numeric base %s\n",
                cp);
      }
      continue;
    } else if(!strcmp(cp,"internal")) {
      continue;
    } else if(!strcmp(cp,"Begin")) {
      continue;
    } else if(!strcmp(cp,"Start")) {
      continue;
    } else {
      canMessage_t message;

      char   *id_str;  /* symbolic CAN-ID */
      char   *rx;
      char   *d;
      int     i;

      if(numbase == unset) {
        fprintf(stderr,"ascReader_processFile(): missing numeric base\n");
        break;
      }

      /* parse line */

      /*
       * timestamps: the fractional part has 1-9 decimal places,
       * depending on the setting of the recording SW.
       */
      char *tp;
      char *time_lasts;
      tp = strtok_r(cp, ".", &time_lasts); if(tp == NULL) continue;

      message.t.tv_sec = 0;
      message.t.tv_nsec = 0;
      message.t.tv_sec = atoi(tp);

      tp = strtok_r(NULL, " ", &time_lasts); if(tp == NULL) continue;
      {
        int i;
        for(i = 0; i < 9; i++) {
          message.t.tv_nsec *= 10;
          if(isdigit(*tp)) {
            message.t.tv_nsec += (*tp) - '0';
            tp++;
          }
        }
      }

      /* remove trailing newline */
      cp = strtok_r(NULL, "\n", &buffer_lasts); if(cp == NULL) continue;

      /* get bus number */
      cp = strtok_r(cp, " ", &buffer_lasts); if(cp == NULL) continue;
      message.bus = atoi(cp);

      /* get message identifier */
      cp = strtok_r(NULL, " ", &buffer_lasts); if(cp == NULL) continue;
      id_str = cp;

      cp = strtok_r(NULL, " ", &buffer_lasts); if(cp == NULL) continue;
      rx = cp;
      if((rx[0] != 'R') || (rx[1] != 'x')) continue;

      cp = strtok_r(NULL, " ", &buffer_lasts); if(cp == NULL) continue;
      d = cp;

      /* get DLC */
      cp = strtok_r(NULL, " ", &buffer_lasts); if(cp == NULL) continue;
      message.dlc = atoi(cp);

      /* get message bytes */
      for(i = 0; i < message.dlc; i++) {
        cp = strtok_r(NULL, " ", &buffer_lasts); if(cp == NULL) break;
        message.byte_arr[i] = (uint8)strtol(cp,NULL,numbase);
      }

      /*
       * compute numeric CAN-ID
       *
       * Different formats are possible based on the selection in the
       * Options/Appearance menu:
       *
       * numeric  (Messages = ID)
       * symbolic (Messages = Message name)
       *
       * decimal     (Number Formats = Decimal)
       * hexadecimal (Number Formats = Hexadecimal)
       *
       * Symbolic mode is only partially supported. It will work only
       * if the hexadecimal ID followed by a lowercaps 'h' is appended
       * to the message name.
       */
      {
        int len = strlen(id_str);
        if(len == 0) break;

        if(id_str[len-1] != 'h') {
          /* assume numeric mode */
          message.id = (uint16)strtol(id_str,NULL,numbase);
        } else {
          /* symbolic mode with hex hint */
          char *cp;
	  char *id_lasts;

          strtok_r(id_str,"_", &id_lasts);
          cp = strtok_r(NULL, "h", &id_lasts);

          /* force hex mode for id string */
          message.id = (uint16)strtol(cp,NULL,16);
        }
      }

      /* invoke message receive callback function */
      msgRxCb(&message, cbData);
    }
  }
}
