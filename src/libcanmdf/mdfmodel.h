#ifndef INCLUDE_MDFMODEL_H
#define INCLUDE_MDFMODEL_H

/*  mdfmodel.h --  declarations for MDF model
    Copyright (C) 2012-2021 Andreas Heitmann

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

#include <stdlib.h>
#include <sys/mman.h> /* off_t */
#include "mdftypes.h"

#if WITH_DMALLOC
#include <dmalloc.h>
#endif

#define CREATE(type,obj) type *(obj) = (type *)malloc(sizeof(type))

#pragma pack(1)
/* mdf */
typedef struct {
  int fd;
  uint8_t *base;
  off_t size;
  int verbose_level;   /* verbose level: 0=none, 1=brief, 2=verbose */
} mdf_t;

typedef struct {
  char_t   file_identifier[8];
  char_t   format_identifier[8];
  char_t   program_identifier[8];
  uint16_t byte_order;            /* 0 = little endian */
  uint16_t floating_point_format; /* 0 = IEEE754 */
  uint16_t version_number;
  /* valid since version 3.30: */
  uint16_t code_page_number;
  char_t   reserved1[2];
  char_t   reserved2[26];
  uint16_t standard_flags;
  uint16_t custom_flags;
} id_block_t;

typedef enum {
  id_block_standard_flags_update_of_record_counters_required = 1,
  id_block_standard_flags_update_of_reduces_samples_counters_required = 2,
} id_block_standard_flags_t;

typedef struct {
  char_t   block_identifier[2];
  uint16_t block_size;
  link_t   link_dg_block;
  link_t   link_tx_block;
  link_t   link_pr_block;
  uint16_t number_data_groups;
  char_t   recording_date[10];
  char_t   recording_time[8];
  char_t   author[32];
  char_t   organization[32];
  char_t   project[32];
  char_t   measurement_id[32];
} hd_block_t;

typedef struct {
  char_t   block_identifier[2];
  uint16_t block_size;
  char_t   text1;
} tx_block_t;

typedef struct {
  char_t   block_identifier[2];
  uint16_t block_size;
  char_t    data1;
} pr_block_t;

typedef uint8_t dr_block_t;

typedef struct {
  char_t   block_identifier[2];
  uint16_t block_size;
  link_t   link_next_dg_block;
  link_t   link_cg_block;
  link_t   link_reserved;
  link_t   link_dr_block;
  uint16_t number_channel_groups;
  uint16_t number_record_ids;
} dg_block_t;

typedef struct {
  /* 000 */ char_t   block_identifier[2];
  /* 002 */ uint16_t block_size;
  /* 004 */ link_t   link_next_cg_block;
  /* 008 */ link_t   link_cn_block;
  /* 012 */ link_t   link_comment;
  /* 016 */ uint16_t record_id;
  /* 018 */ uint16_t number_channels;
  /* 020 */ uint16_t record_size;
  /* 022 */ uint32_t number_of_records;
  /* valid since version 3.30: */
  /* 026 */ link_t   sample_reduction_block;
} cg_block_t;

typedef struct {
  /* 000 */ char_t   block_identifier[2];
  /* 002 */ uint16_t block_size;
  /* 004 */ mdf_bool_t value_range_valid;
  /* 006 */ real_t   value_min;
  /* 014 */ real_t   value_max;
  /* 022 */ char_t   physical_unit[20];
  /* 042 */ uint16_t conversion_type;
  /* 044 */ uint16_t size_information;
  /* additional_conversion_data */
  union {
    struct {
      /* 046 */ real_t   p1;
      /* 054 */ real_t   p2;
    } linear;
    struct {
      real_t   p1;
      real_t   p2;
      real_t   p3;
      real_t   p4;
      real_t   p5;
      real_t   p6;
    } polynomial;
    struct {
      struct {
        real_t   int_value;
        real_t   phys_value;
      } array[1];       /* n times */
    } tabular;
    struct {
      real_t   p1;
      real_t   p2;
      real_t   p3;
      real_t   p4;
      real_t   p5;
      real_t   p6;
      real_t   p7;
    } exponential;
    struct {
      real_t   p1;
      real_t   p2;
      real_t   p3;
      real_t   p4;
      real_t   p5;
      real_t   p6;
      real_t   p7;
    } logarithmic;
    struct {
      real_t   p1;
      real_t   p2;
      real_t   p3;
      real_t   p4;
      real_t   p5;
      real_t   p6;
    } rational;
    struct {
      char_t   text_formula[256];
    } asam_mcd2_formula;
    struct {
      struct {
        real_t   int_value;
        char_t   assigned_text[32];
      } array[1];       /* n times */
    } asam_mcd2_text_table;
    struct {
      real_t   undef1;
      real_t   undef2;
      link_t   default_text;
      struct {
        real_t   lower_range;
        real_t   upper_range;
        link_t   text;
      } array[1];       /* n times */
    } asam_mcd2_text_range_table;
    struct {
      uint16_t   ms;
      uint8_t    min;
      uint8_t    hour;
      uint8_t    day;
      uint8_t    month;
      uint8_t    year;
    } date;
    struct {
      uint32_t   ms;
      uint16_t   days;
    } time;
  } supplement;
} cc_block_t;

typedef enum {
  sdt_unsigned_int_default   = 0,
  sdt_signed_int_default     = 1,
  sdt_ieee754_float_default  = 2,
  sdt_ieee754_double_default = 3,
  sdt_vax_f_float    = 4,
  sdt_vax_g_float    = 5,
  sdt_vax_d_float    = 6,
  sdt_string         = 7,
  sdt_byte_array     = 8,
  sdt_unsigned_int_big_endian   = 9,
  sdt_signed_int_big_endian     = 10,
  sdt_ieee754_float_big_endian  = 11,
  sdt_ieee754_double_big_endian = 12,
  sdt_unsigned_int_little_endian   = 13,
  sdt_signed_int_little_endian     = 14,
  sdt_ieee754_float_little_endian  = 15,
  sdt_ieee754_double_little_endian = 16,
} signal_data_type_t;

typedef struct {
  /* 000 */ char_t   block_identifier[2];
  /* 002 */ uint16_t block_size;
  /* 004 */ link_t   link_next_cn_block;
  /* 008 */ link_t   link_conversion_formula;
  /* 012 */ link_t   link_extensions;
  /* 016 */ link_t   link_dependency;
  /* 020 */ link_t   link_channel_comment;
  /* 024 */ uint16_t channel_type;            /* 0=data, 1=time */
  /* 026 */ char32_t signal_name;
  /* 058 */ char128_t signal_description;
  /* 186 */ uint16_t first_bit;               /* 0..7 */
  /* 188 */ uint16_t number_bits;
  /* 190 */ uint16_t signal_data_type;
  /* 192 */ mdf_bool_t value_range_valid;
  /* 194 */ real_t   value_min;
  /* 202 */ real_t   value_max;
  /* 210 */ real_t   sample_rate;
  /* valid since version 2.12: */
  /* 218 */ link_t   link_asam_mcd_name;
  /* valid since version 3.00: */
  /* 222 */ link_t   link_display_identifier;
  /* valid since version 3.00: */
  /* 226 */ uint16_t additional_byte_offset;
} cn_block_t;

typedef struct {
  /* 000 */ char_t   block_identifier[2];
  /* 002 */ uint16_t block_size;
  /* extension type:
   *  2 MDF_CE_TYPE_DIM      DIM (CCP/XCP)
   * 19 MDF_CE_TYPE_VCN      Vector CAN
   */
  /* 004 */ uint16_t extension_type;
  union {
    struct { /* type 2 */
      uint16_t module_number;
      uint32_t address;
      char80_t description[80];
      char32_t ecu_identification[32];
    } dim;
    struct { /* type 19 */
      uint32_t can_id;
      uint32_t can_channel;
      char36_t message_name[36];
      char36_t sender_name[36];
    } vector_can;
  } supplement;
} ce_block_t;
#pragma pack()

id_block_t *id_block_get(const mdf_t *const mdf);
hd_block_t *hd_block_get(const mdf_t *const mdf);
dg_block_t *dg_block_get(const mdf_t *const mdf, const link_t lnk);
cg_block_t *cg_block_get(const mdf_t *const mdf, const link_t lnk);
cn_block_t *cn_block_get(const mdf_t *const mdf, const link_t lnk);
ce_block_t *ce_block_get(const mdf_t *const mdf, const link_t lnk);
tx_block_t *tx_block_get(const mdf_t *const mdf, const link_t lnk);
const char *tx_block_get_text(const mdf_t *const mdf, link_t lnk);
pr_block_t *pr_block_get(const mdf_t *const mdf, const link_t lnk);
dr_block_t *  dr_block_get(const mdf_t *const mdf, const link_t lnk);
cc_block_t *  cc_block_get(const mdf_t *const mdf, const link_t lnk);
char *cn_get_long_name(const mdf_t *const mdf, const cn_block_t *const cn_block);
char *ce_get_message_name(const ce_block_t *const ce_block);
void ce_get_message_info(const ce_block_t *const ce_block,
                         char **const message_name_ptr,
                         uint32_t *const can_id,
                         uint32_t *const can_channel);

#endif
