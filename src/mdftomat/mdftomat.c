/*  mdftomat -- convert MDF files to MAT files
    Copyright (C) 2012 Andreas Heitmann

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
#include "config.h"
#endif

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

static void
mat_write_signal(const mdf_t *const mdf, 
		 const uint32_t can_channel,
		 const uint32_t number_of_records,
		 const uint16_t channel_type,
		 const char *const message,
		 const char *const name,
		 const double *const timeValue,
		 const filter_t *const filter,
		 void *cbData)
{
  char *mat_name;
  size_t dims[2];
  mat_t *const mat = (mat_t *)cbData;

  dims[0] = number_of_records;
  dims[1] = 2;

  if((can_channel != 0) && (channel_type == 0)) {
    if(mdf->verbose_flag > 0) {
       uint32_t ir;
       printf("ch=%lu n=%lu m=%s s=%s\n",
	 (unsigned long)can_channel, (unsigned long)number_of_records, message, name);
       for(ir=0;ir<number_of_records;ir++) {
          printf("%g %g\n",timeValue[ir],timeValue[ir+number_of_records]);
       }
    }
    mat_name = filter_apply(filter, can_channel, message, name);
    if(mat_name != NULL) {
      int rv;
      matvar_t *const matvar =
	Mat_VarCreate(mat_name, MAT_C_DOUBLE, MAT_T_DOUBLE,
		      2, dims, (double *)timeValue, 0);
      rv = Mat_VarWrite(mat, matvar, 0);
      assert(rv == 0);
      Mat_VarFree(matvar);
      free(mat_name);
      if(mdf->verbose_flag > 0) {
	printf("    CNBLOCK can_ch=%lu, message=%s, name=%s\n",
		 (unsigned long)can_channel, message, name);
      }
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
          "Convert ASC log file to MAT file.\n"
          "\n"
          "Options:\n"
          "  -f, --filter <filterfile>  filter signals\n"
          "      --verbose              verbose output\n"
          "      --brief                brief output (default)\n"
          "      --debug                output debug information\n"
          "  -h, --help                 display this help and exit\n"
	  "\n", program_name);
  fprintf(stderr,
	  "Filter file format:\n"
	  "  // comment\n"
	  "  // any number of:\n"
	  "  <op> <channel> <message> <signal> [newName]\n"
	  "\n"
	  "  op = +   include signal\n"

	  "  channel  numerical channel number or *\n"
	  "  message  message name, wildcards allowed\n"
	  "  signal   signal name, wildcards allowed\n"
	  "  newname  optional: rename signal\n");
}

static void
mdfProcess(const mdf_t *const mdf, mat_t *mat, filter_t *filter)
{
  id_block_t *id_block;
  hd_block_t *hd_block;

  id_block = id_block_get(mdf);
  assert(id_block->byte_order == 0); /* little endian only */

  hd_block = hd_block_get(mdf);

  if(mdf->verbose_flag > 0) {
    const char *comment = tx_block_get_text(mdf, hd_block->link_tx_block);
    if(comment) {
      printf("File Comment =\n%s\n",comment);
    }
    printf("Date         = %s\n",(char *)&(hd_block->recording_date));
    printf("Time         = %s\n",(char *)&(hd_block->recording_time));
    printf("Author       = %s\n",(char *)&(hd_block->author));
    printf("Organization = %s\n",(char *)&(hd_block->organization));
    printf("Project      = %s\n",(char *)&(hd_block->project));
    printf("Measurement  = %s\n",(char *)&(hd_block->measurement_id));
  }

  /* process data groups */
  mdfProcessDataGroups(mdf, filter, hd_block->link_dg_block,
			 mat_write_signal, (void *)mat);
}

static int verbose_flag = 0;

int
main(int argc, char **argv)
{
  char *mdf_filename = NULL;
  char *mat_filename = NULL;
  const mdf_t *mdf;
  mat_t *mat;
  filter_t *filter;
  char *filter_filename = NULL;
  char *program_name = argv[0];

  fprintf(stderr, "%s (%s, %s)\n", program_name, __DATE__, __TIME__);
  /* parse arguments */
  while (1) {
    static struct option long_options[] = {
      /* These options set a flag. */
      {"verbose", no_argument,       &verbose_flag, 1},
      {"debug",   no_argument,       &verbose_flag, 2},
      {"brief",   no_argument,       &verbose_flag, 0},
      /* These options don't set a flag.
         We distinguish them by their indices. */
      {"filter",  required_argument, 0,            (int)'f'},
      {"help",    no_argument,       NULL,         (int)'h'},
      {0, 0, 0, 0}
    };
    /* getopt_long stores the option index here. */
    int option_index = 0;
    int c;

    c = getopt_long (argc, argv, "a:b:d:f:hm:t:",
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
  //  assert(offsetof(cn_block_t,link_asam_mcd_name) == 218);

  /* input files */
  if (optind == argc - 2) {
    mdf_filename = argv[optind++];
    mat_filename = argv[optind++];
  } else {
    fprintf(stderr, "error: wrong number of arguments\n");
    usage_error(program_name);
    return 1;
  }

  /* connect to mdf file */
  mdf = mdf_attach(mdf_filename, verbose_flag);
  if(mdf == NULL) {
    return 1;
  }

  /* create mat file */
  mat = Mat_Create(mat_filename, NULL);
  if(mat == NULL) {
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
  
  mdfProcess(mdf,mat,filter);

  /* free filter */
  filter_free(filter);

  /* detach from mdf file */
  mdf_detach(mdf);

  /* close mat file */
  Mat_Close(mat);

  return 0;
}
