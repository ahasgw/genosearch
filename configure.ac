# $Id: configure.ac,v 1.14 2004/07/21 14:51:35 aki Exp $
# vi: set tabstop=8 shiftwidth=8 noexpandtab:
#
# Makefile for the toplevel directory of GenoSearch.
# Copyright (C) 2004 RIKEN. All rights reserved.
# Written by Aki Hasegawa <aki@gsc.riken.jp>.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(GenoSearch, [0.0.1], aki@gsc.riken.jp, genosearch)
AC_AIX
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_TESTDIR(tests)
AC_CONFIG_SRCDIR(src/mfile.cc)
AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE
AM_CONFIG_HEADER(config.h)
AC_SUBST(ac_aux_dir)
AC_GNU_SOURCE

# Checks for C++ language.
AC_LANG_PUSH(C++)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CXXCPP
AC_PROG_RANLIB
AM_MISSING_PROG(AUTOM4TE, autom4te)

# Checks for system services.
#AC_SYS_LARGEFILE	# We do not want this test.

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS(assert.h)
AC_CHECK_HEADERS(ctype.h)
AC_CHECK_HEADERS(errno.h)
AC_CHECK_HEADERS(fcntl.h)
AC_CHECK_HEADERS(limits.h)
AC_CHECK_HEADERS(math.h)
AC_CHECK_HEADERS(stdarg.h)
AC_CHECK_HEADERS(stddef.h)

AC_CHECK_HEADERS(getopt.h)
AC_CHECK_HEADERS(libgen.h)
AC_CHECK_HEADERS(sys/mman.h)
AC_CHECK_HEADERS(sys/file.h)

AC_CHECK_HEADERS(memory)

AC_CHECK_HEADERS(cerrno)
AC_CHECK_HEADERS(cstdio)

# Checks for typedefs, structures, and compiler characteristics.
AC_C_BIGENDIAN
AC_C_CHAR_UNSIGNED
AC_C_CONST
AC_C_INLINE
AC_CHECK_SIZEOF(int)
AC_CHECK_SIZEOF(long)
AC_CHECK_SIZEOF(void*)
AC_CHECK_SIZEOF(off_t)
AC_CHECK_SIZEOF(_int32)
AC_CHECK_SIZEOF(ssize_t)
AC_CHECK_SIZEOF([long long])
AC_CHECK_SIZEOF([long double])

# Checks for library functions.
#AC_FUNC_MMAP	# AC_FUNC_MMAP test is too severe. We use AC_CHECK_FUNCS.
#AC_FUNC_MALLOC
#AC_FUNC_REALLOC
#AC_FUNC_VPRINTF
#AC_CHECK_FUNCS(ftruncate)
AC_CHECK_FUNCS(getopt_long)
AC_CHECK_FUNCS([getpagesize mmap madvise msync munmap])

# End of checks for C++ language
AC_LANG_POP(C++)

# Outputs.
AC_CONFIG_FILES(Makefile)
AC_CONFIG_FILES(src/Makefile)
AC_CONFIG_FILES(tests/Makefile)
AC_CONFIG_FILES(tests/fa2hdsq, [chmod +x tests/fa2hdsq])
AC_CONFIG_FILES(tests/creatidx, [chmod +x tests/creatidx])
AC_CONFIG_FILES(tests/isearch, [chmod +x tests/isearch])

AC_OUTPUT
