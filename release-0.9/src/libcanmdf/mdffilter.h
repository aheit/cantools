#ifndef INCLUDE_MDFFILTER_H
#define INCLUDE_MDFFILTER_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "mdfmodel.h"
#include "mdftypes.h"

struct filter_element_s {
  struct filter_element_s *next;
  char operation;
  uint32_t channel;
  uint8_t channel_wildcard;
  char *message;
  char *signal;
  char *newname;
};

typedef struct filter_element_s filter_element_t;

typedef struct {
  filter_element_t *first;
} filter_t;

extern char *
filter_apply(const filter_t *filter, const uint32_t channel,
	     const char *message, const char *signal);
extern int
filter_test_channel_group(const mdf_t *const mdf,
			  const filter_t *const filter,
			  const cg_block_t *const cg_block);
extern filter_t *
mdf_filter_create(const char *filename);
extern void
filter_free(filter_t *filter);

#endif
