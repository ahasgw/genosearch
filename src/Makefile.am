## $Id$
## vim:tabstop=8:shiftwidth=8:softtabstop=8
##
## Makefile for the src directory of GenoSearch.
## Copyright (C) 2004 RIKEN. All rights reserved.
## Written by Aki Hasegawa <aki@gsc.riken.jp>.
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

## Process this file with automake to produce Makefile.in

MAINTAINERCLEANFILES = Makefile.in

AM_CPPFLAGS = -I$(top_srcdir)/src
AM_CXXFLAGS = -DNDEBUG

noinst_LIBRARIES = libsfxa.a
libsfxa_a_SOURCES = common_type.h \
	mfile.cc mfile.h mfile_e.h \
	sfxa_concrete.cc sfxa_concrete.h \
	sfxa_sorter.h \
	sfxa_lcpcalc.h \
	sfxa_searcher.cc sfxa_searcher.h \
	sfxa_builder.cc sfxa_builder.h \
	sfxa_opener.cc sfxa_opener.h \
	sfxa.h

bin_PROGRAMS = \
	fa2hdsq \
	fa2hdmz \
	creatidx \
	isearch

fa2hdsq_SOURCES = fa2hdsq.cc fa2hdsq.h
fa2hdsq_LDADD = libsfxa.a

fa2hdmz_SOURCES = fa2hdmz.cc fa2hdmz.h
fa2hdmz_LDADD = libsfxa.a

creatidx_SOURCES = creatidx.cc creatidx.h
creatidx_LDADD = libsfxa.a

isearch_SOURCES = isearch.cc isearch.h
isearch_LDADD = libsfxa.a
