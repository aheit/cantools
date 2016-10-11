/*  test_mdfsg.c --  test signal conversion function
    Copyright (C) 2015 Andreas Heitmann

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

/* Check unit test tool header */
#include <check.h>

#include <stdio.h>
#include <assert.h>
#include "mdfsg.h"
#include "mdfmodel.h"

enum {
  BO_LITTLE=0,
  BO_BIG=1
} byte_order_e;
	
int main(void)
{
    return 0;
}

/* test, if payload is extracted correctly */

/*
 * machine endianess: implicit (need to test on both types of machines)
 * conversion type: linear (other types out of scope)
 * byte_order: L/B (byte order of input type)
 * first_bit: 0..7
 * number_bits: 1..64
 * signal_data_type: U/S (unsigned / signed int)
 * payload: 
 *   unsigned: 0, 1, 2, ..., 2^(number_bits-1)
 *     signed: 0, 1, 2, ..., 2^(number_bits-2)-1
 *               -1,-2, ...,-2^(number_bits-2)
 */
START_TEST(check_mdf_signal_convert)
{
  uint8_t testdata[16];
  mdf_t mdf;
  id_block_t id_block;
  cn_block_t cn_block;
  cc_block_t cc_block;
  uint64_t p,t;
  double res;
  int i,number_bits,number_bytes,first_bit;
  uint16_t mdf_endian;
  
#ifdef WORDS_BIGENDIAN
  const int host_endian = 1;
#else
  const int host_endian = 0;
#endif

  printf("host_endian = %d (%s)\n",host_endian,host_endian?"big":"little");

  /*  */
  cn_block.signal_data_type = sdt_unsigned_int_big_endian;
  /* */
  cc_block.conversion_type = 0;
  cc_block.supplement.linear.p2 = 1;
  cc_block.supplement.linear.p1 = 0;
  /* */
  mdf.base = (uint8_t *)&id_block;
  cn_block.link_conversion_formula = (uint8_t *)&cc_block-mdf.base;

  /* test unsigned */

  /*
   * file byte order
   * LITTLE_ENDIAN (0) - Intel Byte Order
   * BIG_ENDIAN    (1) - Motorola Byte Order
   */
  for(mdf_endian = 0;mdf_endian <= 1; mdf_endian++) {
    for(number_bits = 1;number_bits <= 64; number_bits++) {
      for(first_bit = 0;first_bit < 8; first_bit++) {
	p = 1;

	do { /* loop payload */
	  number_bytes = ((number_bits + first_bit) + 7)/8;

	  /* apply the bit offset, copy to buffer */
	  if(first_bit != 0) {/* some systems do not shift by 0 correctly */
	    t = p << first_bit; 
	  } else {
	    t = p;
	  }

	  /* copy buffer to testdata array */
	  if(host_endian == BO_LITTLE) { 
	    if(mdf_endian == BO_LITTLE) {
	      for(i = 0; i < number_bytes; i++) {
		/* 012... */  /* 012... */
		testdata[i] = ((uint8_t *)&t)[i];
	      }
	    } else { /* host_endian = BO_LITTLE; mdf_endian == BO_BIG */
	      for(i = 0; i < number_bytes; i++) {
		testdata[number_bytes-i-1] = ((uint8_t *)&t)[i];
	      }
	    }
	  } else { /* host_endian == BO_BIG */
	    if(mdf_endian == BO_LITTLE) {
	      for(i = 0; i < number_bytes; i++) {
		testdata[i] = ((uint8_t *)&t)[7-i];
	      }
	    } else { /* mdf_endian == BO_BIG */
	      for(i = 0; i < number_bytes; i++) {
		testdata[number_bytes-i-1] = ((uint8_t *)&t)[7-i];
	      }
	    }
	  }
      
	  id_block.byte_order = mdf_endian;
	  cn_block.first_bit = first_bit;
	  cn_block.number_bits = number_bits;
	  cn_block.signal_data_type = sdt_unsigned_int_default;

	  if(first_bit + number_bits <= 64) {
	    res = mdf_signal_convert(testdata, &mdf, &cn_block);
	    printf("bo = %d (%s), "
		   "n_bytes = %d, n_bits = %d, first_bit = %d, "
		   "p = %llu, res = %.1lf\n",
		   mdf_endian, mdf_endian==BO_LITTLE?"L":"B",
		   number_bytes, number_bits, first_bit,
		   p, res);
	    ck_assert(p == res);

	    if(p != res) {
	      for(i=0;i<16;i++) {
		printf("%02x ",testdata[i]);
	      }
	      puts("");
	    }
	  }
	  p <<= 1;
	  if(number_bits<64) {
	    p &= (1ULL<<number_bits)-1ULL;
	  }
	} while(p!=0);
      }
    }
  }
}
END_TEST
