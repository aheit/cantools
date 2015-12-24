#ifndef INCLUDE_MDFTOMAT_H
#define INCLUDE_MDFTOMAT_H

/*  mdftomat -- convert MDF files to MAT files
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

#include "config.h"
#include <matio.h>

/* callback data for MATLAB output */
typedef struct {
  mat_t *mat;
  enum matio_compression compress;
} mdftomat_t;

#endif
