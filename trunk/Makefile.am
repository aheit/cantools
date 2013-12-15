# Make cantools.					-*-Makefile-*-

# Copyright (C) 2007-2012 Andreas Heitmann

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

## Process this file with automake to produce Makefile.in

AUTOMAKE_OPTIONS= foreign subdir-objects
ACLOCAL_AMFLAGS= -I m4

LEX=@LEX@
YACC=@YACC@

#	
# What to build and install
#
lib_LTLIBRARIES = libcandbc.la libcanasc.la libcanmdf.la
bin_PROGRAMS	= dbccopy dbcls asctomat mdftomat

#
# dbcls
#
dbcls_SOURCES = src/dbcls/dbcls.c
dbcls_LDADD   = libcandbc.la

#
# dbccopy
#
dbccopy_SOURCES = src/dbccopy/dbccopy.c
dbccopy_LDADD	= libcandbc.la

#
# asctomat
#
asctomat_SOURCES = src/asctomat/asctomat.c \
		   src/asctomat/busAssignment.c \
		   src/asctomat/matWrite.c \
		   src/asctomat/messageHash.c \
		   src/asctomat/measurement.c \
		   src/asctomat/signalFormat.c \
		   src/asctomat/measurement.h \
		   src/asctomat/signalFormat.h \
		   src/asctomat/busAssignment.h \
		   src/asctomat/matWrite.h \
		   src/asctomat/messageHash.h \
		   src/hashtable/hashtable.c \
		   src/hashtable/hashtable_itr.c \
		   src/hashtable/hashtable.h \
		   src/hashtable/hashtable_itr.h \
		   src/hashtable/hashtable_private.h

asctomat_LDADD	   = libcandbc.la libcanasc.la $(MATIO_LIB) @LIBOBJS@

#
# mdftomat
#
mdftomat_SOURCES = src/mdftomat/mdftomat.c \
                   src/mdftomat/mdftomat.h

mdftomat_LDADD	   = libcanmdf.la $(MATIO_LIB) @LIBOBJS@

# additional include pathes necessary
AM_CPPFLAGS= -I$(top_srcdir)/src/libcandbc \
	   -I$(top_srcdir)/src/libcanmdf \
	   -I$(top_srcdir)/hashtable

DEFS = $(YYDEBUG)

# YACC: generate token defines for LEX
AM_YFLAGS = -d

## Uncomment to enable debugging of linker script parser
YYDEBUG = -DYYDEBUG=1

#
# library headers, source, etc.
#
include_HEADERS= src/libcandbc/dbcModel.h \
		 src/libcandbc/dbcTypes.h \
		 src/libcandbc/dbcReader.h \
		 src/libcandbc/dbcWriter.h \
		 src/libcanmdf/mdfcg.h \
		 src/libcanmdf/mdfdg.h \
		 src/libcanmdf/mdffile.h \
		 src/libcanmdf/mdffilter.h \
		 src/libcanasc/ascReader.h \
		 src/libcanasc/messageDecoder.h

libcandbc_la_SOURCES= \
	src/libcandbc/dbcModel.c \
	src/libcandbc/dbcReader.c \
	src/libcandbc/dbcWriter.c \
	src/libcandbc/parser.y \
	src/libcandbc/lexer.l

libcanasc_la_SOURCES= \
	src/libcanasc/ascReader.c \
	src/libcanasc/messageDecoder.c

libcanmdf_la_SOURCES= \
	src/libcanmdf/mdfcg.c \
	src/libcanmdf/mdfcn.c \
	src/libcanmdf/mdfdg.c \
	src/libcanmdf/mdffile.c \
	src/libcanmdf/mdffilter.c \
	src/libcanmdf/mdfmodel.c \
	src/libcanmdf/mdfsg.c

libcandbc_la_CPPFLAGS= -I$(top_builddir)/src/libcandbc
libcandbc_la_LDFLAGS= -no-undefined -version-info @version_info@

libcanasc_la_CPPFLAGS= -I$(top_builddir)/src/libcanasc \
		       -I$(top_srcdir)/src/libcandbc
libcanasc_la_LDFLAGS= -no-undefined -version-info @version_info@

libcanmdf_la_CPPFLAGS= -I$(top_builddir)/src/libcanmdf
libcanmdf_la_LDFLAGS= -no-undefined -version-info @version_info@

MAINTAINERCLEANFILES = \
	src/libcandbc/parser.c \
	src/libcandbc/parser.h \
	src/libcandbc/lexer.c

src/libcandbc/parser.h src/libcandbc/parser.c: src/libcandbc/parser.y
