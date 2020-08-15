/*  cantomat -- convert CAN log files to MAT files
    Copyright (C) 2007-2020 Andreas Heitmann

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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include "signalformat.h"
#include "measurement.h"
#include "busassignment.h"
#include "matwrite.h"
#include "ascreader.h"
#include "clgreader.h"
#include "blfreader.h"
#include "vsbreader.h"

int verbose_flag = 0;
int debug_flag   = 0;

const char *program_name;

static void usage_error(void)
{
  fprintf(stderr, "Type '%s --help' for more information\n",program_name);
  exit(1);
}

static void
help(void)
{
  fprintf(stderr,
          "Usage: %s [OPTION] -d dbcfile\n"
          "cantomat " VERSION ": Convert CAN trace file to MAT file.\n"
          "\n"
          "Options:\n"
          "  -b, --bus <busid>          specify bus for next database\n"
          "  -d, --dbc <dbcfile>        assign database to previously specified bus\n"
          "  -a, --asc <ascfile>        ASC input file\n"
          "  -B, --blf <blffile>        BLF input file\n"
          "  -c, --clg <clgfile>        CLG input file\n"
          "  -v, --vsb <vsbfile>        VSB input file\n"
          "  -m, --mat <matfile>        MAT output file\n"
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

int
main(int argc, char **argv)
{
  char *inputFilename = NULL;
  int inputFiles = 0;
  char *matFilename = NULL;
  busAssignment_t *busAssignment = busAssignment_create();
  int bus = -1;
  signalFormat_t signalFormat = signalFormat_Name;
  measurement_t *measurement;
  int ret = 1;
  sint32 timeResolution = 10000;
  parserFunction_t parserFunction = NULL;

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
      {"asc",     required_argument, 0, 'a'},
      {"blf",     required_argument, 0, 'B'},
      {"bus",     required_argument, 0, 'b'},
      {"clg",     required_argument, 0, 'c'},
      {"dbc",     required_argument, 0, 'd'},
      {"format",  required_argument, 0, 'f'},
      {"mat",     required_argument, 0, 'm'},
      {"timeres", required_argument, 0, 't'},
      {"vsb",     required_argument, 0, 'v'},
      {"help",    no_argument,    NULL, 'h'},
      {0, 0, 0, 0}
    };

    /* getopt_long stores the option index here. */
    int option_index = 0;
    int c;

    c = getopt_long (argc, argv, "a:B:b:c:d:f:m:t:v:",
                     long_options, &option_index);

    /* Detect the end of the options. */
    if (c == -1) break;

    switch (c) {
    case 0:
      break;
    case 'a':
      inputFilename = optarg;
      parserFunction =ascReader_processFile;
      inputFiles++;
      break;
    case 'B':
      inputFilename = optarg;
      parserFunction =blfReader_processFile;
      inputFiles++;
      break;
    case 'c':
      inputFilename = optarg;
      parserFunction =clgReader_processFile;
      inputFiles++;
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

      /* reset bus specification */
      bus = -1;
      break;
    case 'm':
      matFilename = optarg;
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
        goto usage_error;
      }
      break;
    case 't':
      timeResolution = atoi(optarg);
      break;
    case 'v':
      inputFilename = optarg;
      parserFunction = vsbReader_processFile;
      inputFiles++;
      break;
    case 'h': help(); exit(0);   break;
    case '?':
      /* getopt_long already printed an error message. */
      goto usage_error;
      break;
    default:
      fprintf(stderr, "error: unknown option %c\n", c);
      goto usage_error;
    }
  }

  /* diagnose options */
  if(inputFiles != 1) {
    fprintf(stderr, "error: please specify exactly one input file\n");
    goto usage_error;
  }

  if(matFilename == NULL) {
    fprintf(stderr, "error: MAT output filename not specified\n");
    goto usage_error;
  }
  
  /* parse DBC files */
  if(busAssignment_parseDBC(busAssignment)) {
    fprintf(stderr, "error: parsing of DBC file failed\n");
    goto error;
  }
  
  /* parse input file */
  if(verbose_flag) {
    if(inputFilename != NULL) {
      fprintf(stderr,
              "Parsing input file %s\n",
              inputFilename?inputFilename:"<stdin>");
    }
  }
  measurement = measurement_read(busAssignment,
                                 inputFilename,
                                 signalFormat,
                                 timeResolution,
                                 parserFunction);
  if(measurement != NULL) {

    /* write MAT file */
    if(verbose_flag) {
      fprintf(stderr, "Writing MAT file %s\n", matFilename);
    }
    matWrite(measurement, matFilename);

    /* free memory */
    measurement_free(measurement);
  }
  ret = 0;
  goto normal_exit;

usage_error:  
  usage_error();

error:
  busAssignment_free(busAssignment);
  ret = 1;

normal_exit:
  return ret;
}
