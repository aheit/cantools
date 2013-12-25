#ifndef INCLUDE_MDFFILTER_H
#define INCLUDE_MDFFILTER_H

/*  mdffilter.h --  declarations for MDF filter
    Copyright (C) 2012,2013 Andreas Heitmann

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
