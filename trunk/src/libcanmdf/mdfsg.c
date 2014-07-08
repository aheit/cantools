/*  mdfsg.c --  access MDF signal groups
    Copyright (C) 2012-2014 Andreas Heitmann

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
#include <endian.h>
#include <byteswap.h>
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
  uint16_t default_byte_order_big_endian = id_block_get(mdf)->byte_order;
  const sdt = cn_block->signal_data_type;
  const int cn_is_big_endian =
       (sdt == sdt_unsigned_int_big_endian)
    || (sdt == sdt_signed_int_big_endian)
    || (sdt == sdt_ieee754_float_big_endian)
    || (sdt == sdt_ieee754_double_big_endian)
    || (default_byte_order_big_endian &&
        (   (sdt == sdt_unsigned_int_default)
         || (sdt == sdt_signed_int_default)
         || (sdt == sdt_ieee754_float_default)
         || (sdt == sdt_ieee754_double_default)));
  /* swap words if channel endianess differs from machine endianess */
#ifdef WORDS_BIGENDIAN
  const int swap = !cn_is_big_endian;
#else
  const int swap = cn_is_big_endian;
#endif

  /* extract data */
  switch(sdt) {
  case sdt_unsigned_int_default:
  case sdt_unsigned_int_big_endian:
  case sdt_unsigned_int_little_endian:
    if(number_bits == 1) {
      data_int64 = ((*(uint8_t *)data_int_ptr) >> bit_offset) & 1;
    } else if(number_bits <= 9) {
      data_int64 = ((*(uint16_t *)data_int_ptr) >> bit_offset)
        & ((1u<<number_bits)-1u);
      if(number_bits>8) {
        if(swap) {
          /*
          printf("UI %04x (%d,%d,%d,%d,%d)\t",*(uint16_t *)data_int_ptr,
                 number_bits, bit_offset, sdt, cn_is_big_endian, swap);
          */
          data_int64 = bswap_16(*(uint16_t *)&data_int64);
          /*
          printf("-> %016llx\n", data_int64);
          */
        }
      }
    } else if(number_bits <= 25) {
      data_int64 = ((*(uint32_t *)data_int_ptr) >> bit_offset)
        & ((1u<<number_bits)-1u);
      if(swap) {
        /*
        printf("UI %08x (%d,%d,%d,%d,%d)\t",*(uint32_t *)data_int_ptr,
               number_bits, bit_offset, sdt, cn_is_big_endian, swap);
        */
        if(number_bits > 16) {
          data_int64 = bswap_32(*(uint32_t *)&data_int64);
        } else {
          data_int64 = bswap_16(*(uint16_t *)&data_int64);
        }
        /*
        printf("-> %016llx\n", data_int64);
        */
      }
    } else {
      assert(bit_offset + number_bits <= 64);
      data_int64 = ((*(uint64_t *)data_int_ptr) >> bit_offset)
        & (((uint64_t)1<<number_bits)-(uint64_t)1);
      if(swap) {
        /*
        printf("UI %16llx (%d,%d,%d,%d,%d)\t",*(uint64_t *)data_int_ptr,
               number_bits, bit_offset, sdt, cn_is_big_endian, swap);
        */
        if(number_bits>32) {
          data_int64 = bswap_64(*(uint64_t *)&data_int64);
        } else {
          data_int64 = bswap_32(*(uint32_t *)&data_int64);
        }
        /*
        printf("-> %016llx\n", data_int64);
        */
      } 
    }
    break;
  case sdt_signed_int_default:
  case sdt_signed_int_big_endian:
  case sdt_signed_int_little_endian:
    if(number_bits <= 9) {
      data_int64  =
          (int64_t)(((int16_t)
                     ((*(uint16_t *)data_int_ptr)
                      << (16-number_bits-bit_offset)))
                    >>(16-number_bits));
      if(number_bits>8) {
        if(swap) {
          data_int64 = bswap_16(*(uint16_t *)&data_int64);
        } else {
        }
      }
    } else if(number_bits <= 25) {
      uint32_t data_u32;

      data_u32 = ((*(uint32_t *)data_int_ptr) << (32-number_bits-bit_offset));
      if(swap) {
        if(number_bits > 16) {
          data_u32 = bswap_32(*(uint32_t *)&data_u32);
        } else {
          data_u32 = bswap_16(*(uint16_t *)&data_u32);
        }
      }
      data_int64 = (int64_t)(((int32_t)data_u32) >> (32-number_bits));
      /*
        printf("SI16 %08lx %d %d %d %d -> %016llx\n",*(uint32_t *)data_int_ptr,
               number_bits, bit_offset, cn_is_big_endian, swap, data_int64);
      */
    } else {
      uint64_t data_u64;

      assert(bit_offset + number_bits <= 64);
      data_u64 = ((*(uint64_t *)data_int_ptr)
                  << (64-number_bits-bit_offset));
      if(swap) {
        if(number_bits>32) {
          data_u64 = bswap_64(*(uint64_t *)&data_u64);
          data_int64 = (int64_t)(((int64_t)data_u64) >> (64-number_bits));
        } else {
          data_u64 = bswap_32(*(((uint32_t *)&data_u64)+1));
          data_int64 = (int64_t)(((int32_t)data_u64) >> (32-number_bits));
        }
      } else {
        data_int64 = (int64_t)(((int64_t)data_u64) >> (64-number_bits));
      }
    }
    break;
  case sdt_ieee754_float_default:
  case sdt_ieee754_float_big_endian:
  case sdt_ieee754_float_little_endian:
    {
      uint32_t data_u32 = *(uint32_t *)data_int_ptr;
      if(swap) {
         data_u32 = bswap_32(*(uint32_t *)&data_u32);
      }
      data_ieee754 = *(float *)&data_u32;
      /*
        printf("FLOAT (%d) 0x%x %d 0x%x %g\n", sdt, *(uint32_t *)data_int_ptr, swap, data_u32,  data_ieee754);
      */
    }
    break;
  case sdt_ieee754_double_default:
  case sdt_ieee754_double_big_endian:
  case sdt_ieee754_double_little_endian:
    {
      uint64_t data_u64 = *(uint64_t *)data_int_ptr;
      if(swap) {
         data_u64 = bswap_64(*(uint64_t *)&data_u64);
      }
      data_ieee754 = *(double *)&data_u64;
      /* 
      printf("DOUBLE (%d) 0x%llx %d 0x%llx %lg\n", sdt, *(uint64_t *)data_int_ptr, swap, data_u64,  data_ieee754);
      */
    }
    break;
  case sdt_string: /* string */
    data_int64 = 0;
    break;
  default:
    fprintf(stderr,"signal_data_type %hu not implemented\n",
            (unsigned short)sdt);
    exit(EXIT_FAILURE);
  }

  /* convert data */
  if(cc_block) {
    switch(cc_block->conversion_type) {
    case 0:
      switch(sdt) {
      case sdt_unsigned_int_default:
      case sdt_signed_int_default:
      case sdt_string:
      case sdt_unsigned_int_big_endian:
      case sdt_signed_int_big_endian:
        converted_double = data_int64 * cc_block->supplement.linear.p2
          +cc_block->supplement.linear.p1;
        /* printf("%ld -> %lg\n",data_int64,converted_double); */
        break;
      case sdt_ieee754_float_default:
      case sdt_ieee754_float_big_endian:
      case sdt_ieee754_float_little_endian:
      case sdt_ieee754_double_default:
      case sdt_ieee754_double_big_endian:
      case sdt_ieee754_double_little_endian:
        converted_double = data_ieee754 * cc_block->supplement.linear.p2
                         + cc_block->supplement.linear.p1;
        break;
      default:
        assert(1);
      }
      break;
    case 12:
      converted_double = (double)data_int64;
      break;
    default:
      converted_double = 0.0;
      fprintf(stderr,"conversion %hu not implemented\n",
              (unsigned short)cc_block->conversion_type);
      exit(EXIT_FAILURE);
    }
  } else {
    switch(sdt) {
      case sdt_unsigned_int_default:
      case sdt_signed_int_default:
      case sdt_string:
      case sdt_unsigned_int_big_endian:
      case sdt_signed_int_big_endian:
      converted_double = data_int64;
      break;
    case sdt_ieee754_float_default:
    case sdt_ieee754_double_default:
    case sdt_ieee754_float_big_endian:
      converted_double = data_ieee754;
      break;
    default:
      assert(1);
    }
  }
  /* printf("CD %lg\n",converted_double); */
  return converted_double;
}

