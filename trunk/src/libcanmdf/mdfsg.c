/*  mdfsg.c --  access MDF signal groups
    Copyright (C) 2012, 2013 Andreas Heitmann

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
#include <assert.h>
#include "mdfsg.h"
#include "mdfmodel.h"

/* convert signal to double value */
double
mdf_signal_convert(const uint8_t *const data_int_ptr,
		   const mdf_t *const mdf,
		   const cn_block_t *const cn_block)
{
  /* decode */
  uint8_t bit_offset = cn_block->first_bit%8; /* LSB */
  cc_block_t *cc_block = cc_block_get(mdf,
				      cn_block->link_conversion_formula);
  double converted_double;
  int64_t data_int64;
  double data_ieee754;
  uint16_t number_bits = cn_block->number_bits;

  /* extract data */
  switch(cn_block->signal_data_type) {
  case 0: /* unsigned integer */
    if(number_bits == 1) {
      data_int64 = ((*(uint8_t *)data_int_ptr) >> bit_offset) & 1;
    } else if(number_bits <= 9) {
      data_int64 = ((*(uint16_t *)data_int_ptr) >> bit_offset)
	& ((1u<<number_bits)-1u);
    } else if(number_bits <= 25) {
      data_int64 = ((*(uint32_t *)data_int_ptr) >> bit_offset)
	& ((1u<<number_bits)-1u);
    } else {
      assert(bit_offset + number_bits <= 64);
      data_int64 = ((*(uint64_t *)data_int_ptr) >> bit_offset)
	& (((uint64_t)1<<number_bits)-(uint64_t)1);
    }
    break;
  case 1: /* signed integer */
    if(number_bits <= 9) {
      data_int64  =
	(int64_t)(((int16_t)
		   ((*(uint16_t *)data_int_ptr)
		    << (16-number_bits-bit_offset)))
		  >>(16-number_bits));
      /* printf("%4x %d %d -> %16llx\n",*(uint16_t *)data_int_ptr, number_bits, bit_offset, data_int64); */
    } else if(number_bits <= 25) {
      data_int64  =
	      (int64_t)(((int32_t)
			 ((*(uint32_t *)data_int_ptr)
			  << (32-number_bits-bit_offset)))
			>>(32-number_bits));
      /* printf("%8x %d %d -> %16llx\n",*(uint32_t *)data_int_ptr, number_bits, bit_offset, data_int64);  */
    } else {
      assert(bit_offset + number_bits <= 64);
      data_int64  =
	      (((int64_t)
		((*(uint64_t *)data_int_ptr)
		 << (64-number_bits-bit_offset)))
	       >>(64-number_bits));
      /* printf("%16llx %d %d -> %16llx\n",*(uint64_t *)data_int_ptr, number_bits, bit_offset, data_int64); */
    }
    break;
  case 2: /* float */
    data_ieee754 = *(float *)data_int_ptr;
    break;
  case 3: /* double */
    data_ieee754 = *(double *)data_int_ptr;
    break;
  case 7: /* string */
    data_int64 = 0;
    break;
  default:
    fprintf(stderr,"signal_data_type %hu not implemented\n",
	    (unsigned short)cn_block->signal_data_type);
    exit(EXIT_FAILURE);
  }

  /* convert data */
  if(cc_block) {
    switch(cc_block->conversion_type) {
    case 0:
      if(cn_block->signal_data_type == 3) {
	converted_double = data_ieee754 * cc_block->supplement.linear.p2
	  +cc_block->supplement.linear.p1;
	/* printf("%lg -> %lg\n",data_ieee754,converted_double); */
      } else {
	converted_double = data_int64 * cc_block->supplement.linear.p2
	  +cc_block->supplement.linear.p1;
      }
      break;
    case 12:
      converted_double = (double)data_int64;
      break;
    default:
      fprintf(stderr,"conversion %hu not implemented\n",
	      (unsigned short)cc_block->conversion_type);
      exit(EXIT_FAILURE);
    }
  } else {
    switch(cn_block->signal_data_type) {
    case 0:
    case 1:
    case 7:
      converted_double = data_int64;
      break;
    case 2:
    case 3:
      converted_double = data_ieee754;
    default:
      assert(1);
    }
  }
  return converted_double;
}

