#ifndef INCLUDE_BLFREADER_H
#define INCLUDE_BLFREADER_H

/*  blfreader.h --  declarations for blfReader
    Copyright (C) 2016-2017 Andreas Heitmann

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

#ifdef HAVE_INTTYPES_H
# include <inttypes.h>
#endif
#ifdef HAVE_STDINT_H
# include <stdint.h>
#endif

#include <stdio.h>

#include "dbctypes.h"
#include "measurement.h"

/* blfRead function */
void blfReader_processFile(FILE *fp, int verbose_level,
                           msgRxCb_t msgRxCb, void *cbData);

#ifdef __cplusplus
}
#endif

#endif
