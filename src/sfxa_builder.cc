// ***************************************************************************
// $Id$
// vim:tabstop=8:shiftwidth=4:softtabstop=4
//
// Suffix array builder class
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

#include "sfxa_builder.h"

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

#include <iostream>

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
#define NEW_SFXA(b) \
    { \
    size_t need = txt_size * sizeof(idx ## b ## _t); \
    mfile ## b ## _t * mf_idx = new mfile ## b ## _t(_idxfpath.c_str(), need); \
    mfile ## b ## _t * mf_lcp = ((get_calc_lcp()) \
	    ? new mfile ## b ## _t(_lcpfpath.c_str(), need) : NULL); \
    sa = new sfxa ## b ## _t(mf_txt, mf_idx, mf_lcp); \
    }
// ---------------------------------------------------------------------------

sfxa * sfxa_builder::build() {
    sfxa * sa;

    try {
	mfile8_t * mf_txt = new mfile8_t(_txtfpath.c_str(),
		((get_ignore_case())
#if 0
		? mfile8_t::private_readwrite
		: mfile8_t::shared_readonly
#else
		? private_readwrite
		: shared_readonly
#endif
		));

	off_t txt_size = mf_txt->get_num_elem();

	if (txt_size == 0) {
	    delete mf_txt;
	    return NULL;
	}

	// when ignore-case flag is on
	if (get_ignore_case()) {
	    for (off_t i = 0; i < txt_size; ++i)
		(*mf_txt)[i] = static_cast<mfile8_t::elem_type>
		    (toupper(toupper((*mf_txt)[i])));
	}

#if SIZEOF_VOIDP == 4
	if (txt_size < (IDX32_MAX / sizeof(idx32_t))) {	// max file size 2GB
	    NEW_SFXA(32);
	} else {
	}
#elif SIZEOF_VOIDP == 8
	if (txt_size < (IDX32_MAX / sizeof(idx32_t))) { // max index number 2GB
	    NEW_SFXA(32);
	} else {
	    NEW_SFXA(64);
	}
#endif // SIZEOF_VOIDP == 8

	sa->sort();

	if (get_calc_lcp()) {
	    sa->calc_lcp();
	}
    }

    catch (mfile_exception & e) {
std::cerr << "sfxa_builder.cc::mfile_exception caught!" << std::endl;
	throw;
    }
    catch (...) {
std::cerr << "sfxa_builder.cc::exception caught!" << std::endl;
	throw;
    }

    return sa;
}

// ---------------------------------------------------------------------------
#undef NEW_SFXA
// ---------------------------------------------------------------------------

// ***************************************************************************
