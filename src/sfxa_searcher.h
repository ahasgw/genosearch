#ifndef SFXA_SEARCHER_H
#define SFXA_SEARCHER_H 1
// ***************************************************************************
// $Id$
// vim:tabstop=8:shiftwidth=4:softtabstop=4
//
// Suffix array searcher class
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

namespace aki_at_gsc_riken_jp {

// ===========================================================================
// sfxa_searcher class
// ===========================================================================

template <typename mftxt_t, typename mfidx_t>
class sfxa_searcher
{
    private:
	mftxt_t &	_txt;
	mfidx_t &	_idx;
	mfidx_t &	_lcp;
	bool _ignore_case;
	bool _use_lcp;
    public:
	sfxa_searcher(
		mftxt_t & txtf,
		mfidx_t & idxf,
		mfidx_t & lcpf = 0,
		bool use_lcp = false,
		bool ignore_case = false
		)
	    : _txt(txtf), _idx(idxf), _lcp(lcpf),
		_use_lcp(false), _ignore_case(false) {}

	void set_ignore_case(bool onoff) { _ignore_case = onoff; }
	void set_use_lcp(bool onoff) { _use_lcp = onoff; }

	bool get_ignore_case() const { return _ignore_case; }
	bool get_use_lcp() const { return _use_lcp; }

	int search(const char * pattern);

    private:
	// These are not supported and are not implemented!
	sfxa_searcher(const sfxa_searcher<mftxt_t, mfidx_t> & x);
	sfxa_searcher<mftxt_t, mfidx_t> & operator=(const sfxa_searcher<mftxt_t, mfidx_t> & x);
};

// ===========================================================================
// methods
// ===========================================================================

#if 0
template <typename mftxt_t, typename mfidx_t>
int sfxa_searcher<mftxt_t, mfidx_t>::search(const char * pattern)
{
    string pat(pattern);
    string::size_type patlen = pat.length();

    return 0;
}
#endif

} // namespace aki_at_gsc_riken_jp

// ***************************************************************************
#endif // SFXA_SEARCHER_H
