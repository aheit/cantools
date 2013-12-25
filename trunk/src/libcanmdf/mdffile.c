/*  mdffile.c --  handle MDF file connection
    Copyright (C) 2012-2013 Andreas Heitmann

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

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "mdfmodel.h"
#include "mdffile.h"

const mdf_t *
mdf_attach(char *filename, int verbose_level)
{
  CREATE(mdf_t, mdf);
  int fd;

  mdf->verbose_level = verbose_level;

  /* open input file */
  mdf->fd = open(filename, O_RDONLY);
  if(fd != -1) {
    struct stat sb;
    fstat(mdf->fd, &sb);
    mdf->size = sb.st_size;
    mdf->base = mmap(NULL, mdf->size, PROT_READ,
		     MAP_PRIVATE, mdf->fd, (off_t)0);
    if(mdf->base == MAP_FAILED) {
      fprintf(stderr, "mdf_attach(): can't mmap MDF file %s\n",filename);
      mdf = NULL;
    }
  } else {
    fprintf(stderr, "mdf_attach(): can't open MDF file %s\n",filename);
    mdf = NULL;
  }
  return mdf;
}

void
mdf_detach(const mdf_t *const mdf)
{
  munmap(mdf->base, mdf->size);
  close(mdf->fd);
}
