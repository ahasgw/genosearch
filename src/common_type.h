#ifndef COMMON_TYPE_H
#define COMMON_TYPE_H 1
// ***************************************************************************
// $Id$
// vim:tabstop=8:shiftwidth=4:softtabstop=4
//
// Common header file for types
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

#ifndef CONFIG_H_INCLUDED
# define CONFIG_H_INCLUDED 1
# include "config.h"
#endif

namespace aki_at_gsc_riken_jp {

// ===========================================================================
// type definitions
// ===========================================================================

#if HAVE_STDINT_H && __STDC_LIMIT_MACROS

    typedef int32_t			idx32_t;
    typedef int64_t			idx64_t;
    typedef uint32_t			uidx32_t;
    typedef uint64_t			uidx64_t;

# define IDX32_MAX			INT32_MAX
# define IDX64_MAX			INT64_MAX
# define UIDX32_MAX			UINT32_MAX
# define UIDX64_MAX			UINT64_MAX

#else // not HAVE_STDINT_H

    typedef int				idx32_t;
    typedef unsigned int		uidx32_t;
# define IDX32_MAX			INT_MAX
# define UIDX32_MAX			UINT_MAX

# if SIZEOF_LONG == 8 // LP64

    typedef long			idx64_t;
    typedef unsigned long		uidx64_t;
#  define IDX64_MAX			LONG_MAX
#  define UIDX64_MAX			ULONG_MAX

# elif SIZEOF_LONG_LONG == 8 // LLP64

    typedef long long			idx64_t;
    typedef unsigned long long		uidx64_t;
#  define IDX64_MAX			LLONG_MAX
#  define UIDX64_MAX			ULLONG_MAX

# endif

#endif // not HAVE_STDINT_H

} // namespace ah

// ***************************************************************************
#endif // COMMON_TYPE_H
