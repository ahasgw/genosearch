// ***************************************************************************
// $Id$
// vim:tabstop=8:shiftwidth=4:softtabstop=4
//
// Suffix array opener class
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

#include "sfxa_opener.h"

#ifndef COMMON_TYPE_H_INCLUDED
# define COMMON_TYPE_H_INCLUDED 1
# include "common_type.h"
#endif
#ifndef SFXA_CONCRETE_H_INCLUDED
# define SFXA_CONCRETE_H_INCLUDED 1
# include "sfxa_concrete.h"
#endif
#ifndef MFILE_H_INCLUDED
# define MFILE_H_INCLUDED 1
# include "mfile.h"
#endif
#ifndef MFILE_E_H_INCLUDED
# define MFILE_E_H_INCLUDED 1
# include "mfile_e.h"
#endif

using namespace aki_at_gsc_riken_jp;

// ===========================================================================
// type definitions
// ===========================================================================

typedef mfile<char>     mfile8_t;
typedef mfile<idx32_t>  mfile32_t;
typedef mfile<idx64_t>  mfile64_t;

// ===========================================================================
// public methods
// ===========================================================================

// ---------------------------------------------------------------------------
#define MFILE(b) \
    mfile ## b ## _t

#if 0
#define NEW_SFXA(b) \
    { \
    MFILE(b) * mf_idx \
	= new MFILE(b)(_idxfpath.c_str(), MFILE(b)::shared_readonly); \
    MFILE(b) * mf_lcp = ((get_use_lcp()) \
	? new MFILE(b)(_lcpfpath.c_str(), MFILE(b)::shared_readonly) : NULL); \
    sa = new sfxa ## b ## _t(mf_txt, mf_idx, mf_lcp); \
    }
#else
#define NEW_SFXA(b) \
    { \
    MFILE(b) * mf_idx \
	= new MFILE(b)(_idxfpath.c_str(), shared_readonly); \
    MFILE(b) * mf_lcp = ((get_use_lcp()) \
	? new MFILE(b)(_lcpfpath.c_str(), shared_readonly) : NULL); \
    sa = new sfxa ## b ## _t(mf_txt, mf_idx, mf_lcp); \
    }
#endif
// ---------------------------------------------------------------------------

sfxa * sfxa_opener::open() {
    try {
	mfile8_t * mf_txt
//	    = new mfile8_t(_txtfpath.c_str(), mfile8_t::shared_readonly);
	    = new mfile8_t(_txtfpath.c_str(), shared_readonly);
	off_t txt_size = mf_txt->get_num_elem();

	sfxa * sa;
#if SIZEOF_VOIDP == 4	    // ssize_t should be 32bits
	if (txt_size < (SSIZE_MAX / sizeof(idx32_t))) {	// max file size 2GB
	    NEW_SFXA(32);
	} else {
	}
#elif SIZEOF_VOIDP == 8	    // ssize_t should be 64bits
	if (txt_size < SSIZE_MAX) { // max index number 2GB
	    NEW_SFXA(32);
	} else {
	    NEW_SFXA(64);
	}
#endif // SIZEOF_VOIDP == 8
    }

    catch (mfile_exception & e) {
	perror(NULL);
    }

    return NULL;
}

// ---------------------------------------------------------------------------
#undef NEW_SFXA
#undef MFILE
// ---------------------------------------------------------------------------

// ***************************************************************************
