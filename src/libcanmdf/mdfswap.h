#ifndef MDF_SWAP_H
#define MDF_SWAP_H

/* mdfswap_swap.h -- Handle swapping for cantools -*- C++ -*-

   Copyright (C) 2006-2017 Free Software Foundation, Inc.
   Written by Ian Lance Taylor <iant@google.com>.

   This file is part of cantools.
   
   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License
   as published by the Free Software Foundation; either version 2, or
   (at your option) any later version.

   In addition to the permissions in the GNU Library General Public
   License, the Free Software Foundation gives you unlimited
   permission to link the compiled version of this file into
   combinations with other programs, and to distribute those
   combinations without any restriction coming from the use of this
   file.  (The Library Public License restrictions do apply in other
   respects; for example, they cover modification of the file, and
  / distribution when not linked into a combined executable.)

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA
   02110-1301, USA. */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef HAVE_INTTYPES_H
# include <inttypes.h>
#endif
#ifdef HAVE_STDINT_H
# include <stdint.h>
#endif

/* gcc 4.3 and later provides __builtin_bswap32 and __builtin_bswap64. */

#if defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))
#define mdf_bswap_32 __builtin_bswap32
#define mdf_bswap_64 __builtin_bswap64
#else

/* Provide our own versions of the byteswap functions. */
inline uint16_t
mdf_bswap_16(uint16_t v)
{
  return ((v >> 8) & 0xff) | ((v & 0xff) << 8);
}

inline uint32_t
mdf_bswap_32(uint32_t v)
{
  return (  ((v & 0xff000000) >> 24)
	  | ((v & 0x00ff0000) >>  8)
	  | ((v & 0x0000ff00) <<  8)
	  | ((v & 0x000000ff) << 24));
}

inline uint64_t
mdf_bswap_64(uint64_t v)
{
  return (  ((v & 0xff00000000000000ULL) >> 56)
	  | ((v & 0x00ff000000000000ULL) >> 40)
	  | ((v & 0x0000ff0000000000ULL) >> 24)
	  | ((v & 0x000000ff00000000ULL) >>  8)
	  | ((v & 0x00000000ff000000ULL) <<  8)
	  | ((v & 0x0000000000ff0000ULL) << 24)
	  | ((v & 0x000000000000ff00ULL) << 40)
	  | ((v & 0x00000000000000ffULL) << 56));
}
#endif /* !GNU >= 4.3 */
#endif /* !defined(MDF_SWAP_H) */
