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

#include "sfxa_concrete.h"

#ifndef COMMON_TYPE_H_INCLUDED
# define COMMON_TYPE_H_INCLUDED 1
# include "common_type.h"
#endif

#ifndef MFILE_H_INCLUDED
# define MFILE_H_INCLUDED 1
# include "mfile.h"
#endif
#ifndef SFXA_SORTER_H_INCLUDED
# define SFXA_SORTER_H_INCLUDED 1
# include "sfxa_sorter.h"
#endif
#ifndef SFXA_LCPCALC_H_INCLUDED
# define SFXA_LCPCALC_H_INCLUDED 1
# include "sfxa_lcpcalc.h"
#endif
#ifndef SFXA_SEARCHER_H_INCLUDED
# define SFXA_SEARCHER_H_INCLUDED 1
# include "sfxa_searcher.h"
#endif

#ifndef MEMORY_INCLUDED
# define MEMORY_INCLUDED 1
# include <memory>
#endif

namespace aki_at_gsc_riken_jp {

// ===========================================================================
// sfxa method
// ===========================================================================

template <typename char_t, typename idx_t>
sfxa_concrete<char_t, idx_t>::sfxa_concrete(
	txtf_t * tp,
	idxf_t * ip,
	idxf_t * lp)
    : _mftxt(tp)
    , _mfidx(ip)
    , _mflcp(lp)
{
}

template <typename char_t, typename idx_t>
sfxa_concrete<char_t, idx_t>::~sfxa_concrete()
{
    delete _mflcp;
    delete _mfidx;
    delete _mftxt;
}

template <typename char_t, typename idx_t>
void sfxa_concrete<char_t, idx_t>::sort()
{
    try {
	std::auto_ptr<sfxa_sorter<txtf_t, idxf_t> >
	    sorter(new sfxa_sorter<txtf_t, idxf_t>(*_mftxt, *_mfidx));
    }
    catch (...) {
    }
//    sfxa_sorter<txtf_t, idxf_t>   sorter(*_mftxt, *_mfidx);
}

template <typename char_t, typename idx_t>
void sfxa_concrete<char_t, idx_t>::calc_lcp()
{
    try {
	std::auto_ptr<sfxa_lcpcalc<txtf_t, idxf_t> >
	    calculator(new sfxa_lcpcalc<txtf_t, idxf_t>(*_mftxt, *_mfidx, *_mflcp));
    }
    catch (...) {
    }
//    sfxa_lcpcalc<txtf_t, idxf_t>	lcpcalc(*_mftxt, *_mfidx, *_mflcp);
}

template <typename char_t, typename idx_t>
void sfxa_concrete<char_t, idx_t>::search(const char * pattern)
{
    try {
	std::auto_ptr<sfxa_searcher<txtf_t, idxf_t> >
	    s(new sfxa_searcher<txtf_t, idxf_t>(*_mftxt, *_mfidx, *_mflcp));
	s->search(pattern);
    }
    catch (...) {
    }
//    sfxa_searcher<txtf_t, idxf_t>	searcher(*_mftxt, *_mfidx, *_mflcp);
//    searcher.search(pattern);
}

// ===========================================================================
// instances
// ===========================================================================

template class sfxa_concrete<char, idx32_t>;
template class sfxa_concrete<char, idx64_t>;

} // namespace aki_at_gsc_riken_jp

// ***************************************************************************
