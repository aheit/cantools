# configuration cantools                        -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

# Copyright (C) 2007-2017 Andreas Heitmann

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.


AC_PREREQ(2.69)
AC_INIT(cantools, 0.24, andreas.heitmann@gmail.com)
AC_CONFIG_SRCDIR([src/libcandbc/parser.y])
AC_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE([subdir-objects])
AC_CONFIG_MACRO_DIR([m4])
AC_LIBTOOL_WIN32_DLL
AC_USE_SYSTEM_EXTENSIONS

dnl common library version
version_info='0:24:0'
AC_SUBST(version_info)

# Checks for programs.
 	
# Turn off shared libraries during beta-testing, since they
# make the build process take too long.
LT_INIT([disable_shared])
AC_PROG_LIBTOOL

AC_SUBST(LIBTOOL_DEPS)
AC_PROG_YACC
AC_PROG_CC
AC_PROG_CXX
AC_PROG_LEX
AC_PROG_INSTALL
AC_PROG_AWK
AC_PROG_CPP
AC_PROG_MKDIR_P
LT_INIT
AC_PROG_LN_S
AC_PROG_RANLIB

# Checks for functions
AC_REPLACE_FUNCS([strtok_r])
AC_CHECK_DECLS([strtok_r],
 , , [
#include <stdio.h>
#include <string.h>
#ifdef HAVE_STRINGS_H
# include <strings.h>
#endif])

AH_BOTTOM([
#if !HAVE_DECL_STRTOK_R
extern char *strtok_r (char *s, const char *delim, char **save_ptr);
#endif
])

AC_REPLACE_FUNCS([strndup])
AC_CHECK_DECLS([strndup],,,[#include <string.h>])
if test $ac_cv_have_decl_strndup = no; then
    HAVE_DECL_STRNDUP=0
fi
if test $ac_cv_func_strndup = yes; then
    HAVE_STRNDUP=1
else
    HAVE_STRNDUP=0
fi
AH_BOTTOM([
#if !HAVE_DECL_STRNDUP
#include <stddef.h>
extern char *strndup (const char *s, size_t n);
#endif
])

# workaround for missing LINE_MAX definition
AC_MSG_CHECKING(if LINE_MAX is defined)
AC_EGREP_CPP(yes,
[#include <limits.h>
#ifdef LINE_MAX
yes
#endif
], line_max_defined=yes, line_max_defined=no)
AC_MSG_RESULT($line_max_defined)

if test "$line_max_defined" = "no"; then
   CFLAGS="$CFLAGS -DLINE_MAX=2048"
fi

# Checks for header files.
AC_FUNC_ALLOCA
AC_FUNC_FSEEKO
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_STRNLEN
AC_FUNC_STRTOD
AC_CHECK_HEADERS([fcntl.h inttypes.h libintl.h limits.h malloc.h stddef.h \
                  stdint.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT8_T
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_OFF_T
AC_TYPE_SIZE_T
AC_TYPE_UINT8_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_C_CONST
AC_C_BIGENDIAN

# check availability of arithmetic right shift
AC_DEFUN([AX_C_ARITHMETIC_RSHIFT], [
  AC_CACHE_CHECK([whether right shift operation is arithmetic],
                 [ax_cv_c_arithmetic_rshift],
                 [AC_COMPILE_IFELSE([
 		 AC_LANG_SOURCE([[int dummy[((-1 >> 1) < 0) ? 1 : -1];]])
			     ],
                                    [ax_cv_c_arithmetic_rshift=yes],
                                    [ax_cv_c_arithmetic_rshift=no])])
  if test "x$ax_cv_c_arithmetic_rshift" = xyes; then
    AC_DEFINE([HAVE_ARITHMETIC_RSHIFT], [1],
              [Define to 1 if the right shift operation is arithmetic.])
  fi
])
AX_C_ARITHMETIC_RSHIFT

# Checks for libraries
AC_CHECK_LIB([hdf5], [H5Fcreate], AC_SUBST([HDF5_LIB], [-lhdf5]), ,-lz)
AC_CHECK_LIB([m], [floor], AC_SUBST([Z_LIB], [-lz]))
AC_CHECK_LIB([z], [deflate])

AM_WITH_DMALLOC

AC_ARG_ENABLE(efence,
[  --enable-efence         Use electric fence (www.perens.com)],
[case "$enableval" in \
	yes)  efence=yes ;; \
	no)   efence=no;; \
	*)    efence=no;; \
esac], [efence=no])

# Check for efence
if test $efence = yes; then
AC_CHECK_LIB(efence,memalign)
fi

#
# Configure check for unit testing
#
PKG_CHECK_MODULES([CHECK], [check >= 0.9.0])
PKG_CHECK_MODULES([GLIB],  [glib-2.0 >= 2.0])
PKG_CHECK_MODULES([MATIO], [matio >= 1.5])
PKG_CHECK_MODULES([ZLIB],  [zlib >= 1.2])
#PKG_CHECK_MODULES([HDF5], [hdf5 >= 1.8])
 
# Checks for library functions.
#AC_FUNC_ERROR_AT_LINE
AC_HEADER_ASSERT
AC_FUNC_MMAP
AC_CHECK_FUNCS([memset munmap strchr strdup strndup strpbrk strspn strstr strtol strtoul])
AC_CONFIG_FILES([Makefile tests/Makefile])
AC_OUTPUT

AM_WITH_DMALLOC
