#ifndef SFXA_H
#define SFXA_H 1
// ***************************************************************************
// $Id$
// vim:tabstop=8:shiftwidth=4:softtabstop=4
//
// Suffix array class
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

namespace aki_at_gsc_riken_jp {

// ===========================================================================
// sfxa class
// ===========================================================================

class sfxa
{
    public:
	virtual ~sfxa() {}
	virtual void sort() = 0;
	virtual void calc_lcp() = 0;
	virtual void search(const char * pattern) = 0;
    private:
	// These are not supported and are not implemented!
//	sfxa(const sfxa & x);
	sfxa & operator=(const sfxa & x);
};

} // namespace aki_at_gsc_riken_jp

// ***************************************************************************
#endif // SFXA_H
