// ***************************************************************************
// $Id$
// vim:tabstop=8:shiftwidth=4:softtabstop=4
//
// Isearch application class
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

#include "isearch.h"

#ifndef SFXA_OPENER_H_INCLUDED
# define SFXA_OPENER_H_INCLUDED 1
# include "sfxa_opener.h"
#endif
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

#include "sfxa.h"

using namespace std;
using namespace aki_at_gsc_riken_jp;

// ===========================================================================
// constructor
// ===========================================================================

isearch::isearch(const char * name, const char * path)
    : d_help(false)
    , d_usage(false)
    , d_version(false)
    , d_verbose(false)
    , d_ignore_case(false)
{
    d_program_name = name;
    d_program_path = path;
    d_program_file = d_program_path.substr(d_program_path.rfind('/') + 1);
}

// ===========================================================================
// destructor
// ===========================================================================

isearch::~isearch()
{
}

// ===========================================================================
// public method
// ===========================================================================

void isearch::run(int argc, char ** argv)
{
    recv_option(argc, argv);

    if (::optind + 2 > argc) {
	show_usage();
	exit(EXIT_SUCCESS);
    }

    try {
	d_txtfpath = argv[::optind++];
	d_idxfpath = argv[::optind++];

	if (opt_verbose()) {
	    cerr << "text file:\t'" << d_txtfpath << "'\n";
	    cerr << "index file:\t'" << d_idxfpath << "'\n";
	    if (opt_use_lcp())
		cerr << "lcp file:\t'" << d_lcpfpath << "'\n";
	    if (opt_ignore_case())
		cerr << "ignoring character case...\n";
	}

	// open sfxa
	{
	    auto_ptr<sfxa_opener> opener(
		    new sfxa_opener(
			d_txtfpath.c_str(), d_idxfpath.c_str(), d_lcpfpath.c_str(),
			opt_use_lcp(), opt_ignore_case()
			)
		    );
	    d_sa = opener->open();
	}

	// process files
	for (; ::optind < argc; ++::optind) {
	    if (opt_verbose()) {
		cerr << "searching '" << argv[::optind] << "'..." << endl;
	    }

	    // search
	    d_sa->search(argv[::optind]);

	    if (opt_verbose()) {
		cerr << "done." << endl;
	    }
	}
    }

    catch (...) {
	throw;
    }
}

// ===========================================================================
// private methods
// ===========================================================================

void isearch::recv_option(int argc, char ** argv)
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
	    {"ignore-case",     no_argument,        NULL, 'i'},
	    {"lcp-file",	required_argument,  NULL, 'p'},
	    {0, 0, 0, 0}
	};

	opt = ::getopt_long(argc, argv, "huVvip:", long_opts, &opt_index);
#else // not HAVE_GETOPT_LONG
	opt = ::getopt(argc, argv, "huVvip:");
#endif // not HAVE_GETOPT_LONG
	if (opt == -1)
	    break;

	switch (opt) {
	    case '?':
	    case 'h': d_help = true;		break;
	    case 'u': d_usage = true;		break;
	    case 'V': d_version = true;		break;
	    case 'v': d_verbose = true;		break;
	    case 'i': d_ignore_case = true;	break;
	    case 'p': d_lcpfpath = ::optarg;	break;
	    default: break;
	}
    }
}

void isearch::show_version() const
{
    cout << get_program_name() << " (" << PACKAGE << ") " << VERSION << endl;
}

void isearch::show_usage() const
{
    cout << "This is " <<
	get_program_name() << " (" << PACKAGE << ") " << VERSION <<
	", The index search program.\n"
	"Copyright (C) 2004 RIKEN. All rights reserved.\n"
	"This program comes with ABSOLUTELY NO WARRANTY.\n"
	"You may redistribute copies of this program under the terms of the\n"
	"GNU General Public License.\n"
	"For more information about these matters, see the file named COPYING.\n"
	"\n"
	"Usage: " << get_program_file()
	<< " [ Options ] <seq_file> <sqx_file> [ PATTERN ... ]\n"
#ifdef HAVE_GETOPT_LONG
	"  -h, --help                   shows this help message and exit\n"
	"  -u, --usage                  print usage, and exit\n"
	"  -V, --version                print version number, and exit\n"
	"  -v, --verbose                verbose output\n"
	"  -i, --ignore-case            case insensitive\n"
	"  -p, --lcp-file=<sqp_file>    use lcp file\n"
#else
	"  -h              shows this help message and exit\n"
	"  -u              print usage, and exit\n"
	"  -V              print version number, and exit\n"
	"  -v              verbose output\n"
	"  -i              case insensitive\n"
	"  -p, <sqp_file>  use lcp file\n"
#endif
	"Report bugs to " << PACKAGE_BUGREPORT "."
	<< endl;
}

// ===========================================================================
// main function
// ===========================================================================

int main(int argc, char ** argv);

int main(int argc, char ** argv)
{
    try {
	auto_ptr<isearch> app(new isearch("isearch", argv[0]));
	app->run(argc, argv);
    }

    catch (...) {
	exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

// ***************************************************************************
