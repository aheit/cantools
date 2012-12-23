#ifndef INCLUDE_MDFMODEL_H
#define INCLUDE_MDFMODEL_H

#include <stdlib.h>
#include <sys/mman.h> /* off_t */
#include "mdftypes.h"

#if WITH_DMALLOC
#include <dmalloc.h>
#endif

#define CREATE(type,obj) type *(obj) = (type *)malloc(sizeof(type))

/* mdf */
typedef struct {
  int fd;
  uint8_t *base;
  off_t size;
  int verbose_flag;   /* verbose reporting: 0=none, 1=brief, 2=verbose */
} mdf_t;

typedef struct {
  char_t   file_identifier[8];
  char_t   format_identifier[8];
  char_t   program_identifier[8];
  uint16_t byte_order;            /* 0 = little endian */
  uint16_t floating_point_format; /* 0 = IEEE754 */
  uint16_t version_number;
  uint16_t reserved1;
  char_t   reserved2[2];
  char_t   reserved3[30];
} id_block_t;

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
  /* 022 */ uint32_t number_of_records      __attribute__ ((packed));
  /* 026 */ link_t   sample_reduction_block __attribute__ ((packed));
} cg_block_t;

typedef struct {
  /* 000 */ char_t   block_identifier[2];
  /* 002 */ uint16_t block_size;
  /* 004 */ mdf_bool_t value_range_valid;
  /* 006 */ real_t   value_min               __attribute__ ((packed));
  /* 014 */ real_t   value_max               __attribute__ ((packed));
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
  } supplement  __attribute__ ((packed));
} cc_block_t;

typedef struct {
  /* 000 */ char_t   block_identifier[2];
  /* 002 */ uint16_t block_size;
  /* 004 */ link_t   link_next_cn_block;
  /* 008 */ link_t   link_conversion_formula;
  /* 012 */ link_t   link_extensions;
  /* 016 */ link_t   link_dependency;
  /* 020 */ link_t   link_channel_comment;
  /* 024 */ uint16_t channel_type;            /* 0=data, 1=time */
  /* 026 */ char_t   signal_name[32];
  /* 058 */ char_t   signal_description[128];
  /* 186 */ uint16_t first_bit;               /* 0..7 */
  /* 188 */ uint16_t number_bits;
  /* 190 */ uint16_t signal_data_type; /* 0=uint, 1=sint, 2,3=IEEE754, 7=str, 8=array*/
  /* 192 */ mdf_bool_t value_range_valid;
  /* 194 */ real_t   value_min               __attribute__ ((packed));
  /* 202 */ real_t   value_max               __attribute__ ((packed));
  /* 210 */ real_t   sample_rate             __attribute__ ((packed));
  /* 218 */ link_t   link_asam_mcd_name      __attribute__ ((packed));
  /* 222 */ link_t   link_display_identifier __attribute__ ((packed));
  /* 226 */ uint16_t additional_byte_offset;
} cn_block_t;

typedef struct {
  /* 000 */ char_t   block_identifier[2];
  /* 002 */ uint16_t block_size;
  /* 004 */ uint16_t extension_type; /* 2=DIM, 19=Vector CAN */
  union {
    struct {
      uint32_t can_id                        __attribute__ ((packed));
      uint32_t can_channel                   __attribute__ ((packed));
      char_t   message_name[36];
      char_t   sender_name[36];
    } vector_can;
    struct {
      uint16_t module_number;
      uint32_t address                       __attribute__ ((packed));
      char_t   description[80];
      char_t   ecu_identification[32];
    } dim;
  } supplement;
} ce_block_t;

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
const char *cn_get_long_name(const mdf_t *const mdf, const cn_block_t *const cn_block);

#endif
