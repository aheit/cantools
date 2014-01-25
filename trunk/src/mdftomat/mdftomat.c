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

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <matio.h>
#include <getopt.h>

#include "mdftomat.h"
#include "mdfcg.h"
#include "mdffilter.h"
#include "mdffile.h"
#include "mdfdg.h"

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
    int i;
    for(i=0;i<sizeof(xtable);i++) {
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
    out[j] = xtable[in[j]];
  }

  /* ensure name begins with letter */
  if(!(isupper(out[0]) || islower(out[0]))) {
    out[0] = 'X';
  }

  /* terminate name */
  out[j] = 0;

  return out;
}

static void
mat_write_signal(const mdf_t *const mdf, 
                 const uint32_t can_channel,
                 const uint32_t number_of_records,
                 const uint16_t channel_type,
                 const char *const message_name,
                 const char *const signal_name,
                 const double *const timeValue,
                 const filter_t *const filter,
                 const void *const cbData)
{
  char *filter_signal_name_in;
  char *filter_message_name_in;
  char *filter_name_out;
  size_t dims[2];
  mdftomat_t *const mdftomat = (mdftomat_t *)cbData;

  dims[0] = number_of_records;
  dims[1] = 2;

  if(   ((can_channel != 0) && (channel_type == 0)) /* Vector CAN */
     || ((can_channel == 0) && (channel_type == 0)) /* DIM */ ) {
    if(mdf->verbose_level >= 2) {
       uint32_t ir;
       printf("ch=%lu n=%lu m=%s s=%s\n",
              (unsigned long)can_channel,
              (unsigned long)number_of_records,
              message_name,
              signal_name);
      if(mdf->verbose_level >= 3) {
       for(ir=0;ir<number_of_records;ir++) {
          printf("%g %g\n",timeValue[ir],timeValue[ir+number_of_records]);
       }
      }
    }
    /* sanitize variable name */
    filter_signal_name_in = sanitize_name(signal_name);
    filter_message_name_in = sanitize_name(message_name);
    filter_name_out = filter_apply(filter, can_channel,
				   filter_message_name_in,
				   filter_signal_name_in);
    if(mdf->verbose_level >= 2) {
      printf("    CNBLOCK can_ch=%lu\n"
	     "            message      = %s\n"
	     "            signal_name  = %s\n"
	     "            filter_input = %s\n"
	     "            filter_output= %s\n",
	     (unsigned long)can_channel, filter_message_name_in,
	     signal_name, filter_signal_name_in,
	     (filter_name_out!=NULL)?filter_name_out:"<rejected by filter>" );
      if(filter_name_out != NULL) {
	printf("+ %d %s %s %s\n",
	       can_channel,
	       filter_message_name_in,
	       filter_signal_name_in,
	       filter_name_out );
      }
    }
    free(filter_signal_name_in);
    free(filter_message_name_in);

    if(filter_name_out != NULL) {
      matvar_t *matvar;
      int rv;

      /* write matlab variable */
      matvar = Mat_VarCreate(filter_name_out, MAT_C_DOUBLE, MAT_T_DOUBLE,
			     2, dims, (double *)timeValue, 0);
      rv = Mat_VarWrite(mdftomat->mat, matvar, mdftomat->compress);
      assert(rv == 0);
      Mat_VarFree(matvar);
      free(filter_name_out);
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
          "Usage: %s [OPTIONS] <mdffile> <matfile>\n"
          "Convert MDF file to MAT file.\n"
          "\n"
          "Options:\n"
          "  -f, --filter <filterfile>  filter signals\n"
          "      --verbose              verbose output\n"
          "      --brief                brief output (default)\n"
          "      --debug                output debug information\n"
          "  -z, --compress             compression MAT file\n"
          "      --v5                   output version 5 MAT file\n"
          "      --v73                  output version 7.3 MAT file\n"
          "  -h, --help                 display this help and exit\n"
          "\n", program_name);
  fprintf(stderr,
          "Filter file format:\n"
          "  // comment\n"
          "  // any number of:\n"
          "  <op> <channel> <message> <signal> [newName]\n"
          "\n"
          "  op = +   include signal\n"
          "       -   exclude signal\n"
          "  channel  numerical channel number or *\n"
          "  message  message name, wildcards allowed\n"
          "  signal   signal name, wildcards allowed\n"
          "  newname  optional: rename signal\n");
}

/*
 * conversion of fixed-length text buffer to string.
 * input format: text array of up to len bytes, padded with null bytes
 * output format: null byte terminated string
 */
static char *
string_from_array(const char *input, const size_t len)
{
  char *const output = malloc(len+1);
  char *const cp = memccpy(output, input, '\0', len);
  if(cp == NULL) {
    output[len]='\0';
  }
  return output;
}

#define FIELD_PRINT(desc,field) \
{ \
  char *const cp = \
     string_from_array((const char *)&(field), sizeof(field));  \
  fputs(desc,stdout); \
  puts(cp);           \
  free(cp);           \
}

static void
mdfProcess(const mdf_t *const mdf, const mdftomat_t *const mdftomat,
           const filter_t *const filter)
{
  id_block_t *id_block;
  hd_block_t *hd_block;

  id_block = id_block_get(mdf);
  assert(id_block->byte_order == 0); /* little endian only */

  hd_block = hd_block_get(mdf);

  if(mdf->verbose_level >= 1) {
    const char *comment = tx_block_get_text(mdf, hd_block->link_tx_block);
    if(comment) {
      printf("File Comment =\n%s\n",comment);
    }
    FIELD_PRINT("Date         = ", hd_block->recording_date);
    FIELD_PRINT("Time         = ", hd_block->recording_time);
    FIELD_PRINT("Author       = ", hd_block->author);
    FIELD_PRINT("Organization = ", hd_block->organization);
    FIELD_PRINT("Project      = ", hd_block->project);
    FIELD_PRINT("Measurement  = ", hd_block->measurement_id);
   }

  /* process data groups */
  mdfProcessDataGroups(mdf, filter, hd_block->link_dg_block,
                         mat_write_signal, (const void * const)mdftomat);
}

static int verbose_level = 0;
static mdftomat_t mdftomat = {
  NULL,
  MAT_COMPRESSION_NONE
};

static int mat_file_ver = (int)MAT_FT_DEFAULT;

int
main(int argc, char **argv)
{
  char *mdf_filename = NULL;
  char *mat_filename = NULL;
  const mdf_t *mdf;
  filter_t *filter;
  char *filter_filename = NULL;
  char *program_name = argv[0];

  /* parse arguments */
  while (1) {
    static struct option long_options[] = {
      /* These options set a flag. */
      {"verbose", no_argument,       &verbose_level,  1},
      {"debug",   no_argument,       &verbose_level,  2},
      {"brief",   no_argument,       &verbose_level,  0},
      {"v5",      no_argument,       &mat_file_ver,   (int)MAT_FT_MAT5},
      {"v73",     no_argument,       &mat_file_ver,   (int)MAT_FT_MAT73},
      {"compress",no_argument,       NULL,           'z'},
      /* These options don't set a flag.
         We distinguish them by their indices. */
      {"filter",  required_argument, 0,            (int)'f'},
      {"help",    no_argument,       NULL,         (int)'h'},
      {0, 0, 0, 0}
    };
    /* getopt_long stores the option index here. */
    int option_index = 0;
    int c;

    c = getopt_long (argc, argv, "a:b:d:f:hm:t:vz",
                     long_options, &option_index);

    /* Detect the end of the options. */
    if (c == -1) break;

    switch (c) {
    case 0:
      break;
    case 'f':
      filter_filename = optarg;
      break;
    case 'h':
      help(program_name);
      exit(EXIT_SUCCESS);
      break;
    case 'v':
      verbose_level = 1;
      break;
    case 'd':
      verbose_level = 2;
      break;
    case 'z':
      mdftomat.compress = MAT_COMPRESSION_ZLIB;
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


  /* check structure packing */
  assert(offsetof(cn_block_t,link_asam_mcd_name) == 218);

  /* input files */
  if (optind == argc - 2) {
    mdf_filename = argv[optind++];
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

  /* connect to mdf file */
  mdf = mdf_attach(mdf_filename, verbose_level);
  if(mdf == NULL) {
    return 1;
  }

  /* create mat file */
  mdftomat.mat = Mat_CreateVer(mat_filename, NULL, (enum mat_ft)mat_file_ver);
  if(mdftomat.mat == NULL) {
    fprintf(stderr,"can't write to mat file %s\n",mat_filename);
    return 1;
  }

  /* read filter */
  if(filter_filename != NULL) {
    filter = mdf_filter_create(filter_filename);
    if(filter == NULL) {
      return 1;
    }
  } else {
    filter = NULL;
  }

  /* process MDF file */
  if(verbose_level >= 1) {
    fprintf(stderr, "converting %s to %sfile %s\n",
            mdf_filename,
            (mdftomat.compress == MAT_COMPRESSION_ZLIB)?"compressed ":"",
            mat_filename);
  }
  mdfProcess(mdf, &mdftomat, filter);

  /* free filter */
  filter_free(filter);

  /* detach from mdf file */
  mdf_detach(mdf);

  /* close mat file */
  Mat_Close(mdftomat.mat);

  /* say goodbye */
  if(verbose_level >= 1) {
    fprintf(stderr, "done.\n", mdf_filename);
  }

  return 0;
}
