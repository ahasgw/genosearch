#ifndef SFXA_CONCRETE_H
#define SFXA_CONCRETE_H 1
// ***************************************************************************
// $Id$
// vim:tabstop=8:shiftwidth=4:softtabstop=4
//
// Suffix array concrete class
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

#ifndef COMMON_TYPE_H_INCLUDED
# define COMMON_TYPE_H_INCLUDED 1
# include "common_type.h"
#endif
#ifndef SFXA_H_INCLUDED
# define SFXA_H_INCLUDED 1
# include "sfxa.h"
#endif

namespace aki_at_gsc_riken_jp {

template <typename elem_t>
class mfile;

/*
template <typename mftxt_t, typename mfidx_t>
class sfxa_sorter;

template <typename mftxt_t, typename mfidx_t>
class sfxa_lcpcalc;

template <typename mftxt_t, typename mfidx_t>
class sfxa_searcher;
*/

// ===========================================================================
// sfxa concrete class
// ===========================================================================

template <typename char_t, typename idx_t>
class sfxa_concrete : public sfxa
{
    public:
	typedef char_t	char_type;
	typedef idx_t	idx_type;
	typedef mfile<char_t> txtf_t;
	typedef mfile<idx_t>  idxf_t;

    private:
	txtf_t *	_mftxt;
	idxf_t *	_mfidx;
	idxf_t *	_mflcp;

    public:
	sfxa_concrete(txtf_t * tp, idxf_t * ip, idxf_t * lp);
	~sfxa_concrete();

	virtual void sort();
	virtual void calc_lcp();
	virtual void search(const char * pattern);

    private:
	// These are not supported and are not implemented!
//	sfxa_concrete(const sfxa_concrete & x);
	sfxa_concrete & operator=(const sfxa_concrete & x);
};

// ===========================================================================
// type definitions
// ===========================================================================

typedef sfxa_concrete<char, idx32_t>	sfxa32_t;
typedef sfxa_concrete<char, idx64_t>	sfxa64_t;

} // namespace aki_at_gsc_riken_jp

// ***************************************************************************
#endif // SFXA_CONCRETE_H
