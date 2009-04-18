/*  asctomat -- convert ASC files to MAT files
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include "signalFormat.h"
#include "measurement.h"
#include "busAssignment.h"
#include "matWrite.h"

int verbose_flag = 0;
int debug_flag   = 0;

const char *program_name;

static void usage_error(void)
{
  fprintf(stderr, "Type '%s --help' for more information\n",program_name);
  exit(1);
}

static void help(void)
{
  fprintf(stderr,
          "Usage: %s [OPTION] -d dbcfile\n"
          "List information about dbcfile.\n"
          "\n"
          "Options:\n"
          "  -b, --bus <busid>          specify bus for next database\n"
          "  -d, --dbc <dbcfile>        assign database to previously specified bus\n"
          "  -a, --asc <ascfile>        ASC input file to convert\n"
          "  -m, --mat <matfile>        MAT file to output\n"
          "  -f, --format <format>      signal name format\n"
          "  -t, --timeres <nanosec>    time resolution\n"
          "      --verbose              verbose output\n"
          "      --brief                brief output (default)\n"
          "      --debug                output debug information\n"
          "      --help                 display this help and exit\n"
          "\n"
          "<format> is either n, mn, or dmn, specifying the output name format\n"
          "      n                      signalname\n"
          "      mn                     messagename_signalname\n"
          "      dmn                    dbcname_messagename_signalname\n",
	program_name);
}

int main(int argc, char **argv)
{
  char *asc_filename = NULL;
  char *mat_filename = NULL;
  busAssignment_t *busAssignment = busAssignment_create();
  int bus = -1;
  signalFormat_t signalFormat = signalFormat_Name;
  measurement_t *measurement;
  int ret;
  sint32 timeResolution = 10000;

  program_name = argv[0];

  /* parse arguments */
  while (1) {
    static struct option long_options[] = {
      /* These options set a flag. */
      {"verbose", no_argument,       &verbose_flag, 1},
      {"brief",   no_argument,       &verbose_flag, 0},
      {"debug",   no_argument,       &debug_flag,   1},
      /* These options don't set a flag.
         We distinguish them by their indices. */
      {"bus",     required_argument, 0, 'b'},
      {"dbc",     required_argument, 0, 'd'},
      {"asc",     required_argument, 0, 'a'},
      {"mat",     required_argument, 0, 'm'},
      {"format",  required_argument, 0, 'f'},
      {"timeres", required_argument, 0, 't'},
      {"help",    no_argument,       NULL, 'h'},
      {0, 0, 0, 0}
    };

    /* getopt_long stores the option index here. */
    int option_index = 0;
    int c;

    c = getopt_long (argc, argv, "a:b:d:f:m:t:",
                     long_options, &option_index);

    /* Detect the end of the options. */
    if (c == -1) break;

    switch (c) {
    case 0:
      break;
    case 'a':
      asc_filename = optarg;
      break;
    case 'b':
      bus = atoi(optarg);
      break;
    case 'd':
      if(verbose_flag) {
	if(bus == -1) {
	  fprintf(stderr, "Assigning DBC file %s to all busses\n", optarg);
	} else {
	  fprintf(stderr, "Assigning DBC file %s to bus %d\n", optarg, bus);
	}
      }
      busAssignment_associate(busAssignment, bus, optarg);
      break;
    case 'm':
      mat_filename = optarg;
      break;
    case 'f':
      if(!strcmp(optarg, "n")) {
        signalFormat =  signalFormat_Name;
      } else if(!strcmp(optarg, "mn")) {
        signalFormat =  signalFormat_Message
                     |  signalFormat_Name;
      } else if(!strcmp(optarg, "dmn")) {
        signalFormat =  signalFormat_Database
                     |  signalFormat_Message
                     |  signalFormat_Name;
      } else {
        fprintf(stderr, "error: format must be 's', 'ms', or 'dms'\n");
	usage_error();
      }
      mat_filename = optarg;
      break;
    case 't':
      timeResolution = atoi(optarg);
      break;
    case 'h': help(); exit(0);   break;
    case '?':
      /* getopt_long already printed an error message. */
      usage_error();
      break;
    default:
      fprintf(stderr, "error: unknown option %c\n", c);
      busAssignment_free(busAssignment);
      usage_error();
    }
  }

#ifdef YYDEBUG
  if(debug_flag) {
    extern int yydebug;
    yydebug=1;
  }
#endif

  if(mat_filename != NULL) {

    /* parse DBC files */
    busAssignment_parseDBC(busAssignment);

    /* parse ASC file */
    if(verbose_flag) {
      fprintf(stderr,
	      "Parsing ASC file %s\n", asc_filename?asc_filename:"<stdin>");
    }
    measurement = measurement_read(busAssignment,
				   asc_filename,
				   signalFormat,
				   timeResolution);
    if(measurement != NULL) {

      /* write MAT file */
      if(verbose_flag) {
	fprintf(stderr, "Writing MAT file %s\n", mat_filename);
      }
      matWrite(measurement, mat_filename);
      measurement_free(measurement);
    }
    ret = 0;
  } else {
    fprintf(stderr, "error: must specify MAT filename\n");
    usage_error();
  }
  busAssignment_free(busAssignment);
  return ret;
}
