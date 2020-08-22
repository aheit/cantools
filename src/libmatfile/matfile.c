/*  matfile -- functions for MAT files
    Copyright (C) 2020 Andreas Heitmann

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

#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <inttypes.h>

#include "matfile.h"

/*
 * A valid variable name is a character string of letters, digits, and
 * underscores [...] and beginning with a letter.
 */
char *
sanitize_name(const char *in)
{
  char *out;
  static char xtable[256];
  static int init=0;
  size_t n = strlen(in);
  size_t j;

  /* initialize transformation table */
  if(!init) {
    uint16_t i;
    for(i = 0; i < (uint16_t)sizeof(xtable); i++) {
      if(isupper(i) || islower(i) || isdigit(i) || (i=='_')) {
        xtable[i] = i;
      } else {
        xtable[i] = '_';
      }
    }
    init=1;
  }

  /* perform transformation */
  out = malloc(n+1);
  for(j=0;j<n;j++) {
    out[j] = xtable[(int)in[j]];
  }

  /* ensure name begins with letter */
  if(!(isupper((int)out[0]) || islower((int)out[0]))) {
    out[0] = 'X';
  }

  /* terminate name */
  out[j] = 0;

  return out;
}
