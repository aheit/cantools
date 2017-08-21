/*  blfstream.c -- BLF stream handling
    Copyright (C) 2017 Andreas Heitmann

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
#include <stdlib.h>

#include "blfstream.h"

/********************************************************************
 * blfFile*: Low-level file operations
 ********************************************************************/
static success_t
blfFileReadOrSkip(FILE *fp, void *dest, size_t nBytes)
{
  if(dest != NULL) {
    size_t bytesRead = fread(dest, (size_t)1, nBytes, fp);
    return (!ferror(fp) && (nBytes == bytesRead));
  } else {
    return 0 == fseek(fp, nBytes, SEEK_CUR);
  }
}

static success_t
blfFileGetRemainingFileSize(FILE *fp, uint32_t *remainingSizePtr)
{
  long int endPos, currentPos;

  /* compute remaining bytes in file */
  currentPos = ftell(fp);
  if(-1 == fseek(fp, 0, SEEK_END)) goto fail;
  endPos = ftell(fp);
  if(-1 == endPos) goto fail;
  if(-1 == fseek(fp, currentPos, SEEK_SET)) goto fail;
  if(endPos-currentPos <= 0) goto fail;
  *remainingSizePtr = endPos-currentPos;
  return 1;

fail:
  return 0;
}

/********************************************************************
 * blfSizedStream*: operations which require tracking of remaining
 *                  stream size
 ********************************************************************/
static void
blfSizedStreamInit(SizedStream *s)
{
  s->mFile = NULL;
  s->mBytesLeft = 0;
  s->mBuffer = NULL;
}

int
blfSizedStreamIsEmpty(const SizedStream *const s)
{
  return (s->mBytesLeft == 0);
}

int
blfSizedStreamIsOpen(const SizedStream *const s)
{
  return (s->mFile != NULL);
}


static uint32_t
blfSizedStreamBytesLeft(const SizedStream *const s)
{
  return s->mBytesLeft;
}

static success_t
blfSizedStreamReadOrSkip(const SizedStream *const s, void *const dest, const size_t nBytes)
{
  return blfFileReadOrSkip(s->mFile, dest, nBytes);
}

success_t
blfSizedStreamInitFromMem(SizedStream *const s, void *const buffer, const size_t size)
{
  s->mFile = fmemopen(buffer, size, "r");
  if(s->mFile != NULL) {
    s->mBuffer = buffer;
    s->mBytesLeft = size;
    return 1;
  } else {
    s->mBytesLeft = 0;
    s->mBytesLeft = 0;
    return 0;
  }
}

static success_t
blfSizedStreamClose(SizedStream * const s)
{
  if(s->mFile != NULL) {
    fclose(s->mFile);
    s->mFile = NULL;
  }
  if(s->mBuffer != NULL) {
    free(s->mBuffer);
    s->mBuffer = NULL;
  }
  return 1;
}

static success_t
blfSizedStreamUpdateBytesLeft(SizedStream *s, const uint32_t offset)
{
  if(offset > s->mBytesLeft) goto fail;

  s->mBytesLeft -= offset;
  if(s->mBytesLeft == 0) {
    if(s->mBuffer != NULL) {
      free(s->mBuffer);
      s->mBuffer = NULL;
    }
    fclose(s->mFile);
    s->mFile = NULL;
  }
  return 1;

fail:
  return 0;
}

success_t
blfSizedStreamDetermineBytesLeft(SizedStream *const s)
{
  return blfFileGetRemainingFileSize(s->mFile, &s->mBytesLeft);
}

success_t
blfSizedStreamInitFromFile(SizedStream *const s, FILE *const fp)
{
  if(fp == NULL) {
    fprintf(stderr, "blfSizedStreamFileOpen(): file pointer is NULL\n");
    goto fail;
  }
  s->mFile = fp;
  if(!blfSizedStreamDetermineBytesLeft(s)) goto fail;
  return 1;

fail:
  return 0;
}

/*******************************************************************
 * blfDualStream: management of two streams, one file stream and one
 * memory stream. Data is initially read from the file stream. When
 * a compressed log object is encountered, the memory stream is
 * filled with the uncompressed log data and subsequent read
 * operations retrieve data from the memory stream. When the memory
 * stream is drained, data is again read from the file stream.
 *******************************************************************/
void
blfDualStreamInit (DualStream *const ds)
{
  blfSizedStreamInit(&ds->fileStream);
  blfSizedStreamInit(&ds->memStream);
}

success_t
blfDualStreamClose(DualStream *ds)
{
  success_t success;

  success = blfSizedStreamClose(&ds->fileStream);
  success = blfSizedStreamClose(&ds->memStream) && success;
  return success;
}

int
blfDualStreamIsEmpty(const DualStream *const ds)
{
  return blfSizedStreamIsEmpty(&ds->fileStream) && blfSizedStreamIsEmpty(&ds->memStream);
}

/* select Stream: use fileStream if indicated by flag or if memStream is empty */
static SizedStream *
blfDualStreamGetSizedStream(DualStream *ds, const int fileOnly)
{
  if(fileOnly || blfSizedStreamIsEmpty(&ds->memStream)) {
    return &ds->fileStream;
  } else {
    return &ds->memStream;
  }
}

uint32_t
blfDualStreamBytesLeft(DualStream *ds)
{
  return blfSizedStreamBytesLeft(blfDualStreamGetSizedStream(ds, 0));
}

success_t
blfDualStreamReduceBytesLeft(DualStream *ds, const uint32_t offset)
{
  return blfSizedStreamUpdateBytesLeft(blfDualStreamGetSizedStream(ds, 0), offset);
}

success_t
blfDualStreamReadOrSkip(DualStream *ds, void *dest, size_t nBytes, int fileOnly)
{
  return blfSizedStreamReadOrSkip(blfDualStreamGetSizedStream(ds, fileOnly), dest, nBytes);
}
