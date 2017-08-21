#ifndef INCLUDE_MDFSG_H
#define INCLUDE_MDFSG_H

/*  mdfsg.h -- signal callback function
    Copyright (C) 2012-2017 Andreas Heitmann

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
# include "config.h"
#endif

#ifdef HAVE_INTTYPES_H
# include <inttypes.h>
#endif
#ifdef HAVE_STDINT_H
# include <stdint.h>
#endif

#include "mdfmodel.h"
#include "mdffilter.h"

/* convert signal to double value */
double mdf_signal_convert(const uint8_t *const data_int_ptr,
			  const mdf_t *const mdf,
			  const cn_block_t *const cn_block);

/* signal callback function */
typedef void (* mdfSignalCb_t)(const mdf_t *const mdf, 
			       const uint32_t can_channel,
			       const uint32_t number_of_records,
			       const uint16_t channel_type,
			       const char_t *const message,
			       const char_t *const name,
			       const double *const timeValue,
			       const filter_t *const filter,
			       const void *const cbData);
#endif
