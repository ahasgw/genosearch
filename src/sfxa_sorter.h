#ifndef SFXA_SORTER_H
#define SFXA_SORTER_H 1
// ***************************************************************************
// $Id$
// vim:tabstop=8:shiftwidth=4:softtabstop=4
//
// Suffix array soter: Larsson and Sadakane method
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

#include <limits>
#include <vector>

// *********************************************************************
// The program codes in this file are based on qsufsort.c included as
// appendix B of N. Jesper Larsson's thesis, and his technical report.
// <http://www.cs.lth.se/Research/Algorithms/Source/qsufsort.c>
// <http://www.larsson.dogma.net/qsufsort.c>
// <http://www.larsson.dogma.net/thesis.pdf>
// <http://www.larsson.dogma.net/ssrev-tr.pdf>
// *********************************************************************

namespace aki_at_gsc_riken_jp {

// ===========================================================================
// sfxa_sorter class
// ===========================================================================

template <typename mftxt_t, typename mfidx_t>
class sfxa_sorter
{
    public:
	typedef mftxt_t		    mftxt_type;
	typedef mfidx_t		    mfidx_type;

    private:
	typedef typename mftxt_t::elem_type char_t;
	// index_t must be a signed type
	typedef typename mfidx_t::elem_type index_t;

	mftxt_t &	_txt;
	mfidx_t &	_idx;

	std::vector<index_t>	_inv;
	index_t		_h;
	index_t		_r;

    public:
	sfxa_sorter(mftxt_t & mftxt, mfidx_t & mfidx);

    private:
	// These are not supported and are not implemented!
	sfxa_sorter(const sfxa_sorter<mftxt_t, mfidx_t> & x);
	sfxa_sorter<mftxt_t, mfidx_t> & operator=(const sfxa_sorter<mftxt_t, mfidx_t> & x);

	void	_sort_split(index_t idx_pos, index_t num);
	void	_select_sort_split(index_t idx_pos, index_t num);
	index_t	_choose_pivot(index_t idx_pos, index_t num);
	void	_update_group(index_t pl, index_t pm);
	void	_bucketsort(index_t n, index_t k);
	index_t	_transform(index_t n, index_t k, index_t l, index_t q);

	index_t	_key(const index_t p) const
	{
	    return _inv[_idx[p] + _h];
	}

	void	_swap(const index_t p, const index_t q)
	{
	    index_t tmp = _idx[p]; _idx[p] = _idx[q]; _idx[q] = tmp;
	}

	index_t	_med3(const index_t a, const index_t b, const index_t c) const
	{
	    return ((_key(a) < _key(b))
		    ? (_key(b) < _key(c) ? b : _key(a) < _key(c) ? c : a)
		    : (_key(b) > _key(c) ? b : _key(a) > _key(c) ? c : a));
	}
};



/*======================================================================
 * macros
 *======================================================================*/

/* COMPACT
 * 
 * 0 to use alphabet 0...UCHAR_MAX without checking what appears. 1 to limit
 * the alphabet to the range l...k-1 that actually appears in the input. 2 to
 * transform the alphabet into 1...k-1 with no gaps and minimum k, preserving
 * the order.
 */
#define COMPACT		2   /* [0/1/2] */

// ===========================================================================
// ctor
// ===========================================================================
/*
 * Makes suffix array p of x. x becomes inverse of p. p and x are both of size
 * n+1. Contents of x[0...n-1] are integers in the range l...k-1. Original
 * contents of x[n] is disregarded, the n-th symbol being regarded as
 * end-of-string smaller than all other symbols.
 */
template <typename mftxt_t, typename mfidx_t>
sfxa_sorter<mftxt_t, mfidx_t>::sfxa_sorter(mftxt_t & mftxt, mfidx_t & mfidx)
    : _txt(mftxt), _idx(mfidx)
{
//std::clog << "sfxa_sorter()\n";
    try {
	index_t   n(static_cast<index_t>(_txt.get_num_elem()));
	--n;
	_inv.resize(n + 1);

#if (COMPACT == 2)
	// fill _inv[] with _txt[]
	index_t l = 1;
	index_t k = 0;
	{
	    index_t q[UCHAR_MAX + 1];
	    for (index_t i = 0; i < UCHAR_MAX + 1; ++i)
		q[i] = 0;
	    for (index_t i = 0; i < n; ++i) {
		_inv[i] = static_cast<index_t>(_txt[i]);
		q[_inv[i]] = 1;
	    }
	    for (index_t i = 0; i < UCHAR_MAX + 1; ++i)
		if (q[i])
		    q[i] = k++;
	    ++k;
	    for (index_t i = 0; i < n; ++i) {
//		_inv[i] = q[_inv[i]] + 1;
		_inv[i] = q[_inv[i]];
	    }
	}
#elif (COMPACT == 1)
	index_t l = UCHAR_MAX;
	index_t k = 0;
	{
	    for (index_t i = 0; i < n; ++i) {
		_inv[i] = static_cast<index_t>(_txt[i]);
		l = ((_txt[i] < l) ? _txt[i] : l);
		k = ((_txt[i] > k) ? _txt[i] : k);
	    }
	    ++k;
	}
#else // (COMPACT == 0)
	// fill _inv[] with _txt[]
	index_t l = 0;
	index_t k = UCHAR_MAX + 1;
	for (index_t i = 0; i < n; ++i)
	    _inv[i] = static_cast<index_t>(_txt[i]);
#endif // (COMPACT == 0)
//std::clog << "suffixsort(" << n << "," << k << "," << l << ")\n";

	if (n >= k - l) {
	    // if bucketing possible,
	    index_t j = _transform(n, k, l, n);
	    _bucketsort(n, j);
	} else {
	    _transform(n, k, l, std::numeric_limits<index_t>::max());
	    for (index_t i = 0; i <= n; ++i)
		_idx[i] = i;
	    _h = 0;
	    _sort_split(0, n + 1);
	}
	_h = _r;

	while (_idx[0] >= -n) {
	    index_t idx_pos = 0;    // idx_pos is first position of group.
	    index_t neg_skp = 0;    // neg_skp is negated length of sorted groups.
	    do {
		index_t ns = _idx[idx_pos];
		if (ns < 0) {
		    idx_pos -= ns;  // skip over sorted group.
		    neg_skp += ns;  // add negated length to neg_skp.
		} else {
		    if (neg_skp) {
			// combine sorted groups before idx_pos.
			_idx[idx_pos + neg_skp] = neg_skp;
			neg_skp = 0;
		    }
		    index_t pos = _inv[ns] + 1;
		    // pos-1 is last position of unsorted group.
		    _sort_split(idx_pos, pos - idx_pos);
		    idx_pos = pos;  // next group.
		}
	    } while (idx_pos <= n);

	    if (neg_skp) {
		// if the array ends with a sorted group.
		// combine sorted groups at end of _idx.
		_idx[idx_pos + neg_skp] = neg_skp;
	    }

	    // double sorted-depth.
	    _h *= 2;
	}

	for (index_t i = 0; i <= n; ++i) {
	    // reconstruct suffix array from inverse.
	    _idx[_inv[i]] = i;
	}
    }

    catch (...) {
	throw;
    }
}

/*
 * Sorting routine called for each unsorted group. Sorts the array of integers
 * (suffix numbers) of length n starting at p. The algorithm is a ternary-split
 * quicksort taken from Bentley & McIlroy, "Engineering a Sort Function",
 * Software -- Practice and Experience 23(11), 1249-1265 (November 1993). This
 * function is based on Program 7.
 */
template <typename mftxt_t, typename mfidx_t>
void sfxa_sorter<mftxt_t, mfidx_t>::_sort_split(index_t idx_pos, index_t num)
{
//std::clog << "_sort_split(" << idx_pos << ", " << num << ")\n";
    index_t pa, pb, pc, pd, pl, pm, pn;
    index_t f, s, t;

    if (num < 7) {	// multi-selection sort smallest arrays.
	_select_sort_split(idx_pos, num);
	return;
    }
    index_t v = _choose_pivot(idx_pos, num);
    pa = pb = idx_pos;
    pc = pd = idx_pos + num - 1;
    while (1) {		// split-end partition.
	while (pb <= pc && (f = _key(pb)) <= v)
	{ if (f == v) { _swap(pa, pb); ++pa; } ++pb; }
	while (pc >= pb && (f = _key(pc)) >= v)
	{ if (f == v) { _swap(pc, pd); --pd; } --pc; }
	if (pb > pc) break;
	_swap(pb, pc); ++pb; --pc;
    }
    pn = idx_pos + num;
    if ((s = pa - idx_pos) > (t = pb - pa)) s = t;
    for (pl = idx_pos, pm = pb - s; s; --s, ++pl, ++pm) _swap(pl, pm);
    if ((s = pd - pc) > (t = pn - pd - 1)) s = t;
    for (pl = pb, pm = pn - s; s; --s, ++pl, ++pm) _swap(pl, pm);
    s = pb - pa;
    t = pd - pc;
    if (s > 0) _sort_split(idx_pos, s);
    _update_group(idx_pos + s, idx_pos + num - t - 1);
//    _update_group(s, num - t - 1);
    if (t > 0) _sort_split(idx_pos + num - t, t);
}

/*
 * Quadratic sorting method to use for small subarrays. To be able to update
 * group numbers consistently, a variant of selection sorting is used.
 */
template <typename mftxt_t, typename mfidx_t>
void sfxa_sorter<mftxt_t, mfidx_t>::_select_sort_split(index_t idx_pos, index_t num)
{
//std::clog << "_select_sort_split(" << idx_pos << ", " << num << ")\n";
    index_t pa, pb, pi, pn;
    index_t f, v;
    pa = idx_pos;		/* pa is start of group being picked out.*/
    pn = idx_pos + num - 1;	/* pn is last position of subarray.*/
    while (pa < pn) {
	for (pi = pb = pa + 1, f = _key(pa); pi <= pn; ++pi) {
	    if ((v = _key(pi)) < f) {
		f = v;		/* f is smallest key found.*/
		_swap(pi, pa);	/* place smallest element at beginning.*/
		pb = pa + 1;	/* place smallest element at beginning.*/
	    } else if (v == f) {/* if equal to smallest key.*/
		_swap(pi, pb);	/* place next to other smallest elements.*/
		++pb;
	    }
	}
	_update_group(pa, pb - 1);
	// update group values for new group.
	pa = pb;
    }
    if (pa == pn) {		/* check if last part is single element.*/
	_inv[_idx[pa]] = pa;
	_idx[pa] = -1;		/* sorted group.*/
    }
}

/*
 * Subroutine for sort_split, algorithm by Bentley & McIlroy.
 */
template <typename mftxt_t, typename mfidx_t>
typename mfidx_t::elem_type
sfxa_sorter<mftxt_t, mfidx_t>::_choose_pivot(index_t idx_pos, index_t num)
{
//std::clog << "_choose_pivot(" << idx_pos << ", " << num << ")\n";
    index_t pm = idx_pos + (num >> 1);  // small arrays, middle element.
    if (num > 7) {
	index_t pl = idx_pos;
	index_t pn = idx_pos + num - 1;
	if (num > 40) {			// big arrays, pseudomedian of 9.
	    index_t s = num >> 3;
	    pl = _med3(pl, pl + s, pl + s + s);
	    pm = _med3(pm - s, pm, pm + s);
	    pn = _med3(pn - s - s, pn - s, pn);
	}
	pm = _med3(pl, pm, pn);	/* midsize arrays, median of 3.*/
    }
    return _key(pm);
}

/*
 * Subroutine for select_sort_split and sort_split. Sets group numbers for a
 * group whose lowest position in I is pl and highest position is pm.
 */
template <typename mftxt_t, typename mfidx_t>
void sfxa_sorter<mftxt_t, mfidx_t>::_update_group(index_t pl, index_t pm)
{
//std::clog << "_update_group(" << pl << ", " << pm << ")\n";
    index_t g = pm;		    // group number.
    _inv[_idx[pl]] = g;		    // update group number of first position.
    if (pl == pm) {
	_idx[pl] = -1;		    // one element, sorted group.
    } else {
	do {			    // more than one element, unsorted group.
	    _inv[_idx[++pl]] = g;   // update group numbers.
	} while (pl < pm);
    }
}

/*
 * Bucketsort for first iteration.
 * 
 * Input: x[0...n-1] holds integers in the range 1...k-1, all of which appear
 * at least once. x[n] is 0. (This is the corresponding output of transform.) k
 * must be at most n+1. p is array of size n+1 whose contents are disregarded.
 * 
 * Output: x is V and p is I after the initial sorting stage of the refined
 * suffix sorting algorithm.
 */
template <typename mftxt_t, typename mfidx_t>
void sfxa_sorter<mftxt_t, mfidx_t>::_bucketsort(index_t n, index_t k)
{
//std::clog << "_bucketsort(" << n << ", " << k << ")\n";
    // mark linked lists empty.
    for (index_t pi = 0; pi < k; ++pi) {
	_idx[pi] = -1;
    }

    // insert in linked list.
    for (index_t i = 0; i <= n; ++i) {
	index_t c = _inv[i];
	_inv[i] = _idx[c];
	_idx[c] = i;
    }

    for (index_t pi = k - 1, i = n; pi >= 0; --pi) {
	index_t c = _idx[pi];
	index_t d = _inv[c];	    // c is position, d is next in list.
	index_t g = i;
	_inv[c] = g;		    // last position equals group number.
	if (d >= 0) {		    // if more than one element in group.
	    _idx[i--] = c;	    // p is permutation for the sorted x.
	    do {
		d = _inv[c = d];    // next in linked list.
		_inv[c] = g;	    // group number in x.
		_idx[i--] = c;	    // permutation in p.
	    } while (d >= 0);
	} else {
	    _idx[i--] = -1;	    // one element, sorted group.
	}
    }
}

/*
 * Transforms the alphabet of x by attempting to aggregate several symbols into
 * one, while preserving the suffix order of x. The alphabet may also be
 * compacted, so that x on output comprises all integers of the new alphabet
 * with no skipped numbers.
 * 
 * Input: x is an array of size n+1 whose first n elements are positive
 * integers in the range l...k-1. p is array of size n+1, used for temporary
 * storage. q controls aggregation and compaction by defining the maximum value
 * for any symbol during transformation: q must be at least k-l; if q<=n,
 * compaction is guaranteed; if k-l>n, compaction is never done; if q is
 * INT_MAX, the maximum number of symbols are aggregated into one.
 * 
 * Output: Returns an integer j in the range 1...q representing the size of the
 * new alphabet. If j<=n+1, the alphabet is compacted. The global variable r is
 * set to the number of old symbols grouped into one. Only x[n] is 0.
 */
template <typename mftxt_t, typename mfidx_t>
typename mfidx_t::elem_type
sfxa_sorter<mftxt_t, mfidx_t>::_transform(
	index_t n, index_t k, index_t l, index_t q
	)
{
//std::clog << "_transform(" << n << "," << k << "," << l << "," << q << ")\n";
    index_t b, c, d, i, j, m, s;
    index_t pi, pj;

    for (s = 0, i = k - l; i; i >>= 1)
	++s;			/* s is number of bits in old symbol.*/

				// e is for overflow checking.
    index_t e = std::numeric_limits<index_t>::max() >> s;
    b = d = _r = 0;
    for (; _r < n && d <= e && (c = d << s | (k - l)) <= q; ++(_r)) {
	b = b << s | (_inv[_r] - l + 1);
				/* b is start of x in chunk alphabet.*/
	d = c;			/* d is max symbol in chunk alphabet.*/
    }

    m = (1 << (_r - 1) * s) - 1;
			        /* m masks off top old symbol from chunk.*/
    _inv[n] = l - 1;		/* emulate zero terminator.*/
    if (d <= n) {		/* if bucketing possible, compact alphabet.*/
	for (pi = 0; pi <= d; ++pi) {
	    _idx[pi] = 0;	// zero transformation table.
	}
	for (pi = _r, c = b; pi <= n; ++pi) {
	    _idx[c] = 1;		/* mark used chunk symbol.*/
	    c = (c & m) << s | (_inv[pi] - l + 1);
				/* shift in next old symbol in chunk.*/
	}
	for (i = 1; i < _r; ++i) {
				/* handle last r-1 positions.*/
	    _idx[c] = 1;		/* mark used chunk symbol.*/
	    c = (c & m) << s;	/* shift in next old symbol in chunk.*/
	}
	for (pi = 0, j = 1; pi <= d; ++pi)
	    if (_idx[pi])
		_idx[pi] = j++;	/* j is new alphabet size.*/
	for (pi = 0, pj = _r, c = b; pj <= n; ++pi, ++pj) {
	    _inv[pi] = _idx[c];		/* transform to new alphabet.*/
	    c = (c & m) << s | (_inv[pj] - l + 1);
				/* shift in next old symbol in chunk.*/
	}
	while (pi < n) {	/* handle last r-1 positions.*/
	    _inv[pi++] = _idx[c];	/* transform to new alphabet.*/
	    c = (c & m) << s;	/* shift right-end zero in chunk.*/
	}
    } else {			/* bucketing not possible, don't compact.*/
	for (pi = 0, pj = _r, c = b; pj <= n; ++pi, ++pj) {
	    _inv[pi] = c;		/* transform to new alphabet.*/
	    c = (c & m) << s | (_inv[pj] - l + 1);
				/* shift in next old symbol in chunk.*/
	}
	while (pi < n) {	/* handle last r-1 positions.*/
	    _inv[pi++] = c;		/* transform to new alphabet.*/
	    c = (c & m) << s;	/* shift right-end zero in chunk.*/
	}
	j = d + 1;		/* new alphabet size.*/
    }
    _inv[n] = 0;			/* end-of-string symbol is zero.*/
    return j;			/* return new alphabet size.*/
}

} // namespace aki_at_gsc_riken_jp

// ***************************************************************************
#endif // SFXA_SORTER_H
