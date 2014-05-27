/*  signalFormat.c --  format signal name
    Copyright (C) 2007-2009 Andreas Heitmann

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

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "signalFormat.h"

/* strapp - copies source string without \0 and returns pointer to
   next destination character */
static char *strapp(char *dp, const char *sp)
{
  while(*sp != '\0') {
    *dp++ = *sp++;
  }
  return dp;
}

char *signalFormat_stringAppend(const char *in, const char *app)
{
  char *ret;

  if(in == NULL) {
    ret = strdup(app);
  } else {
    char *dp;
    char *sp;

    ret = malloc(strlen(in) + 1 + strlen(app) + 1);
    dp = strapp(ret, in);
    *dp++ = '_';
    dp = strapp(dp, app);
    *dp = '\0';
  }
  return ret;
}
