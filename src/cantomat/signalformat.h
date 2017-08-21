#ifndef INCLUDE_SIGNALFORMAT_H
#define INCLUDE_SIGNALFORMAT_H

/*  signalformat.h --  declarations for signalformat
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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

typedef enum {
  signalFormat_Name     = 1<<1,
  signalFormat_Message  = 1<<2,
  signalFormat_Database = 1<<3,
} signalFormat_t;

char *signalFormat_stringAppend(const char *in, const char *app);

#endif
