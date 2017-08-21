/*  matdump -- dump contents of .mat file
    Copyright (C) 2015-2017 Andreas Heitmann

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

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <matio.h>
#include <getopt.h>

#include "matdump.h"

static int mode = 0; /* short dump */
static int verbose_level = 0;

#if defined(_MSC_VER) || defined(__MINGW32__)
#   define SIZE_T_FMTSTR "Iu"
#else
#   define SIZE_T_FMTSTR "zu"
#endif

static void
Mat_PrintNumber(enum matio_types type, void *data)
{
    switch ( type ) {
        case MAT_T_DOUBLE:
            printf("%g",*(double*)data);
            break;
        case MAT_T_SINGLE:
            printf("%g",*(float*)data);
            break;
#ifdef HAVE_MAT_INT64_T
        case MAT_T_INT64:
#if HAVE_INTTYPES_H
            printf("%" PRIi64,*(mat_int64_t*)data);
#elif defined(_MSC_VER) && _MSC_VER >= 1200
            printf("%I64i",*(mat_int64_t*)data);
#elif defined(HAVE_LONG_LONG_INT)
            printf("%lld",(long long)(*(mat_int64_t*)data));
#else
            printf("%ld",(long)(*(mat_int64_t*)data));
#endif
            break;
#endif
#ifdef HAVE_MAT_UINT64_T
        case MAT_T_UINT64:
#if HAVE_INTTYPES_H
            printf("%" PRIu64,*(mat_uint64_t*)data);
#elif defined(_MSC_VER) && _MSC_VER >= 1200
            printf("%I64u",*(mat_uint64_t*)data);
#elif defined(HAVE_UNSIGNED_LONG_LONG_INT)
            printf("%llu",(unsigned long long)(*(mat_uint64_t*)data));
#else
            printf("%lu",(unsigned long)(*(mat_uint64_t*)data));
#endif
            break;
#endif
        case MAT_T_INT32:
            printf("%d",*(mat_int32_t*)data);
            break;
        case MAT_T_UINT32:
            printf("%u",*(mat_uint32_t*)data);
            break;
        case MAT_T_INT16:
            printf("%hd",*(mat_int16_t*)data);
            break;
        case MAT_T_UINT16:
            printf("%hu",*(mat_uint16_t*)data);
            break;
        case MAT_T_INT8:
            printf("%hhd",*(mat_int8_t*)data);
            break;
        case MAT_T_UINT8:
            printf("%hhu",*(mat_uint8_t*)data);
            break;
        default:
            break;
    }
}

static int
full_dump(matvar_t *matvar)
{
  const char *class_type_desc[16] = {
    "Undefined","Cell Array","Structure",
    "Object","Character Array","Sparse Array","Double Precision Array",
    "Single Precision Array", "8-bit, signed integer array",
    "8-bit, unsigned integer array","16-bit, signed integer array",
    "16-bit, unsigned integer array","32-bit, signed integer array",
    "32-bit, unsigned integer array","64-bit, signed integer array",
    "64-bit, unsigned integer array"};
  const char *data_type_desc[23] = {
    "Unknown","8-bit, signed integer",
    "8-bit, unsigned integer","16-bit, signed integer",
    "16-bit, unsigned integer","32-bit, signed integer",
    "32-bit, unsigned integer","IEEE 754 single-precision","RESERVED",
    "IEEE 754 double-precision","RESERVED","RESERVED",
    "64-bit, signed integer","64-bit, unsigned integer", "Matlab Array",
    "Compressed Data","Unicode UTF-8 Encoded Character Data",
    "Unicode UTF-16 Encoded Character Data",
    "Unicode UTF-32 Encoded Character Data","","String","Cell Array",
    "Structure"};
  int i, j;

  if(matvar == 0) return 0;
  if(matvar->isComplex ) return 0;
  if(matvar->rank != 2) return 0;
  switch(matvar->class_type) {
  case MAT_C_DOUBLE:
  case MAT_C_SINGLE:
#ifdef HAVE_MAT_INT64_T
  case MAT_C_INT64:
#endif
#ifdef HAVE_MAT_UINT64_T
  case MAT_C_UINT64:
#endif
  case MAT_C_INT32:
  case MAT_C_UINT32:
  case MAT_C_INT16:
  case MAT_C_UINT16:
  case MAT_C_INT8:
  case MAT_C_UINT8:
    if(matvar->name ) {
      printf("      Name: %s\n", matvar->name);
    }
    printf("      Rank: %d\n", matvar->rank);
    printf("Dimensions: %" SIZE_T_FMTSTR,matvar->dims[0]);
    for ( i = 1; i < matvar->rank; i++ ) {
      printf(" x %" SIZE_T_FMTSTR, matvar->dims[i]);
    }
    printf("\n");
    printf("Class Type: %s",class_type_desc[matvar->class_type]);
    if ( matvar->isComplex ) {
      printf(" (complex)");
    } else if ( matvar->isLogical ) {
      printf(" (logical)");
    }
    printf("\n");
    if ( matvar->data_type ) {
      printf(" Data Type: %s\n", data_type_desc[matvar->data_type]);
    }

    {
      size_t stride = Mat_SizeOf(matvar->data_type);
      char *data = (char*)matvar->data;
      for ( i = 0; i < matvar->dims[0]; i++ ) {
        for ( j = 0; j < matvar->dims[1]; j++ ) {
          size_t idx = matvar->dims[0]*j+i;
          Mat_PrintNumber(matvar->data_type,
                          data+idx*stride);
          printf(" ");
        }
        printf("\n");
      }
    }
    break;
  default:
    return 0;
    break;
  }
  return 1;
}

static void
var_dump(matvar_t *matvar)
{
  switch(mode) {
  case 0:
    Mat_VarPrint(matvar,1);
    puts("");
    break;
  case 1: /* full */
    if(!full_dump(matvar)) {
      Mat_VarPrint(matvar,1);
    }
    puts("");
    break;
  case 2: /* list */
    Mat_VarPrint(matvar,0);
    puts("");
    break;
  default:
    break;
  }
}

static void
mat_dump(mat_t *mat, int nvar, char **varnames)
{
  matvar_t *matvar;
 
  if(nvar == 0) { /* no var names given -> dump everything */
    while ( NULL != (matvar = Mat_VarReadNext(mat)) ) {
      var_dump(matvar);
      Mat_VarFree(matvar);
    }
  } else {
    int ivar;
    
    for(ivar = 0; ivar < nvar; ivar++) {
      matvar = Mat_VarRead(mat, varnames[ivar]);
      var_dump(matvar);
      Mat_VarFree(matvar);
    }
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
          "Usage: %s [OPTIONS] <matfile> [name1] ... \n"
          "Dump contents of .mat file.\n"
          "Dump specific variables if names are given"
          "\n"
          "Options:\n"
          "  -v, --verbose              verbose output\n"
          "  -f, --full                 dump all values of each signal\n"
          "  -l, --list                 list all variables\n"
          "  -h, --help                 display this help and exit\n"
          "\n", program_name);
}

int
main(int argc, char **argv)
{
  char *mat_filename = NULL;
  char *program_name = argv[0];
  mat_t *mat;

  /* parse arguments */
  while (1) {
    static struct option long_options[] = {
      /* These options set a flag. */
      
      /* These options don't set a flag.
         We distinguish them by their indices. */
      {"verbose", no_argument,       &verbose_level,  1},
      {"full",    no_argument,       &mode,           1},
      {"list",    no_argument,       &mode,           2},
      {"help",    no_argument,       NULL,            (int)'h'},
      {0, 0, 0, 0}
    };
    /* getopt_long stores the option index here. */
    int option_index = 0;
    int c;

    c = getopt_long (argc, argv, "hvfl",
                     long_options, &option_index);

    /* Detect the end of the options. */
    if (c == -1) break;

    switch (c) {
    case 0:
      break;
    case 'f':
      mode = 1;
      break;
    case 'l':
      mode = 2;
      break;
    case 'v':
      verbose_level = 1;
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


  /* mat file name */
  if (optind <= argc - 1) {
    mat_filename = argv[optind++];
  } else {
    fprintf(stderr, "error: missing .mat filename\n");
    usage_error(program_name);
    return 1;
  }

  /* print banner */
  if(verbose_level >= 1) {
    fprintf(stderr, "%s (%s, %s, cantools " PACKAGE_VERSION ")\n",
            program_name, __DATE__, __TIME__);
  }

  /* open mat file */
  mat = Mat_Open(mat_filename, MAT_ACC_RDONLY);
  if(NULL != mat) {
    mat_dump(mat, argc - optind, &argv[optind]);
  } else {
    fprintf(stderr,"Error opening MAT file %s",mat_filename);
  }
  
  /* close mat file */
  if(NULL != mat) {
    Mat_Close(mat);
  }

  /* say goodbye */
  if(verbose_level >= 1) {
    puts("done.");
  }

  return 0;
}
