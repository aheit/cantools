/*  mdfmodel.h --  declarations for MDF model
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

#include <string.h>
#include "mdfmodel.h"

id_block_t *
id_block_get(const mdf_t *const mdf)
{
  return (id_block_t *)mdf->base;
}

hd_block_t *
hd_block_get(const mdf_t *const mdf)
{
  return (hd_block_t *)(mdf->base+64);
}

dg_block_t *
dg_block_get(const mdf_t *const mdf, const link_t lnk)
{
  if(lnk == 0) return NULL;
  return (dg_block_t *)(mdf->base+lnk);
}

cg_block_t *
cg_block_get(const mdf_t *const mdf, const link_t lnk)
{
  if(lnk == 0) return NULL;
  return (cg_block_t *)(mdf->base+lnk);
}

cn_block_t *
cn_block_get(const mdf_t *const mdf, const link_t lnk)
{
  if(lnk == 0) return NULL;
  return (cn_block_t *)(mdf->base+lnk);
}

ce_block_t *
ce_block_get(const mdf_t *const mdf, const link_t lnk)
{
  if(lnk == 0) return NULL;
  return (ce_block_t *)(mdf->base+lnk);
}

tx_block_t *
tx_block_get(const mdf_t *const mdf, const link_t lnk)
{
  if(lnk == 0) return NULL;
  return (tx_block_t *)(mdf->base + lnk);
}

const char *
tx_block_get_text(const mdf_t *const mdf, link_t lnk)
{
  if(lnk == 0) return NULL;
  return &((tx_block_t *)(mdf->base + lnk))->text1;
}

pr_block_t *
pr_block_get(const mdf_t *const mdf, const link_t lnk)
{
  if(lnk == 0) return NULL;
  return (pr_block_t *)(mdf->base + lnk);
}

dr_block_t *
dr_block_get(const mdf_t *const mdf, const link_t lnk)
{
  if(lnk == 0) return NULL;
  return (dr_block_t *)(mdf->base + lnk);
}

cc_block_t *
cc_block_get(const mdf_t *const mdf, const link_t lnk)
{
  if(lnk == 0) return NULL;
  return (cc_block_t *)(mdf->base + lnk);
}

char *
cn_get_long_name(const mdf_t *const mdf, const cn_block_t *const cn_block)
{
  const char *asam_name = tx_block_get_text(mdf, cn_block->link_asam_mcd_name);
  char *name;

  if(asam_name != NULL) {
    name = strdup(asam_name);
  } else {
    name = strndup(cn_block->signal_name,sizeof(cn_block->signal_name));
  }
  return name;
}

char *
ce_get_message_name(const ce_block_t *const ce_block)
{
  char *message;
  
  /* message info */
  if(ce_block != NULL) {
    switch(ce_block->extension_type) {
    case 19:
      message     = strndup(
	(const char *)ce_block->supplement.vector_can.message_name,
	sizeof(ce_block->supplement.vector_can.message_name));
      break;
    case 2:
      message     = strndup(
        (const char *)ce_block->supplement.dim.description,
        sizeof(ce_block->supplement.dim.description));
      break;
    default:
      message = strdup("(undef)");
      break;
    }
  } else {
    message = strdup("(undef)");
  }
  return message;
}

void
ce_get_message_info(const ce_block_t *const ce_block,
		    char **const message_name_ptr,
		    uint32_t *const can_id_ptr,
		    uint32_t *const can_channel_ptr)
{
  if(ce_block != NULL) {
    switch(ce_block->extension_type) {
    case 19:
      *can_id_ptr      = ce_block->supplement.vector_can.can_id;
      *can_channel_ptr = ce_block->supplement.vector_can.can_channel;
      break;
    case 2:
    default:
      *can_id_ptr      = 0;
      *can_channel_ptr = 0;
    }
    *message_name_ptr = ce_get_message_name(ce_block);
  } else {
    *can_id_ptr        = 0;
    *can_channel_ptr   = 0;
    *message_name_ptr     = strdup("(undef)");
  }
} 
