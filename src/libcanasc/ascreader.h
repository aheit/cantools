#ifndef INCLUDE_ASCREADER_H
#define INCLUDE_ASCREADER_H

/*  ascreader.h --  declarations for ascreader
    Copyright (C) 2007-2020 Andreas Heitmann

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

#include <stdio.h>
#include "dbctypes.h"
#include <time.h>
#include "measurement.h"

#ifdef __cplusplus
extern "C" {
#endif

void ascReader_processFile(FILE *fp, int verbose_level,
			   msgRxCb_t msgRxCb, void *cbData);

#ifdef __cplusplus
}
#endif

#endif
