#ifndef SFXA_LCPCALC_H
#define SFXA_LCPCALC_H 1
// ***************************************************************************
// $Id$
// vim:tabstop=8:shiftwidth=4:softtabstop=4
//
// Calculate LCP
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

#include <vector>

// ***************************************************************************
// See GetHeight() in T. Kasai, G. Lee, H. Arimura, S. Arikawa, and K. Park.
// Linear-time Longest-Common-Prefix Computation in Suffix Arrays and Its
// Applications. In Proc. the 12th Annual Symposium on Combinatorial Pattern
// Matching (CPM'01), LNCS 2089, 181-192, 2001.
// ***************************************************************************

namespace aki_at_gsc_riken_jp {

// ===========================================================================
// sfxa_lcpcalc class
// ===========================================================================

template <typename mftxt_t, typename mfidx_t>
class sfxa_lcpcalc
{
    public:
	typedef mftxt_t		mftxt_type;
	typedef mfidx_t		mfidx_type;

    private:
	typedef typename mftxt_t::elem_type char_t;
	typedef typename mfidx_t::elem_type index_t;

    public:
	sfxa_lcpcalc(mftxt_t & mftxt, mfidx_t & mfidx, mfidx_t & mflcp);

    private:
	// These are not supported and are not implemented!
	sfxa_lcpcalc(const sfxa_lcpcalc<mftxt_t, mfidx_t> & x);
	sfxa_lcpcalc<mftxt_t, mfidx_t> & operator=(const sfxa_lcpcalc<mftxt_t, mfidx_t> & x);
};

// ===========================================================================
// ctor
// ===========================================================================
template <typename mftxt_t, typename mfidx_t>
sfxa_lcpcalc<mftxt_t, mfidx_t>::sfxa_lcpcalc(mftxt_t & mftxt, mfidx_t & mfidx, mfidx_t & mflcp)
{
    try {
	index_t n(static_cast<index_t>(mfidx.get_num_elem()));
	std::vector<index_t> rank(n);

	for (index_t i = 0; i < n; ++i)
	    rank[mfidx[i]] = i;

	index_t h = 0;
	for (index_t i = 0; i < n; ++i) {
	    if (rank[i] > 1) {
		index_t j = mfidx[rank[i] - 1];
		while (mftxt[i + h] == mftxt[j + h])
		    ++h;
		mflcp[rank[i]] = h;
		if (h > 0)
		    --h;
	    }
	}
    }

    catch (...) {
	throw;
    }
}

} // namespace aki_at_gsc_riken_jp

// ***************************************************************************
#endif // SFXA_LCPCALC_H
