#ifndef INCLUDE_VSBREAD_H
#define INCLUDE_VSBREAD_H

/*  vsbReader.h --  declarations for vsbReader
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

/*
 * vs3bin data structures, see
 * http://www.intrepidcs.com/support/ICSDocumentation/VehicleSpy/vs3Bin.htm
 * http://www.intrepidcs.com/support/ICSDocumentation/neoAPILinux/MessageStructures.htm
 */

/* VSB header 0x101..0x103*/
typedef struct {
  uint8_t text_identifier[6];
  uint16_t file_version;
  uint16_t unknown;
} vsb_header_t;

typedef struct {
  /*
   * see www.intrepidcs.com/support/ICSDocumentation/neoAPILinux/StatusBitfields.htm
   */ 
  uint32_t StatusBitField;
  uint32_t StatusBitField2;
  uint32_t TimeHardware;
  uint32_t TimeHardware2;
  uint32_t TimeSystem;
  uint32_t TimeSystem2;
  uint8_t  TimeStampHardwareID;
  uint8_t  TimeStampSystemID;
  uint8_t  NetworkID;
  uint8_t  NodeID;
  uint8_t  Protocol; 
  uint8_t  MessagePieceID;
  uint8_t  ExtraDataPtrEnabled;
  uint8_t  NumberBytesHeader;
  uint8_t  NumberBytesData;
  int16_t  DescriptionID;
  int32_t  ArbIDOrHeader;
  uint8_t  Data[8]; 
  uint8_t  AckBytes[8]; 
  float    ExtraDataPtr;
  uint8_t  MiscData;
} icsSpyMessage_t;

typedef struct
{
  uint32_t SystemTimeStampID;
  uint32_t SystemTime1;
  uint32_t SystemTime2;
  uint32_t HardwareTimeStampID;
  uint32_t HardwareTime1;
  uint32_t HardwareTime2;
} icsSpyMsgTime;

#ifdef __cplusplus
extern "C" {
#endif

/* vsbRead function */
void vsbReader_processFile(FILE *fp, msgRxCb_t msgRxCb, void *cbData);

#ifdef __cplusplus
}
#endif

#endif
