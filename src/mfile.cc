// ***************************************************************************
// $Id$
// vim:tabstop=8:shiftwidth=4:softtabstop=4
//
// Memory mapped file class implementation file
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

#include "mfile.h"
#include "mfile_e.h"

#ifndef CONFIG_H_INCLUDED
# define CONFIG_H_INCLUDED 1
# include "config.h"
#endif

#ifndef CSTDIO_INCLUDED
# define CSTDIO_INCLUDED 1
# include <cstdio>
#endif
#ifndef CSTRING_INCLUDED
# define CSTRING_INCLUDED 1
# include <cstring>
#endif
#ifndef CERRNO_INCLUDED
# define CERRNO_INCLUDED 1
# include <cerrno>
#endif
#if HAVE_UNISTD_H
# ifndef UNISTD_H_INCLUDED
#  define UNISTD_H_INCLUDED 1
#  include <unistd.h>
# endif
#endif
#if HAVE_SYS_MMAN_H
# ifndef SYS_MMAN_H_INCLUDED
#  define SYS_MMAN_H_INCLUDED 1
#  include <sys/mman.h>
# endif
#endif
#if HAVE_SYS_TYPES_H
# ifndef SYS_TYPES_H_INCLUDED
#  define SYS_TYPES_H_INCLUDED 1
#  include <sys/types.h>
# endif
#endif
#if HAVE_SYS_STAT_H
# ifndef SYS_STAT_H_INCLUDED
#  define SYS_STAT_H_INCLUDED 1
#  include <sys/stat.h>
# endif
#endif
#if HAVE_FCNTL_H
# ifndef FCNTL_H_INCLUDED
#  define FCNTL_H_INCLUDED 1
#  include <fcntl.h>
# endif
#endif

#ifndef COMMON_TYPE_H_INCLUDED
# define COMMON_TYPE_H_INCLUDED 1
# include "common_type.h"
#endif

#include <iostream>

namespace aki_at_gsc_riken_jp {

// ===========================================================================
// mfile_i class
// ===========================================================================

template <typename elem_t>
class mfile_i {
    public:
	char *	    _path;
	int	    _open_flags;
	mode_t	    _creat_mode;
	void *	    _start_addr;
	size_t	    _mmap_size;
	int	    _mmap_prot;
	int	    _mmap_flags;
	off_t	    _file_offset;
	int	    _msync_flags;

	int	    _fdesc;
	elem_t *    _ptr;
	off_t	    _file_size;
	bool	    _mmapped;
	void	    _init(const char * path);

	mfile_i(
	    const char * path,
	    int open_flags,
	    mode_t creat_mode,
	    size_t length,
	    int mmap_prot,
	    int mmap_flags,
	    off_t offset,
	    void * start_addr,
	    int msync_flags
	    );

	mfile_i(const char * path, size_t length);
	mfile_i(const char * path,
//		enum mfile<elem_t>::e_mode_type
		mode_type
		mode);

	~mfile_i();

    private:
	// These are not supported and are not implemented!
	mfile_i(const mfile_i<elem_t> & x);
	mfile_i<elem_t> & operator=(const mfile_i<elem_t> & x);
};

// ---------------------------------------------------------------------------
// mfile_i methods
// ---------------------------------------------------------------------------

// most general ctor
template <typename elem_t>
mfile_i<elem_t>::mfile_i(
	const char * path,
	int open_flags,
	mode_t creat_mode,
	size_t length,
	int mmap_prot = PROT_READ,
	int mmap_flags = MAP_SHARED,
	off_t offset = 0,
	void * start_addr = 0,
	int msync_flags = MS_SYNC
	)
    : _path(new char[strlen(path) + 1])
    , _open_flags(open_flags)
    , _mmap_size(length)
    , _mmap_prot(mmap_prot)
    , _mmap_flags(mmap_flags)
    , _msync_flags(msync_flags)
    , _creat_mode(creat_mode)
    , _file_offset(offset)
    , _start_addr(start_addr)
    , _fdesc(-1)
    , _ptr(0)
    , _file_size(0)
    , _mmapped(false)
{
    _init(path);
}

template <typename elem_t>
mfile_i<elem_t>::mfile_i(const char * path, size_t length)
    : _path(new char[strlen(path) + 1])
    , _open_flags(O_CREAT | O_TRUNC | O_RDWR)
    , _mmap_size(length)
    , _mmap_prot(PROT_READ | PROT_WRITE)
    , _mmap_flags(MAP_SHARED)
    , _msync_flags(MS_SYNC)
    , _creat_mode(00666)
    , _file_offset(0)
    , _start_addr(0)
    , _fdesc(-1)
    , _ptr(0)
    , _file_size(0)
    , _mmapped(false)
{
    _init(path);
}

template <typename elem_t>
//mfile_i<elem_t>::mfile_i(const char * path, enum mfile<elem_t>::e_mode_type mode)
mfile_i<elem_t>::mfile_i(const char * path, mode_type mode)
    : _path(new char[strlen(path) + 1])
    , _open_flags(O_RDONLY)
    , _mmap_size(0)
    , _mmap_prot(PROT_READ)
    , _mmap_flags(MAP_SHARED)
    , _msync_flags(MS_SYNC)
    , _creat_mode(00444)
    , _file_offset(0)
    , _start_addr(0)
    , _fdesc(-1)
    , _ptr(0)
    , _file_size(0)
    , _mmapped(false)
{
//    if (mode == mfile<elem_t>::private_readwrite) {
    if (mode == private_readwrite) {
	_mmap_prot |= PROT_WRITE;
	_mmap_flags = MAP_PRIVATE;
    }
#if 0
    _init(path);
#else
    try {
	_init(path);
    }
    catch (...) {
//std::cerr << "mfile.cc::mfile_i(path, mode): caught exception" << std::endl;
//	throw;
    }
#endif
}

template <typename elem_t>
void mfile_i<elem_t>::_init(const char * path)
{
//    try {
	std::strcpy(_path, path);

	if ((_fdesc = open(_path, _open_flags, _creat_mode)) == -1) {
//std::cerr << "mfile.cc::mfile_i::_init(): open() failed. throws mfile_exception" << std::endl;
	    throw mfile_exception(errno);
	}

	if (_mmap_size == 0) {
	    struct stat st;
	    if (fstat(_fdesc, &st) == -1)
		throw mfile_exception(errno);
	    _file_size = st.st_size;
#if SIZEOF_OFF_T == SIZEOF_SSIZE_T
	    _mmap_size = _file_size;
#else // not SIZEOF_OFF_T == SIZEOF_SSIZE_T
	    /* !!! */
	    _mmap_size = ((_file_size < SSIZE_MAX)
			? (size_t)_file_size : SSIZE_MAX);
#endif // not SIZEOF_OFF_T == SIZEOF_SSIZE_T
	}
	else if (_open_flags & O_TRUNC && _mmap_size > 0) {
	    if (lseek(_fdesc, (off_t)(_mmap_size - 1), SEEK_SET) == (off_t)(-1))
		throw mfile_exception(errno);
	    char c = '\0';
	    if (write(_fdesc, &c, sizeof(char)) == -1)
		throw mfile_exception(errno);
	}

#if HAVE_MMAP
	_ptr = (elem_t *)mmap(_start_addr, _mmap_size, _mmap_prot, _mmap_flags, _fdesc, _file_offset);
	if (_ptr != (void *)(-1)) {
	    /* successed mmap */
	    _mmapped = true;
	} else {
	    /* failed to mmap */
	    if (errno != ENODEV && errno != ENOEXEC)
		throw mfile_exception(errno);
#endif // HAVE_MMAP

	    if ((_ptr = (elem_t *)(new elem_t[_mmap_size])) == 0)
		throw mfile_exception(errno);

	    if (lseek(_fdesc, 0, SEEK_SET) == (off_t)(-1))
		throw mfile_exception(errno);

	    // read file contents into memory
#if SIZEOF_OFF_T == SIZEOF_SSIZE_T
	    {
		ssize_t rd;
		if ((rd = read(_fdesc, _ptr, _mmap_size)) < _mmap_size) {
		    if (rd == -1)
			throw mfile_exception(errno);
		    errno = EINTR;
		    throw mfile_exception(errno);
		}
	    }
#else // not SIZEOF_OFF_T == SIZEOF_SSIZE_T
	    if (_mmap_size <= SSIZE_MAX) {
		ssize_t rd;
		if ((rd = read(_fdesc, _ptr, _mmap_size)) < _mmap_size) { /* !!! */
		    if (rd == -1)
			throw mfile_exception(errno);
		    errno = EINTR;	/* !!! */
		    throw mfile_exception(errno);
		}
	    } else {
		errno = EFBIG;		/* !!! */
		throw mfile_exception(errno);
	    }
#endif // not SIZEOF_OFF_T == SIZEOF_SSIZE_T

#if HAVE_MMAP
	}
#endif // HAVE_MMAP

//    }

#if 0
    catch (mfile_exception & e) {
std::cerr << "mfile.cc::_init(): mfile_exception caught" << std::endl;
	throw;
    }
#endif
#if 0
    catch (...) {
std::cerr << "mfile.cc::_init(): exception caught" << std::endl;
	throw;
    }
#endif
}

//
template <typename elem_t>
mfile_i<elem_t>::~mfile_i()
{
    // write back to the file
    if (_mmap_prot & PROT_WRITE && _mmap_flags & MAP_SHARED) {
#if HAVE_MMAP
	if (_mmapped) {
	    if (msync(_ptr, _mmap_size, _msync_flags) == -1)
		throw mfile_exception(errno);
	} else {
#endif // HAVE_MMAP

//#if SIZEOF_OFF_T == SIZEOF_SSIZE_T
	    if (lseek(_fdesc, 0, SEEK_SET) == (off_t)-1)
		throw mfile_exception(errno);
	    ssize_t wr;
	    if ((wr = write(_fdesc, _ptr, _mmap_size)) < _mmap_size) { /* !!! */
		if (wr == -1)
		    throw mfile_exception(errno);
		errno = EINTR;  /* !!! */
		throw mfile_exception(errno);
	    }
//#else
//#endif

#if HAVE_MMAP
	}
#endif // HAVE_MMAP
    }

    // free the memory
#if HAVE_MMAP
    if (_mmapped) {
	if (munmap(_ptr, _mmap_size) == -1)
	    throw mfile_exception(errno);
    } else {
#endif // HAVE_MMAP
        delete [] _ptr;
#if HAVE_MMAP
    }
#endif // HAVE_MMAP

    if (close(_fdesc) == -1)
	throw mfile_exception(errno);

    delete [] _path;
}

// ===========================================================================
// mfile class
// ===========================================================================

// ---------------------------------------------------------------------------
// mfile methods
// ---------------------------------------------------------------------------

// dtor
template <typename elem_t>
mfile<elem_t>::~mfile() {}

// most general ctor
template <typename elem_t>
mfile<elem_t>::mfile(
	const char * path,
	int open_flags,
	mode_t creat_mode,
	size_t length,
	int mmap_prot = PROT_READ,
	int mmap_flags = MAP_SHARED,
	off_t offset = 0,
	void * start_addr = 0,
	int msync_flags = MS_SYNC
	)
: d_this(new mfile_i<elem_t>(path, open_flags, creat_mode, length, mmap_prot, mmap_flags, offset, start_addr, msync_flags))
{
}

// @: mandatory parameter, %:determined (by mandatory parameter), #: n/a

// ctor for create read write
// (@path, %O_CREAT|O_TRUNC|O_RDWR, %0666, #NULL, @length,
// %PROT_READ|PROT_WRITE, %MAP_SHARED, #0, %MS_SYNC)
template <typename elem_t>
mfile<elem_t>::mfile(const char * path, size_t length)
    : d_this(new mfile_i<elem_t>(path, length))
{
}

// ctor for shared readonly
// (@path, %O_RDONLY, #00444, #NULL, %0, %PROT_READ, %MAP_SHARED,
// #0, #MS_SYNC)
// 
// ctor for private read write
// (@path, %O_RDONLY, #00444, #NULL, %0, %PROT_READ|PROT_WRITE,
// %MAP_PRIVATE, #0, %MS_SYNC)

#if 0
template <typename elem_t>
mfile<elem_t>::mfile(const char * path, mode_type mode)
    : d_this(new mfile_i<elem_t>(path, mode))
{
}
#else
template <typename elem_t>
mfile<elem_t>::mfile(const char * path, mode_type mode)
{
    try {
	d_this = new mfile_i<elem_t>(path, mode);
    }
    catch (...) {
	throw;
    }
}
#endif

template <typename elem_t>
elem_t & mfile<elem_t>::operator[](const off_t index) const
{
    return d_this->_ptr[index];
}

template <typename elem_t>
off_t mfile<elem_t>::get_num_elem() const
{
    return (d_this->_mmap_size / sizeof(elem_t));
}

// ===========================================================================
// instances
// ===========================================================================

template class mfile_i<char>;
template class mfile<char>;

template class mfile_i<idx32_t>;
template class mfile<idx32_t>;

template class mfile_i<idx64_t>;
template class mfile<idx64_t>;

} // namespace aki_at_gsc_riken_jp

// ***************************************************************************
