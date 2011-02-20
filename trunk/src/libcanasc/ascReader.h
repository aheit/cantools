#ifndef INCLUDE_ASCREAD_H
#define INCLUDE_ASCREAD_H

/*  ascReader.h --  declarations for ascReader
    Copyright (C) 2007-2011 Andreas Heitmann

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


#include <stdio.h>
#include <dbcTypes.h>
#include <time.h>

/* CAN message type */
typedef struct {
  struct {
    time_t tv_sec;
    uint32 tv_nsec;
  } t; /* time stamp */
  uint8   bus;     /* can bus */
  uint32  id;      /* numeric CAN-ID */
  uint8   dlc;
  uint8   byte_arr[8];
} canMessage_t;

/* message received callback function */
typedef void (* msgRxCb_t)(canMessage_t *message, void *cbData);

/* ascRead function */
void ascReader_processFile(FILE *fp, msgRxCb_t msgRxCb, void *cbData);

#endif
