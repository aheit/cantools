/*  matdump -- dump contents of .mat file
    Copyright (C) 2015 Andreas Heitmann

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

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <matio.h>
#include <getopt.h>

#include "matdump.h"

static int verbose_level = 0;

static void
mat_dump(mat_t *matfp)
{
  size_t dims[2];

  matvar_t *matvar;
  int rv;
  
  while ( NULL != (matvar = Mat_VarReadNext(matfp)) ) {
    Mat_VarPrint(matvar,1);
    Mat_VarFree(matvar);
  }
}

static void usage_error(const char *program_name)
{
  fprintf(stderr, "Type '%s --help' for more information\n",program_name);
  exit(EXIT_FAILURE);
}

static void help(const char *program_name)
{
  fprintf(stderr,
          "Usage: %s [OPTIONS] <mdffile> <matfile>\n"
          "Convert MDF file to MAT file.\n"
          "\n"
          "Options:\n"
          "  -h, --help                 display this help and exit\n"
          "\n", program_name);
}

int
main(int argc, char **argv)
{
  char *mat_filename = NULL;
  char *program_name = argv[0];
  mat_t *matfp;

  /* parse arguments */
  while (1) {
    static struct option long_options[] = {
      /* These options set a flag. */
      
      /* These options don't set a flag.
         We distinguish them by their indices. */
      {"help",    no_argument,       NULL,         (int)'h'},
      {0, 0, 0, 0}
    };
    /* getopt_long stores the option index here. */
    int option_index = 0;
    int c;

    c = getopt_long (argc, argv, "h",
                     long_options, &option_index);

    /* Detect the end of the options. */
    if (c == -1) break;

    switch (c) {
    case 0:
      break;
    case 'h':
      help(program_name);
      exit(EXIT_SUCCESS);
      break;
    case '?':
      /* getopt_long already printed an error message. */
      usage_error(program_name);
      break;
    default:
      fprintf(stderr, "error: unknown option %c\n", c);
      usage_error(program_name);
    }
  }


  /* input files */
  if (optind == argc - 1) {
    mat_filename = argv[optind++];
  } else {
    fprintf(stderr, "error: wrong number of arguments\n");
    usage_error(program_name);
    return 1;
  }

  /* print banner */
  if(verbose_level >= 1) {
    fprintf(stderr, "%s (%s, %s, cantools " PACKAGE_VERSION ")\n",
            program_name, __DATE__, __TIME__);
  }

  /* open mat file */
  matfp = Mat_Open(mat_filename, MAT_ACC_RDONLY);
  if(NULL != matfp) {
    mat_dump(matfp);
  } else {
    fprintf(stderr,"Error opening MAT file %s",mat_filename);
  }
  
  /* close mat file */
  if(NULL != matfp) {
    Mat_Close(matfp);
  }

  /* say goodbye */
  if(verbose_level >= 1) {
    puts("done.");
  }

  return 0;
}
