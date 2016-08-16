# configuration cantools                        -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

# Copyright (C) 2007-2016 Andreas Heitmann

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
AC_INIT(cantools, 0.17, andreas.heitmann@gmail.com)
AC_CONFIG_SRCDIR([src/libcandbc/parser.y])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([subdir-objects])
AC_CONFIG_MACRO_DIR([m4])
AC_LIBTOOL_WIN32_DLL

dnl common library version
version_info='0:17:0'
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
AC_CHECK_HEADERS([fcntl.h inttypes.h libintl.h limits.h malloc.h stddef.h stdint.h stdlib.h string.h unistd.h endian.h])

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

AC_SUBST(MATIO_LIB)
matio=1
AC_CHECK_HEADER(matio.h, [], [matio=0])
AC_CHECK_LIB(matio, Mat_VarCreate, [matio=matio], [matio=0], -lhdf5 -lz)
if test $matio == 0
then
	echo "Error! You need to install libmatio, hdf5, and first."
        exit -1
else
	MATIO_LIB=-lmatio
fi

AM_WITH_DMALLOC

AC_ARG_ENABLE(clg,
[  --enable-clg            Enable CLG file format],
[case "$enableval" in \
	yes)  enable_clg=yes ;; \
	no)   enable_clg=no;; \
	*)    enable_clg=no;; \
esac], [enable_clg=no])

# pass option to Makefile.am
AM_CONDITIONAL([ENABLE_CLG], [test "$enable_clg" = "yes"])

# Check for CLG library
if test $enable_clg = yes; then
clg_available=1
AC_CHECK_FILE([src/libcanclg/clgReader.h], [], [clg_available=0])
if test $clg_available == 0
then
	echo "Error! CLG source not installed."
        exit -1
fi
fi

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
 
# Checks for library functions.
#AC_FUNC_ERROR_AT_LINE
AC_HEADER_ASSERT
AC_FUNC_MMAP
AC_CHECK_FUNCS([memset munmap strchr strdup strndup strpbrk strspn strstr strtol strtoul])
AC_CONFIG_FILES([Makefile tests/Makefile])
AC_OUTPUT

