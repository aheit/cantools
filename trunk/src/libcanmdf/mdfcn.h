/*  mdfunsorted.h -- process unsorted MDF file
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

#ifndef INCLUDE_MDFUNSORTED_H
#define INCLUDE_MDFUNSORTED_H

#include "config.h"

#include "mdfmodel.h"
#include "mdffilter.h"
#include "mdfsg.h"

void
mdfProcessChannel(const mdf_t *const mdf,
		  const cg_block_t *const cg_block,
		  const cn_block_t *const cn_block,
		  const filter_t *const filter,
		  const double *const time,
		  const double *const value,
		  mdfSignalCb_t const mdfSignalCb,
		  const void *const cbData);
void
mdfProcessChannelsSorted(const mdf_t *const mdf,
			 const filter_t *const filter,
			 link_t link,
			 uint32_t number_of_records,
			 uint16_t number_record_ids,
			 uint16_t record_size,
			 uint8_t *data_base,
			 mdfSignalCb_t const mdfSignalCb,
			 const void *const cbData);

#endif
