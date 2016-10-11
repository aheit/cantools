#ifndef INCLUDE_CLGREAD_H
#define INCLUDE_CLGREAD_H

/*  clgReader.h --  declarations for clgReader
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
#include <stdint.h>
#include <time.h>
#include <dbcTypes.h>
#include "../cantomat/measurement.h"

typedef struct {
  uint8_t  log_time_array[4];   /* time */
  uint8_t  id_channel_array[4]; /* id and channel */
  uint8_t  data_array[8];       /* data */
} clg_message_t;

/* CLG header 0x101..0x103*/
typedef struct {
  char identifier[4];
  uint8_t unknown[8];
  uint8_t channel_type1;
  uint8_t channel_type2;
  uint8_t unknown2[6];
  clg_message_t unknown3[16];
} clg_header_t;

/* clgRead function */
void clgReader_processFile(FILE *fp, msgRxCb_t msgRxCb, void *cbData);

#endif
