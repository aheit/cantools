/*  mdfdg.c --  access MDF data groups
    Copyright (C) 2012-2015 Andreas Heitmann

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

#include "config.h"

#include <stdio.h>
#include "mdfmodel.h"
#include "mdffilter.h"
#include "mdfcg.h"

void
mdfProcessDataGroups(const mdf_t *const mdf, const filter_t *const filter,
		     link_t lnk, mdfSignalCb_t const mdfSignalCb,
		     const void *const cbData)
{
  dg_block_t *dg_block;
  dr_block_t *dr_block;
  uint8_t *data;
  int idg;

  for( dg_block = dg_block_get(mdf, lnk)                        , idg=0;
       dg_block;
       dg_block = dg_block_get(mdf, dg_block->link_next_dg_block), idg++) {
    if(mdf->verbose_level >= 2) {
      printf("DGBLOCK %d, nCG = %hu, nRec = %hu, offset=0x%lx\n",
	     idg,
	     (unsigned short)dg_block->number_channel_groups,
	     (unsigned short)dg_block->number_record_ids,
	     (unsigned long)dg_block->link_dr_block );
    }
    dr_block = dr_block_get(mdf, dg_block->link_dr_block);
    data = dr_block;

    switch(dg_block->number_record_ids) {
    case 0: /* sorted records */
      mdfProcessChannelGroupsSorted(mdf, filter, dg_block->link_cg_block,
				    dg_block->number_record_ids, data,
				    mdfSignalCb, cbData);
      break;
    case 1: /* unsorted records */
    case 2:
      mdfProcessChannelGroupsUnsorted(mdf, filter, dg_block->link_cg_block,
				      dg_block->number_record_ids, data,
				      mdfSignalCb, cbData);
      break;
    default:
      fprintf(stderr,"number_record_ids %hu not implemented\n",
	      (unsigned short)dg_block->number_record_ids);
      exit(EXIT_FAILURE);
    }
  }
}
