#ifndef INCLUDE_BLFPARSER_H
#define INCLUDE_BLFPARSER_H

/*  blfparser.h --  declarations for blfReader
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

#include <stdio.h>

#include "blfstream.h"
#include "blfapi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BLHANDLE_MAGIC    0x01234567

#define BL_OBJ_SIGNATURE  0x4A424F4C       /* 'LOBJ' */
#define BL_LOGG_SIGNATURE 0x47474F4C       /* 'LOGG' */

void      blfMemZero(uint8_t *mem, const size_t n);
success_t blfHandleIsInitialized(BLFHANDLE h);
success_t blfPeekObjectInternal(BLFHANDLE hFile, VBLObjectHeaderBase *pBase);
BLFHANDLE  blfHandleInit(BLFHANDLE this);
success_t blfHandleOpen(BLFHANDLE h, FILE *fp);
success_t blfHandleRead(BLFHANDLE h, uint8_t fileOnlyBit, uint8_t *dest_ptr,
                        uint32_t nBytes);
success_t blfFreeHeader(BLFHANDLE hFile, VBLObjectHeader *pBase);
success_t blfHandleSkip(BLFHANDLE h, uint32_t nBytes, uint32_t skipPadding);
void      blfVBLObjectHeaderBaseCopy (VBLObjectHeaderBase *const dest,
                                      const VBLObjectHeaderBase *const source);
success_t blfHandleClose(BLFHANDLE h);

#ifdef __cplusplus
}
#endif

#endif
