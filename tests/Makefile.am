## Process this file with automake to produce Makefile.in

TESTS = check_mdf_signal_convert
check_PROGRAMS = check_mdf_signal_convert
check_mdf_signal_convert_SOURCES = check_mdf_signal_convert.c \
	$(top_builddir)/src/libcanmdf/mdfsg.h \
	$(top_builddir)/src/libcanmdf/mdfmodel.h
check_mdf_signal_convert_CFLAGS = @CHECK_CFLAGS@ 
check_mdf_signal_convert_LDADD = $(top_builddir)/libcanmdf.la @CHECK_LIBS@

AM_CPPFLAGS = -I$(top_srcdir)/src/libcanmdf
