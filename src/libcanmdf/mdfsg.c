/*  mdfsg.c -- access MDF signal groups
    Copyright (C) 2012-2020 Andreas Heitmann

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

#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include "mdfswap.h"
#include "mdfsg.h"
#include "mdfmodel.h"

static double dataToDouble(signal_data_type_t sdt,
                           int64_t data_int64,
                           double data_ieee754)
{
  double x;
  
  switch(sdt) {
  case sdt_unsigned_int_default:
  case sdt_unsigned_int_big_endian:
  case sdt_string:
    x = (double)(uint64_t)data_int64;
    break;
  case sdt_signed_int_default:
  case sdt_signed_int_big_endian:
    x = (double)data_int64;
    break;
  case sdt_ieee754_float_default:
  case sdt_ieee754_float_big_endian:
  case sdt_ieee754_float_little_endian:
  case sdt_ieee754_double_default:
  case sdt_ieee754_double_big_endian:
  case sdt_ieee754_double_little_endian:
    x = data_ieee754;
    break;
  default:
    x = 0;
    assert(1);
  }
  return x;
}

/* convert signal to double value */
double
mdf_signal_convert(const uint8_t *const data_int_ptr,
                   const mdf_t *const mdf,
                   const cn_block_t *const cn_block)
{
  /* position of LSB within first byte: 0..7 */
  uint8_t bit_offset = cn_block->first_bit%8;
  cc_block_t *cc_block = cc_block_get(mdf,
                                      cn_block->link_conversion_formula);
  double converted_double;
  int64_t data_int64;
  double data_ieee754;
  uint16_t number_bits = cn_block->number_bits;
  uint16_t number_of_signal_bytes = (bit_offset + number_bits + 7)/8;
  uint16_t default_byte_order_big_endian = id_block_get(mdf)->byte_order;
  const signal_data_type_t sdt = cn_block->signal_data_type;
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
  const int cn_is_signed_int = 
       (sdt == sdt_signed_int_default)
    || (sdt == sdt_signed_int_big_endian)
    || (sdt == sdt_signed_int_little_endian);
 
  /* swap words if channel endianess differs from machine endianess */
#ifdef WORDS_BIGENDIAN
  const int swap = !cn_is_big_endian;
#else
  const int swap = cn_is_big_endian;
#endif

  /* extract data */
  switch(sdt) {
  case sdt_signed_int_default:
  case sdt_signed_int_big_endian:
  case sdt_signed_int_little_endian:
    /*
     *  NOTE: the MDF specification allows 1-bit signed ints. In this case,
     *  unset bits are mapped to 0 and set bits are mapped to -1.
     */
    /* FALLTHROUGH (to decode signal) */
  case sdt_unsigned_int_default:
  case sdt_unsigned_int_big_endian:
  case sdt_unsigned_int_little_endian:
    /* copy and swap bytes if required */
    {
      uint8_t *dp = (uint8_t *)&data_int64;
      const uint8_t *sp;
      uint8_t i = number_of_signal_bytes;

      data_int64 = 0;
      if(swap) {
        for(sp = &data_int_ptr[number_of_signal_bytes-1]; i>0; i--) {
          *dp++ = *sp--;
        }
      } else {
        for(sp = data_int_ptr; i>0; i--) {
          *dp++ = *sp++;
        }
      }
    }

    /* shift result */
    if(bit_offset > 0) {
      data_int64 >>= bit_offset;
    }

    /* mask result */
    if(number_bits < 64) {
      if(cn_is_signed_int) {
        /* 64 bit sign extension */
        data_int64 <<= 64-number_bits;

        /*
         * per ISO/IEC 9899:1999, section 6.5.7, the result of a right
         * shift operation with negative first operand is
         * implementation dependent. check with autoconf, if we can
         * use arithmetic right shift or if we need to emulate it.
         */
#ifdef AX_C_ARITHMETIC_RSHIFT
        data_int64 >>= 64-number_bits;
#else
        data_int64 = (int64_t) (
          /* do a logical shift right */
         (((uint64_t)data_int64) >> (64-number_bits))
          /* add the leading 1-bits */
          |
         ((data_int64<0)?~(~0ULL >> (64-number_bits)):0));
#endif
      } else {
        data_int64 &= ((1ULL<<number_bits)-1ULL);
      }
    }
    break;
  case sdt_ieee754_float_default:
  case sdt_ieee754_float_big_endian:
  case sdt_ieee754_float_little_endian:
    {
      uint32_t data_u32 = *(uint32_t *)data_int_ptr;

      if(swap) {
         data_u32 = mdf_bswap_32(*(uint32_t *)&data_u32);
      }
      data_ieee754 = *(float *)&data_u32;
    }
    break;
  case sdt_ieee754_double_default:
  case sdt_ieee754_double_big_endian:
  case sdt_ieee754_double_little_endian:
    {
      uint64_t data_u64 = *(uint64_t *)data_int_ptr;

      if(swap) {
         data_u64 = mdf_bswap_64(*(uint64_t *)&data_u64);
      }
      data_ieee754 = *(double *)&data_u64;
    }
    break;
  case sdt_string: /* string type not yet implemented */
    data_int64 = 0;
    break;
  case sdt_byte_array:  /* byte array type not yet implemented */
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
    case 0: /* parametric, linear */
      {
        const double x = dataToDouble(sdt,data_int64,data_ieee754);
        converted_double = x
          * cc_block->supplement.linear.p2
          + cc_block->supplement.linear.p1;
      }
      break;
    case 1: /* 3.12.4 CCBLOCK – Tabular, with Interpolation */
      {
        const uint32_t n = cc_block->size_information;
        const double x = dataToDouble(sdt, data_int64, data_ieee754);
        uint32_t i;

        switch(n) {
        case 0:
          fprintf(stderr, "Warning: empty table in lookup. Physical value set to 0.0\n");
          converted_double = 0.0;
          break;
        case 1:
          converted_double = cc_block->supplement.tabular.array[0].phys_value;
          break;
        default:
          if(x < cc_block->supplement.tabular.array[0].int_value) {
            /* Is x < than Int value 1, Physvalue 1 will be returned. */
            converted_double = cc_block->supplement.tabular.array[0].phys_value;
          } else {
            /* If a value x is located between two table values,
               (tablevalue[i] ≤ x < tablevalue[i+1]), linear
               interpolation between physvalue[i] and physvalue[i+1] is
               used. */
            for(i = 0; i < n-1; i++) {
              if(x < cc_block->supplement.tabular.array[i+1].int_value) {
                double x0 = cc_block->supplement.tabular.array[i].int_value;
                double x1 = cc_block->supplement.tabular.array[i+1].int_value;
                double y0 = cc_block->supplement.tabular.array[i].phys_value;
                double y1 = cc_block->supplement.tabular.array[i+1].phys_value;
                converted_double = y0 + (y1-y0)*(x-x0)/(x1-x0);
                /* printf("TABULAR %lf @ (%lf,%lf) -> (%lf,%lf) = %lf\n", */
                /*             x,x0,x1,y0,y1,converted_double); */
                break;
              }
            } /* end for */
            /* If x is larger than or equal to the greatest Int value, Phys value n will be returned. */
            if(i == n-1) {
              converted_double = cc_block->supplement.tabular.array[n-1].phys_value;
            }
          } /* end case between two values */
          break;
        } /* switch(n) */
      } /* end tabular with interpolation */
      break;
    case 9: /* rational conversion */
      {
        const double x = dataToDouble(sdt, data_int64, data_ieee754);
        const double p1 = cc_block->supplement.rational.p1;
        const double p2 = cc_block->supplement.rational.p2;
        const double p3 = cc_block->supplement.rational.p3;
        const double p4 = cc_block->supplement.rational.p4;
        const double p5 = cc_block->supplement.rational.p5;
        const double p6 = cc_block->supplement.rational.p6;
        const double denom = x*(x*p4+p5)+p6;
        if(denom != 0) {
          const double nom = x*(x*p1+p2)+p3;
          converted_double = nom / denom;
        } else {
          converted_double = 0;
        }
      }      
      break;
    case 11: /* text table lookup. use raw value for now */
      converted_double = (double)data_int64;
      break;
    case 12:
      converted_double = (double)data_int64;
      break;
    case 65535: /* 65535 = 1:1 conversion formula (Int = Phys) */
      converted_double = dataToDouble(sdt, data_int64, data_ieee754);
      break;
    default:
      converted_double = 0.0;
      fprintf(stderr,"conversion %hu not implemented\n",
              (unsigned short)cc_block->conversion_type);
      exit(EXIT_FAILURE);
    }
  } else {
    converted_double = dataToDouble(sdt, data_int64, data_ieee754);
  }
  return converted_double;
}

