#ifndef MFILE_H
#define MFILE_H 1
// ***************************************************************************
// $Id$
// vim:tabstop=8:shiftwidth=4:softtabstop=4
//
// Memory mapped file class header file
// Copyright (C) 2004 RIKEN. All rights reserved.
// Written by Aki Hasegawa <aki@gsc.riken.jp>.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
// ***************************************************************************

#ifndef CONFIG_H_INCLUDED
# define CONFIG_H_INCLUDED 1
# include "config.h"
#endif

#if HAVE_SYS_TYPES_H
# ifndef SYS_TYPES_H_INCLUDED
#  define SYS_TYPES_H_INCLUDED 1
#  include <sys/types.h>
# endif
#endif

namespace aki_at_gsc_riken_jp {

typedef enum e_mode_type { shared_readonly, private_readwrite } mode_type;

// ===========================================================================
// mfile implementation class
// ===========================================================================

template <typename elem_t>
class mfile_i;

// ===========================================================================
// mfile class
// ===========================================================================

template <typename elem_t>
class mfile
{
	mfile_i<elem_t> *   d_this;

    public:
	typedef elem_t	elem_type;
//	typedef enum e_mode_type { shared_readonly, private_readwrite } mode_type;

	~mfile();
	
	// most general ctor
	mfile(
		const char * path,
		int open_flags,
		mode_t creat_mode,
		size_t length,
		int mmap_prot,
		int mmap_flags,
		off_t offset,
		void * start_addr,
		int msync_flags
	     );

	// @: mandatory parameter, %:determined (by mandatory parameter), #: n/a

	// ctor for create read write
	// (@path, %O_CREAT|O_TRUNC|O_RDWR, %0666, #NULL, @length,
	// %PROT_READ|PROT_WRITE, %MAP_SHARED, #0, %MS_SYNC)
	mfile(const char * path, size_t length);

	// ctor for shared readonly
	// (@path, %O_RDONLY, #00444, #NULL, %0, %PROT_READ, %MAP_SHARED,
	// #0, #MS_SYNC)
	// 
	// ctor for private read write
	// (@path, %O_RDONLY, #00444, #NULL, %0, %PROT_READ|PROT_WRITE,
	// %MAP_PRIVATE, #0, %MS_SYNC)
//	mfile(const char * path, enum e_mode_type mode);
	mfile(const char * path, mode_type mode);
	
	elem_t & operator[](const off_t index) const;

	off_t get_num_elem() const;

    private:
	// These are not supported and are not implemented!
	mfile(const mfile<elem_t> & x);
	mfile<elem_t> & operator=(const mfile<elem_t> & x);
};

#if 0
// ===========================================================================
// type definitions
// ===========================================================================

typedef mfile<char>     mfile8_t;
typedef mfile<idx32_t>  mfile32_t;
typedef mfile<idx64_t>  mfile64_t;
#endif

} // namespace aki_at_gsc_riken_jp

// ***************************************************************************
#endif // MFILE_H
