#ifndef INCLUDE_DBCREADER_H
#define INCLUDE_DBCREADER_H

/*  dbcreader.h -- declarations for libcandbc
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

#include "dbcmodel.h"

#ifdef __cplusplus
extern "C" {
#endif

dbc_t *dbc_read_file(char *filename);

#ifdef __cplusplus
}
#endif


#endif
