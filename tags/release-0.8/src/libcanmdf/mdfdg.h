#ifndef INCLUDE_MDFDG_H
#define INCLUDE_MDFDG_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "mdfmodel.h"

void mdfProcessDataGroups(const mdf_t *const mdf, filter_t *filter, link_t link, 
			  mdfSignalCb_t const mdfSignalCb, void *const cbData);

#endif
