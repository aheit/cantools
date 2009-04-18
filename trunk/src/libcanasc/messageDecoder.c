/*  messageDecoder.c --  decode CAN messages
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

#include <dbcModel.h>
#include "messageDecoder.h"

void canMessage_decode(message_t      *dbcMessage,
		       canMessage_t   *canMessage,
		       sint32          timeResolution,
		       signalProcCb_t  signalProcCb,
		       void           *cbData)
{
  signal_list_t *sl;
  uint32  sec = canMessage->t.tv_sec;
  sint32 nsec = canMessage->t.tv_nsec;
  double dtime;

  /* limit time resolution */
  if(timeResolution != 0) {
    nsec -= (nsec % timeResolution);
  }
  dtime = nsec * 1e-9 + sec;

  /* debug: dump canMessage */
#if 0
  fprintf(stderr,
          "%d.%09d %d %04x     %02x %02x %02x %02x %02x %02x %02x %02x\n",
          sec, nsec,
          canMessage->bus, canMessage->id,
          canMessage->byte_arr[0], canMessage->byte_arr[1],
          canMessage->byte_arr[2], canMessage->byte_arr[3],
          canMessage->byte_arr[4], canMessage->byte_arr[5],
          canMessage->byte_arr[6], canMessage->byte_arr[7] );
#endif

  /* iterate over all signals */
  for(sl = dbcMessage->signal_list; sl != NULL; sl = sl->next) {
    /*
     * The "raw value" of a signal is the value as it is transmitted
     * over the network.
     */
    uint32 rawValue   = 0;

    /*
     * compute some signal properties
     *
     * signal bit order:
     *
     *     7  6  5  4  3  2  1  0 offset
     *    bit
     * 0   7  6  5  4  3  2  1  0
     * 1  15 14 13 12 11 10  9  8
     * 2  23 22 21 20 19 18 17 16
     * 3  31 30 29 28 27 26 25 24
     * 4  39 38 37 36 35 34 33 32
     * 5  47 46 45 44 43 42 41 40
     * 6  55 54 53 52 51 50 49 48
     * 7  63 62 61 60 59 58 57 56
     * |
     * start_byte
     *
     * big endian place value exponent
     *                15 14 13 12   <- start_byte
     *    11 10  9  8  7  6  5  4
     *     3  2  1  0               <- end_byte
     *
     * little endian place value exponent
     *     3  2  1  0               <- start_byte
     *    11 10  9  8  7  6  5  4
     *                15 14 13 12   <- end_byte
     */
    const signal_t *const s = sl->signal;
    uint8  bit_len      = s->bit_len;
    uint8  start_offset = s->bit_start & 7;
    uint8  start_byte   = s->bit_start / 8;
    uint8  end_byte     = start_byte + (7 + bit_len - start_offset - 1)/8;
    uint8  data;
    sint8  work_byte;
    uint8  shift;

    /* align signal into ulong32 */
    /* 0 = Big Endian, 1 = Little Endian */    
    if(s->endianess == 0) { /* big endian */
      uint8  end_offset   = (start_offset - bit_len + 1) & 7;

      /* loop over all source bytes from start_byte to end_byte */
      for(work_byte = start_byte; work_byte <= end_byte; work_byte++) {
	/* fetch source byte */
        data = canMessage->byte_arr[work_byte];

	/* process source byte */
        if(work_byte == start_byte && start_offset != 7) {
	  /* less that 8 bits in start byte? mask out unused bits */
          data &= (uint8)~0 >> (7 - start_offset);
          shift = start_offset + 1;
        } else {
          shift = 8; /* use all eight bits */
        }
        if(work_byte == end_byte && end_offset != 0) {
	  /* less that 8 bits in end byte? shift out unused bits */
          data >>= end_offset;
          shift -= end_offset;
        }

	/* store processed byte */
        rawValue <<= shift; /* make room for shift bits */
        rawValue |= data;   /* insert new bits at low position */
      }
    } else {
      /* little endian - similar algorithm with reverse bit significance  */
      uint8  end_offset   = (start_offset + bit_len - 1) & 7;

      for(work_byte = end_byte; work_byte >= start_byte; work_byte--) {
        data = canMessage->byte_arr[work_byte];
        if(work_byte == end_byte && end_offset != 7) {
          data &= (uint8)~0 >> (7 - end_offset);
          shift = end_offset + 1;
        } else {
          shift = 8;
        }
        if(work_byte == start_byte && start_offset != 0) {
          data >>= start_offset;
          shift -= start_offset;
        }
        rawValue <<= shift;
        rawValue |= data;
      }
    }

    {
      double physicalValue;

      /* perform sign extension */
      if(s->signedness && (bit_len < 32)) {
        sint32 m = 1<< (bit_len-1);
        rawValue = ((sint32)rawValue ^ m) - m;
      }

      /*
       * Factor, Offset and Physical Unit
       *
       * The "physical value" of a signal is the value of the physical
       * quantity (e.g. speed, rpm, temperature, etc.) that represents
       * the signal.
       * The signal's conversion formula (Factor, Offset) is used to
       * transform the raw value to a physical value or in the reverse
       * direction.
       * [Physical value] = ( [Raw value] * [Factor] ) + [Offset]
       */
      if(s->signedness) {
        physicalValue = (double)(sint32)rawValue
          * s->scale + s->offset;
      } else {
        physicalValue = (double)        rawValue
          * s->scale + s->offset;
      }

#if 0
      fprintf(stderr,"   %s\t=%f ~ raw=%ld\t~ %d|%d@%d%c (%f,%f)"
             " [%f|%f] %d %ul \"%s\"\n",
             outputSignalName,
             physicalValue,
             rawValue,
             s->bit_start,
             s->bit_len,
             s->endianess,
             s->signedness?'-':'+',
             s->scale,
             s->offset,
             s->min,
             s->max,
             s->mux_type,
             (unsigned int)s->mux_value,
             s->comment!=NULL?s->comment:"");
#endif

      /* invoke signal processing callback function */
      signalProcCb(s, dtime, rawValue, physicalValue, cbData);
    }
  }
}
