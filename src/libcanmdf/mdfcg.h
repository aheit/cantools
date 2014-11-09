/*  mdfcg.h -- access MDF channel groups
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

#ifndef INCLUDE_MDFCG_H
#define INCLUDE_MDFCG_H

#include "config.h"

#include "mdfmodel.h"
#include "mdffilter.h"
#include "mdfsg.h"

#ifdef __cplusplus
extern "C" {
#endif

/* find time channel of channel group */
cn_block_t *
find_time_channel(mdf_t *mdf, cg_block_t *cg_block);

/* loop over all channel groups */
void
mdfProcessChannelGroupsUnsorted(const mdf_t *const mdf,
				const filter_t *const filter,
				const link_t cglink,
				const uint16_t number_record_ids,
				const uint8_t *const data_base,
				mdfSignalCb_t const mdfSignalCb,
				const void *const cbData);

void
mdfProcessChannelGroupsSorted(const mdf_t *const mdf,
			      const filter_t *const filter,
			      link_t link,
			      uint16_t number_record_ids,
			      uint8_t *data,
			      mdfSignalCb_t const mdfSignalCb,
			      const void *const cbData);

#ifdef __cplusplus
}
#endif


#endif
