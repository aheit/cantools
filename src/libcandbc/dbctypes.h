#ifndef INCLUDE_DBCTYPES_H
#define INCLUDE_DBCTYPES_H

/*  dbctypes.h --  declarations for libcandbc
    Copyright (C) 2007-2017 Andreas Heitmann

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

/* dbc base types */
typedef uint8_t        uint8;
typedef int8_t         sint8;
typedef uint16_t       uint16;
typedef int16_t        sint16;
typedef uint32_t       uint32;
typedef int32_t        sint32;
typedef int64_t        number_t;
typedef uint64_t       uint64;
typedef float          float32;
typedef double         float64;

#endif
