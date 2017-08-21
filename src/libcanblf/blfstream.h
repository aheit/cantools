#ifndef INCLUDE_BLFSTREAM_H
#define INCLUDE_BLFSTREAM_H

/*  blfstream.h -- declarations for blfstream
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

#ifdef HAVE_INTTYPES_H
# include <inttypes.h>
#endif
#ifdef HAVE_STDINT_H
# include <stdint.h>
#endif

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int success_t;

#define BLFMIN(x,y) ((x)<(y)?(x):(y))

/*
 * SizedStream: a file or memory based stream, which is tracking its
 * remaining bytes
 */
typedef struct{
  FILE      *mFile;      /* FILE pointer to associated stream */
  uint32_t   mBytesLeft; /* number of bytes left in stream */
  uint8_t   *mBuffer;    /* pointer to allocated memory for a
                            memory-based stream */
} SizedStream;

/*
 * DualStream: two associated streams from which data can be read.
 * if memStream is active, data is streamed from memStream, otherwise
 * fileStream is used.
 */
typedef struct {
  SizedStream fileStream;
  SizedStream memStream;
} DualStream;

success_t blfSizedStreamInitFromMem(SizedStream *const m, void *buffer,
                                    const size_t size);
int blfSizedStreamIsEmpty(const SizedStream *const s);
int blfSizedStreamIsEmpty(const SizedStream *const s);
int blfSizedStreamIsOpen(const SizedStream *const s);
FILE *blfFileStreamGetFile(SizedStream *fs);
success_t blfSizedStreamDetermineBytesLeft(SizedStream *fs);
success_t blfSizedStreamInitFromFile(SizedStream *const s, FILE *const fp);

void blfDualStreamInit (DualStream *ds);
success_t blfDualStreamClose(DualStream *ds);
int blfDualStreamIsEmpty(const DualStream *const ds);
uint32_t blfDualStreamBytesLeft(DualStream *ds);
success_t blfDualStreamReadOrSkip(DualStream *ds, void *dest, size_t nBytes,
                                  int fileOnly);
success_t blfDualStreamReduceBytesLeft(DualStream *ds,
                                       const uint32_t offset);

#ifdef __cplusplus
}
#endif

#endif
