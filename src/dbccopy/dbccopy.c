/*  dbccopy.c -- copy DBC files
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

#include <stdio.h>
#include "dbcreader.h"
#include "dbcwriter.h"

int
main(int argc, char **argv)
{
  dbc_t *dbc;
  char *const inFilename = (argc>1 ? argv[1] : NULL);
  char *const outFilename = (argc>2 ? argv[2] : NULL);
  int ret = 0;

  if(NULL != (dbc = dbc_read_file(inFilename))) {
    FILE *dbcout;

    /* open output file */
    if(outFilename != NULL) {
      if(NULL == (dbcout = fopen(outFilename,"w"))) {
        fprintf(stderr, "can't open output file '%s'\n", outFilename);
        ret = 1;
      }
    } else {
      dbcout = stdout;
    }

    /* perform copy */
    if(dbcout != NULL) {
      dbc_write(dbcout, dbc);
      
      /* close output file */
      if(outFilename != NULL) {
        fclose(dbcout);
      }
    }

    dbc_free(dbc);
  } else {
    fprintf(stderr, "can't open input file '%s'\n", inFilename);
    ret = 1;
  }

  return ret;
}
