## $Id: Makefile.am,v 1.3 2004/04/02 10:43:37 aki Exp $
## vim:tabstop=8:shiftwidth=8
##
## Makefile for the toplevel directory of genosearch.
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

MAINTAINERCLEANFILES = Makefile.in aclocal.m4 configure \
	config.h.in config.h.in~ stamp-h.in $(AUX_DIST) \
	configure.scan autoscan.log

EXTRA_DIST = bootstrap BUGS THANKS TODO

SUBDIRS = src tests

.PHONY: maintainer-check

maintainer-check:
	cd tests && $(MAKE) $(AM_MAKEFLAGS) $@

AUX_DIST = $(ac_aux_dir)/install-sh $(ac_aux_dir)/missing \
	$(ac_aux_dir)/mkinstalldirs $(ac_aux_dir)/depcomp \
	$(ac_aux_dir)/config.guess $(ac_aux_dir)/config.sub \
	$(ac_aux_dir)/mdate-sh $(ac_aux_dir)/texinfo.tex

ACLOCAL = aclocal -I $(ac_aux_dir)
