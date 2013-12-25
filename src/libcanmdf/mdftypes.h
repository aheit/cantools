#ifndef INCLUDE_MDFTYPES_H
#define INCLUDE_MDFTYPES_H

/*  mdftypes.h -- declaration of MDF data types
    Copyright (C) 2012,2013 Andreas Heitmann

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

#include <stdint.h>

/* base types */
typedef int8_t         sint8_t;
typedef int16_t        sint16_t;
typedef int32_t        sint32_t;
typedef double         real_t;
typedef char           char_t;
typedef char           char32_t[32];
typedef char           char36_t[36];
typedef char           char80_t[80];
typedef char           char128_t[128];
typedef int32_t        link_t;
typedef uint16_t       mdf_bool_t;

#endif
