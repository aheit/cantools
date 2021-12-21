#ifndef INCLUDE_MDFDG_H
#define INCLUDE_MDFDG_H

/*  mdfdg.h -- declarations for MDF data groups
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

#include "cantools_config.h"

#include "mdfmodel.h"

#ifdef __cplusplus
extern "C" {
#endif

void mdfProcessDataGroups(const mdf_t *const mdf, const filter_t *const filter,
                          link_t link, mdfSignalCb_t const mdfSignalCb,
                          const void *const cbData);

#ifdef __cplusplus
}
#endif

#endif
