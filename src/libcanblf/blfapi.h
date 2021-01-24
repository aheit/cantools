#ifndef INCLUDE_BLFAPI_H
#define INCLUDE_BLFAPI_H

/*  blfapi.h --  declarations for BLF API
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

#ifdef HAVE_INTTYPES_H
# include <inttypes.h>
#endif
#ifdef HAVE_STDINT_H
# include <stdint.h>
#endif

#include "blfstream.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BL_OBJ_TYPE_CAN_MESSAGE            1
#define BL_OBJ_TYPE_CAN_STATISTIC          4
#define BL_OBJ_TYPE_LOG_CONTAINER         10
#define BL_OBJ_TYPE_CAN_DRIVER_ERROR      31
#define BL_OBJ_TYPE_CAN_ERROR_EXT         73
#define BL_OBJ_TYPE_CAN_MESSAGE2          86
#define BL_OBJ_TYPE_CAN_FD_MESSAGE       100  
#define BL_OBJ_TYPE_CAN_FD_MESSAGE_64    101
#define BL_OBJ_TYPE_TRIGGER_CONDITION    128

#define BL_OBJ_FLAG_TIME_TEN_MICS 1
#define BL_OBJ_FLAG_TIME_ONE_NANS       2

typedef struct __attribute__ ((__packed__)) {
  uint16_t wYear;
  uint16_t wMonth;
  uint16_t wDayOfWeek;
  uint16_t wDay;
  uint16_t wHour;
  uint16_t wMinute;
  uint16_t wSecond;
  uint16_t wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;

typedef struct __attribute__ ((__packed__)) {
  uint32_t mSignature;
  uint32_t mHeaderSize;
  uint32_t mCRC;
  uint8_t  appID;
  uint8_t  dwCompression;
  uint8_t  appMajor;
  uint8_t  appMinor;
  uint64_t fileSize;
  uint64_t uncompressedFileSize;
  uint32_t objectCount;
  uint8_t  appBuild;
  uint8_t  mReserved1;
  uint8_t  mReserved2;
  uint8_t  mReserved3;
  SYSTEMTIME mMeasurementStartTime;
  SYSTEMTIME mMeasurementEndTime;
  uint8_t  mReserved4[72];
} *LOGG, LOGG_t;

typedef struct __attribute__ ((__packed__)) {
  uint32_t  mSignature;         /*  0: "LOBJ" BL_OBJ_SIGNATURE */
  uint16_t  mHeaderSize;        /*  4: header size */
  uint16_t  mHeaderVersion;     /*  6: 1=VBLObjectHeader, 2=VBLObjectHeader2*/
  uint32_t  mObjectSize;        /*  8: object size*/
  uint32_t  mObjectType;        /* 12: block type */
} VBLObjectHeaderBase;          /* 16 */

typedef struct __attribute__ ((__packed__)) {
  VBLObjectHeaderBase mBase;
  uint32_t  mObjectFlags;       /* 16 */
  uint16_t  mReserved;          /* 20 */
  uint16_t  mObjectVersion;     /* 22 */
  uint64_t  mObjectTimeStamp;   /* 24..31 */
} VBLObjectHeader;              /* 32 */


typedef struct __attribute__ ((__packed__)) {
  VBLObjectHeaderBase base;    /*  0: base */
  uint32_t            compressedflag;    /* 16: compressed data=2 */
  uint32_t            reserved1;         /* 20: reserved */
  uint32_t            deflatebuffersize; /* 24: uncompressed size*/
  uint32_t            reserved2;         /* 28: reserved */
} VBLObjectHeaderBaseLOGG;     /* 32 */

typedef struct __attribute__ ((__packed__)) {
  VBLObjectHeader mHeader;     /*  0: header */
  uint16_t        mChannel;    /* 32: channel*/
  uint8_t         mFlags;      /* 34: flags */
  uint8_t         mDLC;        /* 35: DLC */
  uint32_t        mID;         /* 36: message ID*/
  uint8_t         mData[8];    /* 40 */
} VBLCANMessage;

typedef struct __attribute__ ((__packed__)) {
  VBLObjectHeader mHeader;
  uint16_t        mChannel;
  uint8_t         mFlags;
  uint8_t         mDLC;
  uint32_t        mID;
  uint8_t         mData[8];
  uint32_t        mFrameLength;
  uint8_t         mBitCount;
  uint8_t         mReserved1;
  uint16_t        mReserved2;
} VBLCANMessage2;

typedef struct __attribute__ ((__packed__)) {
  VBLObjectHeader mHeader;
  uint16_t        mChannel;
  uint8_t         mFlags;
  uint8_t         mDLC;
  uint32_t        mID;
  uint32_t        mFrameLength;
  uint8_t         mArbBitCount;
  uint8_t         mCANFDFlags;
  uint8_t         mValidDataBytes;
  uint8_t         mReserved1;
  uint32_t        mReserved2;
  uint8_t         mData[64];
} VBLCANFDMessage;

typedef struct __attribute__ ((__packed__)) {
  VBLObjectHeader mHeader;
  uint8_t         mChannel;
  uint8_t         mDLC;
  uint8_t         mValidDataBytes;
  uint8_t         mTxCount;
  uint32_t        mID;
  uint32_t        mFrameLength;
  uint32_t        mFlags;
  uint32_t        mBtrCfgArb;
  uint32_t        mBtrCfgData;
  uint32_t        mTimeOffsetBrsNs;
  uint32_t        mTimeOffsetCrcDelNs;
  uint16_t        mBitCount;
  uint8_t         mDir;
  uint8_t         mReserved1;                  
  uint32_t        mReserved2; 
  uint8_t         mData[64];
} VBLCANFDMessage64;

typedef struct VBLFileStatistics_t {
  uint32_t  mStatisticsSize;                   /* sizeof (VBLFileStatistics) */
  uint8_t   mApplicationID;                    /* application ID */
  uint8_t   mApplicationMajor;                 /* application major number */
  uint8_t   mApplicationMinor;                 /* application minor number */
  uint8_t   mApplicationBuild;                 /* application build number */
  uint64_t  mFileSize;                         /* file size in bytes */
  uint64_t  mUncompressedFileSize;             /* uncompressed file size in bytes */
  uint32_t  mObjectCount;                      /* number of objects */
  uint32_t  mObVBLFileStatisticsjectsRead;     /* number of objects read */
} VBLFileStatistics;

typedef struct VBLFileStatisticsEx_t {
  uint32_t      mStatisticsSize;               /* sizeof (VBLFileStatisticsEx) */
  uint8_t       mApplicationID;                /* application ID */
  uint8_t       mApplicationMajor;             /* application major number */
  uint8_t       mApplicationMinor;             /* application minor number */
  uint8_t       mApplicationBuild;             /* application build number */
  uint64_t      mFileSize;                     /* file size in bytes */
  uint64_t      mUncompressedFileSize;         /* uncompressed file size in bytes */
  uint32_t      mObjectCount;                  /* number of objects */
  uint32_t      mObjectsRead;                  /* number of objects read */
  SYSTEMTIME    mMeasurementStartTime;         /* measurement start time */
  SYSTEMTIME    mLastObjectTime;               /* last object time */
  uint32_t      mReserved[18];                 /* reserved */
} VBLFileStatisticsEx;

typedef struct {
  uint32_t            magic;
  LOGG_t              mLOGG;
  DualStream          mDualStream;
  uint32_t            mPeekFlag;
  VBLFileStatisticsEx mStatistics;
  uint32_t            mCANMessageFormat_v1;
} *BLFHANDLE;

/* public functions */
success_t blfPeekObject(BLFHANDLE h, VBLObjectHeaderBase* pBase);
BLFHANDLE  blfCreateFile(FILE *fp);
success_t blfCloseHandle(BLFHANDLE h);
success_t blfGetFileStatisticsEx(BLFHANDLE h, VBLFileStatisticsEx* pStatistics);
success_t blfReadObject(BLFHANDLE hFile, VBLObjectHeaderBase *pBase);
success_t blfFreeObject(BLFHANDLE h, VBLObjectHeaderBase* pBase);
success_t blfSkipObject(BLFHANDLE h, VBLObjectHeaderBase* pBase);
success_t blfReadObjectSecure(BLFHANDLE h, VBLObjectHeaderBase* pBase,
                              size_t expectedSize);

#ifdef __cplusplus
}
#endif

#endif
