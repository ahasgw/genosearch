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

#include "sfxa_searcher.h"

#ifndef COMMON_TYPE_H_INCLUDED
# define COMMON_TYPE_H_INCLUDED 1
# include "common_type.h"
#endif
#ifndef SFXA_H_INCLUDED
# define SFXA_H_INCLUDED 1
# include "sfxa.h"
#endif
#ifndef MFILE_H_INCLUDED
# define MFILE_H_INCLUDED 1
# include "mfile.h"
#endif
#ifndef MFILE_E_H_INCLUDED
# define MFILE_E_H_INCLUDED 1
# include "mfile_e.h"
#endif
#ifndef STRING_INCLUDED
# define STRING_INCLUDED 1
# include <string>
#endif

using namespace std;
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

template <typename mftxt_t, typename mfidx_t>
int sfxa_searcher<mftxt_t, mfidx_t>::search(const char * pattern)
{
    string pat(pattern);
    string::size_type patlen = pat.length();

    return 0;
}

// ===========================================================================
// instances
// ===========================================================================

template class sfxa_searcher<mfile8_t, mfile32_t>;
template class sfxa_searcher<mfile8_t, mfile64_t>;

// ***************************************************************************
