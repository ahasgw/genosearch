#ifndef MFILE_E_H
#define MFILE_E_H 1
// ***************************************************************************
// $Id$
// vim:tabstop=8:shiftwidth=4:softtabstop=4
//
// Memory mapped file exception class
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
// mfile_exception class
// ===========================================================================

class mfile_exception
{
    private:
	int d_errno;
    public:
	mfile_exception(int e) : d_errno(e) {}
	int get_errno() const { return d_errno; }
    private:
	// These are not supported and are not implemented!
//	mfile_exception(const mfile_exception & x);
	mfile_exception & operator=(const mfile_exception & x);
};

} // namespace aki_at_gsc_riken_jp

// ***************************************************************************
#endif // MFILE_E_H
