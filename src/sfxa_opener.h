#ifndef SFXA_OPENER_H
#define SFXA_OPENER_H 1
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

#ifndef STRING_INCLUDED
# define STRING_INCLUDED 1
# include <string>
#endif

namespace aki_at_gsc_riken_jp {

class sfxa;

// ===========================================================================
// sfxa_opener class
// ===========================================================================

class sfxa_opener
{
    private:
	std::string	_txtfpath;
	std::string	_idxfpath;
	std::string	_lcpfpath;
	bool _ignore_case;
	bool _use_lcp;
    public:
	sfxa_opener(
		const char * txtf,
		const char * idxf,
		const char * lcpf = 0,
		bool use_lcp = false,
		bool ignore_case = false
		)
	    : _txtfpath(txtf), _idxfpath(idxf), _lcpfpath(lcpf),
		_use_lcp(false), _ignore_case(false) {}

	void set_ignore_case(bool onoff) { _ignore_case = onoff; }
	void set_use_lcp(bool onoff) { _use_lcp = onoff; }

	bool get_ignore_case() const { return _ignore_case; }
	bool get_use_lcp() const { return _use_lcp; }

	sfxa * open();

    private:
	// These are not supported and are not implemented!
	sfxa_opener(const sfxa_opener & x);
	sfxa_opener & operator=(const sfxa_opener & x);
};

} // namespace aki_at_gsc_riken_jp

// ***************************************************************************
#endif // SFXA_OPENER_H
