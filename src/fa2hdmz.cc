// ***************************************************************************
// $Id$
// vim:tabstop=8:shiftwidth=4:softtabstop=4
//
// Fa2HdMz application class
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

#include "fa2hdmz.h"

#ifndef CONFIG_H_INCLUDED
# define CONFIG_H_INCLUDED 1
# include "config.h"
#endif
#ifndef IOSTREAM_INCLUDED
# define IOSTREAM_INCLUDED 1
# include <iostream>
#endif
#ifndef MEMORY_INCLUDED
# define MEMORY_INCLUDED 1
# include <memory>
#endif
#if HAVE_GETOPT_H
# ifndef GETOPT_H_INCLUDED
#  define GETOPT_H_INCLUDED 1
#  include <getopt.h>
# endif
#endif

#ifndef COMMON_TYPE_H_INCLUDED
# define COMMON_TYPE_H_INCLUDED 1
# include "common_type.h"
#endif

using namespace std;
using namespace aki_at_gsc_riken_jp;

#if SIZEOF_VOIDP == 4
    typedef idx32_t	index_t;
#elif SIZEOF_VOIDP == 8
    typedef idx64_t	index_t;
#endif // SIZEOF_VOIDP == 8

float fa2hdmz::ms_table[] = {
     71.0788,	/* A */
      0.0000,	/* B */
    103.1388,	/* C */
    115.0886,	/* D */
    129.1155,	/* E */
    147.1766,	/* F */
     57.0519,	/* G */
    137.1411,	/* H */
    113.1594,	/* I */
      0.0000,	/* J */
    128.1741,	/* K */
    113.1594,	/* L */
    131.1926,	/* M */
    114.1038,	/* N */
      0.0000,	/* O */
     97.1167,	/* P */
    128.1307,	/* Q */
    156.1875,	/* R */
     87.0782,	/* S */
    101.1051,	/* T */
      0.0000,	/* U */
     99.1326,	/* V */
    186.2132,	/* W */
      0.0000,	/* X */
    163.1760,	/* Y */
      0.0000,	/* Z */
};

// ===========================================================================
// constructor
// ===========================================================================

fa2hdmz::fa2hdmz(const char * name, const char * path)
    : d_help(false)
    , d_usage(false)
    , d_version(false)
    , d_verbose(false)
    , d_basename("stdin")
    , d_hdr_suffix(".hdr")
    , d_hdx_suffix(".hdx")
    , d_dmz_suffix(".dmz")
{
    d_program_name = name;
    d_program_path = path;
    d_program_file = d_program_path.substr(d_program_path.rfind('/') + 1);
}

// ===========================================================================
// destructor
// ===========================================================================

fa2hdmz::~fa2hdmz()
{
}

// ===========================================================================
// public method
// ===========================================================================

void fa2hdmz::run(int argc, char ** argv)
{
    recv_option(argc, argv);

    if (opt_version()) {
	// show version number and exit normally
	show_version();
	exit(EXIT_SUCCESS);
    }

    if (opt_help() || opt_usage()) {
	// show usage and exit normally
	show_usage();
	exit(EXIT_SUCCESS);
    }

    if (::optind < argc) {
	for (; ::optind < argc; ++::optind)
	    process_file(argv[::optind]);
    } else {
	process_file();
    }
}

// ===========================================================================
// private methods
// ===========================================================================

void fa2hdmz::recv_option(int argc, char ** argv)
{
    for (;;) {
	int opt;
#ifdef HAVE_GETOPT_LONG
	int opt_index = 0;
	static struct option long_opts[] = {
	    {"help",            no_argument,        NULL, 'h'},
	    {"usage",           no_argument,        NULL, 'u'},
	    {"version",         no_argument,        NULL, 'V'},
	    {"verbose",         no_argument,        NULL, 'v'},
	    {"basename",	required_argument,  NULL, 'b'},
	    {0, 0, 0, 0}
	};

	opt = ::getopt_long(argc, argv, "huVvb:", long_opts, &opt_index);
#else // not HAVE_GETOPT_LONG
	opt = ::getopt(argc, argv, "huVvb:");
#endif // not HAVE_GETOPT_LONG
	if (opt == -1)
	    break;

	switch (opt) {
	    case '?':
	    case ':':
	    case 'h': d_help = true;		break;
	    case 'u': d_usage = true;		break;
	    case 'V': d_version = true;		break;
	    case 'v': d_verbose = true;		break;
	    case 'b': d_basename = ::optarg;	break;
	    default: break;
	}
    }
}

void fa2hdmz::show_version() const
{
    cout << get_program_name() << " (" << PACKAGE << ") " << VERSION << endl;
}

void fa2hdmz::show_usage() const
{
    cout << "This is " <<
	get_program_name() << " (" << PACKAGE << ") " << VERSION <<
	", Fasta format to header/differential m over z separator rogram.\n"
	"Copyright (C) 2004 RIKEN. All rights reserved.\n"
	"This program comes with ABSOLUTELY NO WARRANTY.\n"
	"You may redistribute copies of this program under the terms of the\n"
	"GNU General Public License.\n"
	"For more information about these matters, see the file named COPYING.\n"
	"\n"
	"Usage: " << get_program_file() << " [ Options ] [ <file> ... ]\n"
	"Options:\n"
#ifdef HAVE_GETOPT_LONG
	"  -h, --help               shows this help message and exit\n"
	"  -u, --usage              print usage, and exit\n"
	"  -V, --version            print version number, and exit\n"
	"  -v, --verbose            verbose output\n"
	"  -b, --basename=BASENAME  base name for newly created file (for stdin)\n"
#else
	"  -h             shows this help message and exit\n"
	"  -u             print usage, and exit\n"
	"  -V             print version number, and exit\n"
	"  -v             verbose output\n"
	"  -b, BASENAME   base name for newly created file (for stdin)\n"
#endif
	"Report bugs to " << PACKAGE_BUGREPORT "."
	<< endl;
}

void fa2hdmz::process_file(const char * basename)
{
    try {
	string bn = ((basename == 0) ? d_basename : basename);
	FILE * _in = ((basename == 0) ? stdin : fopen(bn.c_str(), "r"));

	if (opt_verbose()) cout << "processing '" << bn << "'...\n";

	if (_in != 0)
	{
	    string hdrfn = bn + d_hdr_suffix;
	    string hdxfn = bn + d_hdx_suffix;
	    string dmzfn = bn + d_dmz_suffix;

	    FILE * _ohdr;
	    FILE * _ohdx;
	    FILE * _odmz;

	    if (((_ohdr = fopen(hdrfn.c_str(), "w")) != 0)
		&& ((_ohdx = fopen(hdxfn.c_str(), "wb")) != 0)
		&& ((_odmz = fopen(dmzfn.c_str(), "wb")) != 0))
	    {
		index_t hdr_beg = 0;
		index_t hdr_len = 0;
		index_t dmz_beg = 0;
		index_t dmz_len = 0;

		const float zero = 0.0;
		char *line = NULL;
		size_t len = 0;
		ssize_t read;
		while ((read = getline(&line, &len, _in)) != -1) {
		    if (read <= 1)	/* empty line or delimiter only */
			continue;
		    if (*line == '>') {
			fwrite(&zero, sizeof(float), 1, _odmz);
			if (hdr_len > 0) {
			    /*
			    * hdx[0] = {dmz_beg0, hdr_beg0}
			    * hdx[1] = {dmz_beg1, hdr_beg1}
			    *  ...
			    * hdx[n-1] = {dmz_beg(n-1), hdr_beg(n-1)}
			    */
			    {
				index_t dmz_end = dmz_beg + dmz_len;
				fwrite(&dmz_beg, sizeof(index_t), 1, _ohdx);
				fwrite(&dmz_end, sizeof(index_t), 1, _ohdx);
				fwrite(&hdr_beg, sizeof(index_t), 1, _ohdx);
			    }
			    dmz_beg += (dmz_len + 1), dmz_len = 0;
			    hdr_beg += hdr_len, hdr_len = 0;
			} else {
			    ++dmz_beg;
			}
			line[read - 1] = '\0';  /* truncate delimiter */
			fputs(line + 1, _ohdr);
			fputc('\0', _ohdr);
			hdr_len = read - 2 + 1;
		    } else {
			line[read - 1] = '\0';  /* truncate delimiter */
			{
			    float mz;
			    char *cp;
			    for (cp = line; *cp != '\0'; ++cp) {
				mz = ms_table[toupper(*cp) - 'A'];
				fwrite(&mz, sizeof(float), 1, _odmz);
			    }
			}
			dmz_len += read - 1;
		    }
		}
		{
		    index_t dmz_end = dmz_beg + dmz_len;
		    fwrite(&dmz_beg, sizeof(index_t), 1, _ohdx);
		    fwrite(&dmz_end, sizeof(index_t), 1, _ohdx);
		    fwrite(&hdr_beg, sizeof(index_t), 1, _ohdx);
		    fwrite(&zero, sizeof(float), 1, _odmz);
		}
	    }
	    if (_odmz) fclose(_odmz), _odmz = 0;
	    if (_ohdx) fclose(_ohdx), _ohdx = 0;
	    if (_ohdr) fclose(_ohdr), _ohdr = 0;
	} else {
	    perror(bn.c_str());
	}

	if (opt_verbose()) cout << "done.\n";
    }

    catch (...) {
    }
}

// ===========================================================================
// main function
// ===========================================================================

int main(int argc, char ** argv);

int main(int argc, char ** argv)
{
    try {
	auto_ptr<fa2hdmz> app(new fa2hdmz("fa2hdmz", argv[0]));
	app->run(argc, argv);
    }

    catch (...) {
	exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

// ***************************************************************************
