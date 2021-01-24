/*  blfapi.c -- API for BLF access
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

#include <stdlib.h>
#include <string.h>

#include "blfapi.h"
#include "blfparser.h"

/* read object header base of next object */
success_t
blfPeekObject(BLFHANDLE h, VBLObjectHeaderBase* pBase)
{
  if(!blfHandleIsInitialized(h)) goto fail;
  if(pBase == 0) goto fail;
  if(!blfPeekObjectInternal(h, pBase)) goto fail;
  return 1;

fail:
  return 0;
}

/* open a BLF file for reading */
BLFHANDLE
blfCreateFile(FILE *fp)
{
  BLFHANDLE h = (BLFHANDLE)malloc(sizeof(*h));

  if(h == NULL) goto fail;
  blfHandleInit(h);
  if(!blfHandleOpen(h, fp)) goto fail;
  return h;

fail:
  if(h != NULL) free(h);
  fprintf(stderr,"blfCreateFile() failed\n");
  return NULL;
}

/* close BLFHANDLE */
success_t
blfCloseHandle(BLFHANDLE h)
{
  return    blfHandleIsInitialized(h)
         && blfHandleClose(h);
}

/* retrieve VBLFileStatisticsEx data */
success_t
blfGetFileStatisticsEx(BLFHANDLE h, VBLFileStatisticsEx* pStatistics)
{
  unsigned int nBytes;

  if(!blfHandleIsInitialized(h)) goto fail;
  if(pStatistics == NULL) goto fail;

  nBytes = BLFMIN(h->mStatistics.mStatisticsSize, pStatistics->mStatisticsSize);
  memcpy(pStatistics, &h->mStatistics, nBytes);
  pStatistics->mStatisticsSize = nBytes;
  return 1;

fail:
  return 0;
}

/* read next object */
success_t
blfReadObject(BLFHANDLE hFile, VBLObjectHeaderBase *pBase)
{
  success_t success = 0;

  switch(pBase->mObjectType) {
    case BL_OBJ_TYPE_CAN_DRIVER_ERROR:
    case BL_OBJ_TYPE_CAN_ERROR_EXT:
    case BL_OBJ_TYPE_CAN_MESSAGE:
    case BL_OBJ_TYPE_CAN_MESSAGE2:
    case BL_OBJ_TYPE_CAN_FD_MESSAGE_64:
    case BL_OBJ_TYPE_LOG_CONTAINER:
    case BL_OBJ_TYPE_TRIGGER_CONDITION:
      success = blfHandleRead(hFile, 0, (uint8_t *)&pBase[1],
          pBase->mObjectSize - sizeof(*pBase));
      break;
    default:
      fprintf(stderr, "blfReadObject: mObjectType not "
                "implemented: %d\n", pBase->mObjectType);
      success = 0;
      break;
  }

  if(success) {
    hFile->mStatistics.mObjectsRead++;
  }

  return success;
}

/* read next object into size-limited memory */
success_t
blfReadObjectSecure(BLFHANDLE h, VBLObjectHeaderBase* pBase,
        size_t expectedSize)
{
  if(!blfHandleIsInitialized(h)) goto fail;

  if(pBase == NULL)              goto fail;

  if(pBase->mObjectSize > expectedSize) {
    /* allocate additional memory to read from handle */
    VBLObjectHeaderBase *obj =
      (VBLObjectHeaderBase *)malloc(pBase->mObjectSize);
    if(obj == NULL) {
      fprintf(stderr, "Allocation of VBLObjectHeaderBase "
        "with size %u failed.",(uint32_t)pBase->mObjectSize);
      goto fail;
    }
    blfVBLObjectHeaderBaseCopy(obj, pBase);
    if(!blfReadObject(h, obj)) {
       free(obj);
       goto fail;
    }

    /* copy expected bytes back to pBase */
    memcpy(pBase, obj, expectedSize);
  } else {
    if(!blfReadObject(h, pBase)) goto fail;

    /* less bytes read than expected? -> clear remaining bytes */
    if(pBase->mObjectSize < expectedSize) {
      blfMemZero((uint8_t *)pBase + pBase->mObjectSize,
     expectedSize - (size_t)pBase->mObjectSize);
    }
  }
  return 1;

fail:
  return 0;
}

/* free object data */
success_t
blfFreeObject(BLFHANDLE h, VBLObjectHeaderBase* pBase)
{
  return blfHandleIsInitialized(h)
      && (pBase != NULL)
      && blfFreeHeader(h, (VBLObjectHeader *)pBase);
}

/* skip next object */
success_t
blfSkipObject(BLFHANDLE h, VBLObjectHeaderBase* pBase)
{
  success_t success;
  uint32_t skipPadding = 1;

  if(pBase->mObjectType == BL_OBJ_TYPE_TRIGGER_CONDITION) skipPadding = 0;

  success = 
           blfHandleIsInitialized(h)
        && (pBase != NULL)
        && (pBase->mObjectSize >= pBase->mHeaderSize)
        && blfHandleSkip(h, pBase->mObjectSize - 16, skipPadding);
  if(success) {
    h->mStatistics.mObjectsRead++;
  }
  return success;
}
