# Make cantools.					-*-Makefile-*-

# Copyright (C) 2007-2017 Andreas Heitmann

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

SUBDIRS = . tests

AUTOMAKE_OPTIONS= foreign subdir-objects
ACLOCAL_AMFLAGS= -I m4

LEX=@LEX@
YACC=@YACC@

#	
# What to build and install
#
lib_LTLIBRARIES = libcandbc.la libcanasc.la libcanmdf.la libcanvsb.la \
	          libcanclg.la libcanblf.la

bin_PROGRAMS	= dbccopy dbcls cantomat mdftomat matdump

#
# dbcls
#
dbcls_SOURCES  = src/dbcls/dbcls.c
dbcls_CPPFLAGS = -I$(top_srcdir)/src/libcandbc
dbcls_LDADD    = libcandbc.la -lm

#
# dbccopy
#
dbccopy_SOURCES  = src/dbccopy/dbccopy.c
dbccopy_CPPFLAGS = -I$(top_srcdir)/src/libcandbc
dbccopy_LDADD	 = libcandbc.la -lm

#
# cantomat
#
cantomat_SOURCES = src/cantomat/cantomat.c \
		   src/cantomat/messagedecoder.c \
		   src/cantomat/busassignment.c \
		   src/cantomat/matwrite.c \
		   src/cantomat/messagehash.c \
		   src/cantomat/measurement.c \
		   src/cantomat/signalformat.c \
		   src/cantomat/measurement.h \
		   src/cantomat/signalformat.h \
		   src/cantomat/busassignment.h \
		   src/cantomat/matwrite.h \
		   src/cantomat/messagehash.h \
		   src/hashtable/hashtable.c \
		   src/hashtable/hashtable_itr.c \
		   src/hashtable/hashtable.h \
		   src/hashtable/hashtable_itr.h \
		   src/hashtable/hashtable_private.h
cantomat_CPPFLAGS = @MATIO_CFLAGS@ \
		   -I$(top_srcdir)/src/libcanasc \
	   	   -I$(top_srcdir)/src/libcanblf \
           -I$(top_srcdir)/src/libcanclg \
		   -I$(top_srcdir)/src/libcandbc \
		   -I$(top_srcdir)/src/libcanvsb \
           -I$(top_srcdir)/src/cantomat \
	  	   -I$(top_srcdir)/src/hashtable
cantomat_LDADD = libcandbc.la libcanasc.la libcanblf.la \
	         libcanvsb.la libcanclg.la
cantomat_LDADD += @MATIO_LIBS@ @ZLIB_LIBS@ $(HDF5_LIB) @LIBOBJS@ -lm

#
# mdftomat
#
mdftomat_SOURCES = src/mdftomat/mdftomat.c \
                   src/mdftomat/mdftomat.h
mdftomat_CPPFLAGS  = @MATIO_CFLAGS@ \
	   -I$(top_srcdir)/src/libcanmdf
mdftomat_LDADD	   = libcanmdf.la @MATIO_LIBS@ @ZLIB_LIBS@ $(HDF5_LIB) @LIBOBJS@

#
# matdump
#
matdump_SOURCES = src/matdump/matdump.c \
                  src/matdump/matdump.h
matdump_CPPFLAGS  = @MATIO_CFLAGS@
matdump_LDADD	= @MATIO_LIBS@ @ZLIB_LIBS@ $(HDF5_LIB) @LIBOBJS@

# additional include pathes necessary
AM_CPPFLAGS = 
DEFS = $(YYDEBUG) @DEFS@

# YACC: generate token defines for LEX
AM_YFLAGS = -d

## Uncomment to enable debugging of linker script parser
YYDEBUG = -DYYDEBUG=1

#
# library headers, source, etc.
#
include_HEADERS= src/libcandbc/dbcmodel.h \
		 src/libcandbc/dbctypes.h \
		 src/libcandbc/dbcreader.h \
		 src/libcandbc/dbcwriter.h \
		 src/libcanmdf/mdfcg.h \
		 src/libcanmdf/mdfdg.h \
		 src/libcanmdf/mdffile.h \
		 src/libcanmdf/mdffilter.h \
		 src/libcanasc/ascreader.h \
		 src/libcanblf/blfreader.h \
		 src/libcanblf/blfapi.h \
		 src/libcanblf/blfstream.h \
		 src/libcanblf/blfparser.h \
		 src/libcanvsb/vsbreader.h \
		 src/libcanclg/clgreader.h \
		 src/cantomat/messagedecoder.h \
		 src/libcanmdf/mdfcn.h \
		 src/libcanmdf/mdfswap.h \
		 src/libcanmdf/mdftypes.h

libcandbc_la_SOURCES= \
	src/libcandbc/dbcmodel.c \
	src/libcandbc/dbcreader.c \
	src/libcandbc/dbcwriter.c \
	src/libcandbc/parser.y \
	src/libcandbc/lexer.l

libcandbc_la_LIBADD= -lm

libcanasc_la_SOURCES= src/libcanasc/ascreader.c

libcanblf_la_SOURCES= src/libcanblf/blfreader.c \
		              src/libcanblf/blfparser.c \
				      src/libcanblf/blfstream.c \
		     		  src/libcanblf/blfapi.c

libcanvsb_la_SOURCES= src/libcanvsb/vsbreader.c

libcanclg_la_SOURCES= src/libcanclg/clgreader.c

libcanmdf_la_SOURCES= \
	src/libcanmdf/mdfcg.c \
	src/libcanmdf/mdfcn.c \
	src/libcanmdf/mdfdg.c \
	src/libcanmdf/mdffile.c \
	src/libcanmdf/mdffilter.c \
	src/libcanmdf/mdfmodel.c \
	src/libcanmdf/mdfsg.c
libcanmdf_CPPFLAGS = @MATIO_CFLAGS@

libcandbc_la_CPPFLAGS= -I$(top_builddir)/src/libcandbc \
                       -I$(top_srcdir)/src/libcandbc
libcandbc_la_LDFLAGS= -no-undefined -version-info @version_info@

libcanasc_la_CPPFLAGS= -I$(top_builddir)/src/libcanasc \
		      	       -I$(top_srcdir)/src/libcandbc \
		    		   -I$(top_srcdir)/src/cantomat \
                       -I$(top_srcdir)/src/hashtable
libcanasc_la_LDFLAGS= -no-undefined -version-info @version_info@

libcanblf_la_CPPFLAGS= -I$(top_builddir)/src/libcanblf \
				       -I$(top_srcdir)/src/libcandbc \
                       -I$(top_srcdir)/src/cantomat \
                       -I$(top_srcdir)/src/hashtable \
                       -Wunused -pedantic
libcanblf_la_LDFLAGS= -no-undefined -version-info @version_info@

libcanvsb_la_CPPFLAGS= -I$(top_builddir)/src/libcanvsb \
					   -I$(top_srcdir)/src/libcandbc \
				       -I$(top_srcdir)/src/cantomat \
                       -I$(top_srcdir)/src/hashtable
libcanvsb_la_LDFLAGS= -no-undefined -version-info @version_info@

libcanclg_la_CPPFLAGS= -I$(top_builddir)/src/libcanclg \
				       -I$(top_srcdir)/src/libcandbc \
	       		       -I$(top_srcdir)/src/cantomat \
                       -I$(top_srcdir)/src/hashtable
libcanclg_la_LDFLAGS= -no-undefined -version-info @version_info@

libcanmdf_la_CPPFLAGS= -I$(top_builddir)/src/libcanmdf @MATIO_CFLAGS@
libcanmdf_la_LDFLAGS= -no-undefined -version-info @version_info@

MAINTAINERCLEANFILES = \
	src/libcandbc/parser.c \
	src/libcandbc/parser.h \
	src/libcandbc/lexer.c

src/libcandbc/parser.h src/libcandbc/parser.c: src/libcandbc/parser.y

install-exec-hook:
	cd $(DESTDIR)$(bindir) && \
		$(LN_S) cantomat$(EXEEXT) asctomat$(EXEEXT)
	cd $(DESTDIR)$(bindir) && \
		$(LN_S) cantomat$(EXEEXT) blftomat$(EXEEXT)
	cd $(DESTDIR)$(bindir) && \
		$(LN_S) cantomat$(EXEEXT) vsbtomat$(EXEEXT)
	cd $(DESTDIR)$(bindir) && \
		$(LN_S) cantomat$(EXEEXT) clgtomat$(EXEEXT)
