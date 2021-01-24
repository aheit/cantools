/*  blfparser.c --  parse BLF files
    Copyright (C) 2016-2021 Andreas Heitmann

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
#include <inttypes.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <zlib.h>
#include <assert.h>

#include "blfparser.h"
#include "blfapi.h"

/* clear memory */
void
blfMemZero(uint8_t *mem, const size_t n)
{
  memset((char *)mem, 0, n);
}

/* in-memory zlib uncompress */
static success_t
blfMemUncompress(uint8_t  *next_out,
     uint32_t  avail_out,
     uint8_t  *next_in,
     uint32_t  avail_in,
     uint32_t *total_out_ptr)
{
  int zres;
  z_stream stream;

  stream.next_in = next_in;
  stream.avail_in = avail_in;
  stream.next_out = next_out;
  stream.avail_out = avail_out;
  stream.total_out = 0;
  stream.state = NULL;
  stream.zalloc = NULL;
  stream.zfree = NULL;

  zres = inflateInit_(&stream, ZLIB_VERSION, sizeof(stream));
  if(zres == Z_OK) zres = inflate(&stream, Z_FINISH);
  if(zres == Z_STREAM_END) zres = Z_OK;
  if(zres == Z_OK) {
    inflateEnd(&stream);
    if(total_out_ptr != NULL) {
      *total_out_ptr = stream.total_out;
    }
  }
  return zres == Z_OK;
}

/* initialize SYSTEMTIME structure */
static void
blfSystemTimeInit(SYSTEMTIME *const s)
{
  s->wYear = 0;
  s->wMonth = 0;
  s->wDayOfWeek = 0;
  s->wDay = 0;
  s->wHour = 0;
  s->wMinute = 0;
  s->wSecond = 0;
  s->wMilliseconds = 0;
}

/* initialize LOGG structure */
static void
blfLOGGInit(LOGG l)
{
  l->mSignature = 0;
  l->mHeaderSize = 0;
  l->mCRC = 0;
  l->appID = 0;
  l->dwCompression = 0;
  l->appMajor = 0;
  l->appMinor = 0;
  l->fileSize = 0;
  l->uncompressedFileSize = 0;
  l->objectCount = 0;
  l->appBuild = 0;
  blfSystemTimeInit(&l->mMeasurementStartTime);
  blfSystemTimeInit(&l->mMeasurementEndTime);
}

/* initialize VBLFileStatisticsEx structure */
static void
blfStatisticsInit(VBLFileStatisticsEx *const s)
{
  s->mStatisticsSize = 0x88u;
  s->mApplicationID = 0;
  s->mApplicationMajor = 0;
  s->mApplicationMinor = 0;
  s->mApplicationBuild = 0;
  s->mFileSize = 0;
  s->mUncompressedFileSize = 0;
  s->mObjectCount = 0;
  s->mObjectsRead = 0;
  blfSystemTimeInit(&s->mMeasurementStartTime);
  blfSystemTimeInit(&s->mLastObjectTime);
  assert(sizeof(s->mReserved) == 0x48);
  blfMemZero((uint8_t *)(s->mReserved),
            sizeof(s->mReserved));
}

/*
 * read bytes from either file or memory stream, or skip bytes, if
 * dest pointer is NULL
 */
static success_t
blfHandleReadOrSkip(BLFHANDLE h, uint8_t *dest,
        uint32_t totalBytesToRead)
{
  uint8_t *destPtr = dest;
  uint32_t alreadyRead = 0;
  uint32_t srcBytesLeft;
  size_t wantToRead;
  int addToDest;
  size_t actuallyRead;
  uint32_t totalRead = 0;
  VBLObjectHeaderBase pBase;
  DualStream *const ds = &h->mDualStream;

  /* loop until all bytes are read or dual stream is empty */
  while(alreadyRead < totalBytesToRead) {
    srcBytesLeft = blfDualStreamBytesLeft(ds);

    if(srcBytesLeft) {
      int memStreamNotEmpty;

      /*
       * We want to read all remaining bytes, but not more than what is
       * left in the current stream. If the Stream is drained and there are
       * more bytes to read, we'll try to read them in the next loop.
       */
      wantToRead = BLFMIN(totalBytesToRead - alreadyRead, srcBytesLeft);
      if(!blfDualStreamReadOrSkip(ds, destPtr, wantToRead, 0)) goto fail;
      addToDest = actuallyRead = wantToRead;
      if(actuallyRead == 0) goto fail;

      memStreamNotEmpty = !blfSizedStreamIsEmpty(&ds->memStream);

      if(!blfDualStreamReduceBytesLeft(ds, actuallyRead)) goto fail;

      /*
       * when MemStream went from non-empty to empty,
       * peek next object (in FileStream)
       */
      if(memStreamNotEmpty) {
        if(blfSizedStreamIsEmpty(&ds->memStream)) {
          h->mPeekFlag = 1;
          blfPeekObject(h, &pBase);
          h->mPeekFlag = 0;
          addToDest = actuallyRead;
        }
      }
      if(destPtr != NULL) {
        destPtr    += addToDest;
      }
      alreadyRead = addToDest + totalRead;
      totalRead  += addToDest;
    } else {
      if(!blfSizedStreamDetermineBytesLeft(&ds->fileStream)) goto fail;
    }
  }
  return 1;

fail:
  return 0;
}

/* read nBytes */
success_t
blfHandleRead(BLFHANDLE h, uint8_t fileOnlyBit, uint8_t *dest_ptr,
        uint32_t nBytes)
{
  DualStream *const ds = &h->mDualStream;
  success_t success;

  if(!(fileOnlyBit & 1) && blfSizedStreamIsOpen(&ds->fileStream)) {
    success = blfHandleReadOrSkip(h, dest_ptr, nBytes);
  } else {
    /* TODO: do we need an extra function for this? */
    success = blfDualStreamReadOrSkip(ds, dest_ptr, nBytes, 1);
  }
  return success;
}

/* skip 1 to 3 bytes to achieve 4 byte alignment  */
success_t
blfHandleSkipPadding(BLFHANDLE h, uint32_t nBytes)
{
  return ((nBytes & 3) == 0) || blfHandleRead(h, 0, NULL, nBytes & 3);
}

/* unpack compressed VBLObjectHeaderBaseLOGG payload if required  */
success_t
blfLOGGUncompress(VBLObjectHeaderBaseLOGG* hbaselogg,
      uint8_t **bufPtr, uint32_t *sizePtr)
{
  if(hbaselogg->compressedflag == 2) {
    uint8_t* uncompressedData;
    success_t suc;

    uncompressedData = (uint8_t *)malloc(hbaselogg->deflatebuffersize);
    if(uncompressedData == NULL) {
      fprintf(stderr, "blfLOBJReadPayload: malloc failed\n");
      goto fail;
    }
    suc = blfMemUncompress(uncompressedData,
         hbaselogg->deflatebuffersize, *bufPtr,
         *sizePtr, 0);

    /* free compressed data */
    free(*bufPtr);

    *sizePtr = hbaselogg->deflatebuffersize;
    *bufPtr = uncompressedData;
    if(!suc) {
      fprintf(stderr, "blfMemUncompress failed\n");
      goto fail;
    }
  } else {
    /* nothing to do. sizePtr and bufPtr point to the non-compressed data */
  }
  return 1;

fail:
  return 0;
}

/* read payload of VBLObjectHeaderBaseLOGG structure */
success_t
blfHandleReadLOGG(VBLObjectHeaderBaseLOGG *hbaselogg, BLFHANDLE h)
{
  uint32_t nObjectData;
  uint8_t *objectData = NULL;
  DualStream *const ds = &h->mDualStream;

  /* nothing to do, if object is not a LOG container */
  if(hbaselogg->base.mObjectType != BL_OBJ_TYPE_LOG_CONTAINER) goto success;

  /* fail, if memStream is not drained yet */
  if(blfSizedStreamIsOpen(&ds->memStream))                     goto fail;

  /* complete reading of VBLHeaderBaseLOGG */
  if(!blfHandleRead(h, 0, (uint8_t *)&hbaselogg->compressedflag,
        sizeof(*hbaselogg) - hbaselogg->base.mHeaderSize))     goto fail;

  /* allocate object data */
  nObjectData = hbaselogg->base.mObjectSize - sizeof(*hbaselogg);
  if(NULL == (objectData = (uint8_t *)malloc(nObjectData)))    goto fail;

  /* read object data */
  if(!blfHandleRead(h, 0, objectData, nObjectData))            goto fail;
  if(!blfHandleSkipPadding(h, nObjectData))                    goto fail;

  /* uncompress, if compressed */
  if(!blfLOGGUncompress(hbaselogg, &objectData, &nObjectData)) goto fail;

  /* establish new memStream */
  if(0 == blfSizedStreamInitFromMem(&ds->memStream,
                                    objectData, nObjectData))  goto fail;

  /* peek next object, if required */
  if(   (h->mPeekFlag == 0)
     && (!blfPeekObject(h, &(hbaselogg->base))))               goto fail;

success:
  return 1;

fail:
  if(objectData != NULL) free(objectData);
  return 0;
}

/* debug: dump VBLObjectHeaderBase structure */
void
blfHeaderBaseDump(VBLObjectHeaderBase *b)
{
  printf("header.base.mSignature = %c%c%c%c\n",
      ((uint8_t *)&b->mSignature)[0],
      ((uint8_t *)&b->mSignature)[1],
      ((uint8_t *)&b->mSignature)[2],
      ((uint8_t *)&b->mSignature)[3]);
  printf("header.base.mHeaderSize    = %d\n",b->mHeaderSize);
  printf("header.base.mHeaderVersion = %d\n",b->mHeaderVersion);
}

void
bldHeaderDump(VBLObjectHeaderBaseLOGG *h)
{
  blfHeaderBaseDump(&(h->base));
  printf("compressedflag = %u\n",h->compressedflag);
  printf("reserved1      = %u\n",h->reserved1);
  printf("defl.buffer.sz = %u\n",h->deflatebuffersize);
  printf("reserved2      = %u\n",h->reserved2);
}


/* copy VBLObjectHeaderBase structure and change CAN message version, if requested */
void
blfVBLObjectHeaderBaseInit(VBLObjectHeaderBase *pBase,
         VBLObjectHeaderBase *base,
         int forceCANMessageV1)
{
  *pBase = *base;

  /* enforce CAN Message V1 format, if requested */
  if(forceCANMessageV1 && (pBase->mObjectType == BL_OBJ_TYPE_CAN_MESSAGE2)) {
    pBase->mObjectType = BL_OBJ_TYPE_CAN_MESSAGE;
  }
}

success_t
blfPeekObjectInternal(BLFHANDLE hFile, VBLObjectHeaderBase *pBase)
{
  VBLObjectHeaderBaseLOGG header;

  /* read signature */
  if(!blfHandleRead(hFile, 0, (uint8_t *)&header, 8u)) goto fail;

  /* check signature */
  if(header.base.mSignature != BL_OBJ_SIGNATURE) {
    printf("incorrect BL_OBJ_SIGNATURE = %08" PRIx32 "\n",
           header.base.mSignature);
    bldHeaderDump(&header);
    goto fail;
  }

  /* read size and type */
  if(!blfHandleRead(hFile, 0,
             (uint8_t *)&header.base.mObjectSize, 8u)) goto fail;

  /* read payload */
  if(!blfHandleReadLOGG(&header, hFile))              goto fail;

  /* copy to target structure */
  blfVBLObjectHeaderBaseInit(pBase, &header.base,
                             hFile->mCANMessageFormat_v1);

  return 1;

fail:
  return 0;
}

/* fill VBLFileStatisticsEx structure from LOGG structure */
void
blfStatisticsFromLOGG(VBLFileStatisticsEx *const s, const LOGG_t *const l)
{
  s->mApplicationID        = l->appID;
  s->mApplicationMajor     = l->appMajor;
  s->mApplicationMinor     = l->appMinor;
  s->mFileSize             = l->fileSize;
  s->mUncompressedFileSize = l->uncompressedFileSize;
  s->mObjectCount          = l->objectCount;
  s->mApplicationBuild     = l->appBuild;
  s->mMeasurementStartTime = l->mMeasurementStartTime;
  s->mLastObjectTime       = l->mMeasurementEndTime;
}

/* decoding on big endian machines requires byte swapping - not yet implemented */
static void
blfCheckEndian(void)
{
#ifdef WORDS_BIGENDIAN
  perror("BLF decoding currently unsupported on big endian machines.");
  exit(EXIT_FAILURE);
#endif
}

/* diagnose structure sizes to ensure that we can fread into them */
static void
blfCheckStructures(void)
{
  assert(sizeof(VBLObjectHeaderBaseLOGG) == 32);
  assert(sizeof(LOGG_t) == 144);
  assert(sizeof(VBLObjectHeaderBase) == 16);
  assert(sizeof(VBLObjectHeader) == 32);
  assert(sizeof(VBLObjectHeaderBaseLOGG) == 32);
  assert(sizeof(VBLCANMessage) == 48);
  assert(sizeof(VBLFileStatisticsEx) == 136);
}

/* initialize BLFHANDLE */
BLFHANDLE
blfHandleInit(BLFHANDLE this)
{
  blfCheckEndian();
  blfCheckStructures();
  blfLOGGInit(&this->mLOGG);
  this->magic = BLHANDLE_MAGIC;

  this->mCANMessageFormat_v1 = 0;
  blfDualStreamInit(&this->mDualStream);
  this->mPeekFlag = 0;
  blfStatisticsInit(&(this->mStatistics));

  return this;
}

/* check, if BLFHANDLE is initialized */
success_t
blfHandleIsInitialized(BLFHANDLE h)
{
  return (h!=NULL) && (h->magic == BLHANDLE_MAGIC);
}

/* close BLFHANDLE */
success_t
blfHandleClose(BLFHANDLE h)
{
  return blfDualStreamClose(&h->mDualStream);
}

/* skip forward nBytes */
success_t
blfHandleSkip(BLFHANDLE h, uint32_t nBytes, uint32_t skipPadding)
{
  success_t success;
  DualStream *const ds = &h->mDualStream;

  if(!blfDualStreamIsEmpty(&h->mDualStream)) {
    success = blfHandleReadOrSkip(h, 0, nBytes);
  } else {
    success = blfDualStreamReadOrSkip(ds, NULL, nBytes, 1);
  }
  if(success) {
    if(skipPadding) {
      success = blfHandleSkipPadding(h, nBytes);
    }
  }
  return success;
}

/* associate BLFHANDLE with a FILE and read header and statistics */
success_t
blfHandleOpen(BLFHANDLE h, FILE *fp)
{
  uint32_t nLOGGFile;
  uint32_t nRead;
  int32_t nSkip;
  const uint32_t nSignatureAndHeader =
      sizeof(h->mLOGG.mSignature) + sizeof(h->mLOGG.mHeaderSize);

  h->mCANMessageFormat_v1 = 0;

  if(!blfSizedStreamInitFromFile(&h->mDualStream.fileStream, fp)) goto fail;

  /* read signature and header size */
  if(!blfHandleRead(h, 1, (uint8_t *)&h->mLOGG.mSignature, nSignatureAndHeader)) {
    goto fail;
  }

  /* check signature */
  if(h->mLOGG.mSignature != BL_LOGG_SIGNATURE) {
    fprintf(stderr, "blfOpenLOGG: LOGG signature not found\n");
    goto fail;
  }

  /* read remaining bytes, but no more than size of LOGG structure */
  nLOGGFile =   h->mLOGG.mHeaderSize - nSignatureAndHeader;
  nRead     =   BLFMIN(sizeof(h->mLOGG), h->mLOGG.mHeaderSize)
        - nSignatureAndHeader;
  nSkip = nLOGGFile - nRead;
  if(nLOGGFile > 0) {
    if(!blfHandleRead(h, 1, (uint8_t *)&h->mLOGG.mCRC, nRead)) goto fail;
  }

  /* if file structure is larger than memory structure, skip the rest
     of the file structure */
  if(nSkip > 0) {
    if(!blfHandleSkip(h, nSkip, 1)) {
      goto fail;
    }
  }

  blfStatisticsFromLOGG(&h->mStatistics, &h->mLOGG);
  return 1;

fail:
  return 0;
}

/* copy VBLObjectHeaderBase */
void
blfVBLObjectHeaderBaseCopy(      VBLObjectHeaderBase *const dest,
                           const VBLObjectHeaderBase *const source)
{
  *dest = *source;
}

/* free VBLObjectHeader */
success_t
blfFreeHeader(BLFHANDLE hFile, VBLObjectHeader *pBase)
{
  switch(pBase->mBase.mObjectType) {
    case BL_OBJ_TYPE_CAN_MESSAGE:
    case BL_OBJ_TYPE_LOG_CONTAINER:
    case BL_OBJ_TYPE_CAN_DRIVER_ERROR:
    case BL_OBJ_TYPE_CAN_ERROR_EXT:
    case BL_OBJ_TYPE_CAN_MESSAGE2:
    case BL_OBJ_TYPE_CAN_FD_MESSAGE_64:
      /* no additional memory to be freed */
      break;
    default:
      break;
  }
  return 1;
}
