#ifndef INCLUDE_MDFFILE_H
#define INCLUDE_MDFFILE_H

/*  mdffile.h --  declarations for mdffile
    Copyright (C) 2007-2011 Andreas Heitmann

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

#include "mdfmodel.h"

const mdf_t *mdf_attach(char *filename, int verbose_flag);
void mdf_detach(const mdf_t *const mdf);

#endif
