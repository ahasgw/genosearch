// ***************************************************************************
// $Id$
// vim:tabstop=8:shiftwidth=4:softtabstop=4
//
// Creatidx application class
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

#include "creatidx.h"

#ifndef SFXA_BUILDER_H_INCLUDED
# define SFXA_BUILDER_H_INCLUDED 1
# include "sfxa_builder.h"
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

creatidx::creatidx(const char * name, const char * path)
    : d_help(false)
    , d_usage(false)
    , d_version(false)
    , d_verbose(false)
    , d_ignore_case(false)
    , d_calc_lcp(false)
    , d_replace_ext(false)
    , d_idx_suffix(".sqx")
    , d_lcp_suffix(".sqp")
{
    d_program_name = name;
    d_program_path = path;
    d_program_file = d_program_path.substr(d_program_path.rfind('/') + 1);
}

// ===========================================================================
// destructor
// ===========================================================================

creatidx::~creatidx()
{
}

// ===========================================================================
// public method
// ===========================================================================

void creatidx::run(int argc, char ** argv)
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
	    
    if (::optind == argc) {
	show_usage();
	exit(EXIT_SUCCESS);
    }

    // process files
    for (; ::optind < argc; ++::optind) {
	process_file(argv[::optind]);
    }
}

// ===========================================================================
// private methods
// ===========================================================================

void creatidx::recv_option(int argc, char ** argv)
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
	    {"calc-lcp",        no_argument,        NULL, 'p'},
	    {"replace-ext",     no_argument,        NULL, 'r'},
	    {"index-ext",	required_argument,  NULL, 'X'},
	    {"lcp-ext",		required_argument,  NULL, 'P'},
	    {0, 0, 0, 0}
	};

	opt = ::getopt_long(argc, argv, "huVviprX:P:", long_opts, &opt_index);
#else // not HAVE_GETOPT_LONG
	opt = ::getopt(argc, argv, "huVviprX:P:");
#endif // not HAVE_GETOPT_LONG
	if (opt == -1)
	    break;

	switch (opt) {
	    case '?':
	    case ':':
	    case 'h': d_help = true;		    break;
	    case 'u': d_usage = true;		    break;
	    case 'V': d_version = true;		    break;
	    case 'v': d_verbose = true;		    break;
	    case 'i': d_ignore_case = true;	    break;
	    case 'p': d_calc_lcp = true;	    break;
	    case 'r': d_replace_ext = true;	    break;
	    case 'X': d_idx_suffix = ::optarg;	    break;
	    case 'P': d_lcp_suffix = ::optarg;	    break;
	    default: break;
	}
    }
}

void creatidx::show_version() const
{
    cout << get_program_name() << " (" << PACKAGE << ") " << VERSION << endl;
}

void creatidx::show_usage() const
{
    cout << "This is " <<
	get_program_name() << " (" << PACKAGE << ") " << VERSION <<
	", The suffix array generator program.\n"
	"Copyright (C) 2004 RIKEN. All rights reserved.\n"
	"This program comes with ABSOLUTELY NO WARRANTY.\n"
	"You may redistribute copies of this program under the terms of the\n"
	"GNU General Public License.\n"
	"For more information about these matters, see the file named COPYING.\n"
	"\n"
	"Usage: " << get_program_file() << " [ Options ] <file> ...\n"
	"Options:\n"
#ifdef HAVE_GETOPT_LONG
	"  -h, --help                   shows this help message and exit\n"
	"  -u, --usage                  print usage, and exit\n"
	"  -V, --version                print version number, and exit\n"
	"  -v, --verbose                verbose output\n"
	"  -i, --ignore-case            ignore case\n"
	"  -p, --calc-lcp               create lcp file\n"
	"  -r, --replace-ext            replace file extension\n"
	"  -X, --index-ext=.EXT         use extention .EXT for index file\n"
	"  -P, --lcp-ext=.EXT           use extention .EXT for lcp file\n"
#else
	"  -h        shows this help message and exit\n"
	"  -u        print usage, and exit\n"
	"  -V        print version number, and exit\n"
	"  -v        verbose output\n"
	"  -i        case insensitive\n"
	"  -p        create lcp file\n"
	"  -r        replace file extension\n"
	"  -X .EXT   use extention .EXT for index file\n"
	"  -P .EXT   use extention .EXT for lcp file\n"
#endif
	"Report bugs to " << PACKAGE_BUGREPORT "."
	<< endl;
}

void creatidx::process_file(const char * path)
{
    string txtfpath(path);
    string basename = txtfpath.substr(txtfpath.rfind('/') + 1);
    if (opt_replace_ext()) {
	basename = basename.substr(0, basename.rfind('.'));
    }
    string idxfpath = basename + d_idx_suffix;
    string lcpfpath = basename + d_lcp_suffix;

    // check path name
    if (basename.empty()) {
	if (opt_verbose())
	    cerr << "invalid file name. '" << path << "' was ignored." << endl;
	return;
    }

    if (opt_verbose())
	cerr << "processing '" << path << "'..." << endl;

    try {
	auto_ptr<sfxa_builder>
	    builder(new sfxa_builder(
			txtfpath.c_str(),
			idxfpath.c_str(),
			lcpfpath.c_str(),
			opt_calc_lcp(),
			opt_ignore_case()
			));

	if (opt_verbose()) {
	    if (opt_ignore_case())
		cerr << "ignoring character case..." << endl;
	    if (opt_calc_lcp())
		cerr << "lcp calculation flag on..." << endl;
	}

	auto_ptr<sfxa> sa(builder->build());
    }
    catch (...) {
	cerr << "cannot create index." << endl;
    }

    if (opt_verbose())
	cerr << "done." << endl;
}

// ===========================================================================
// main function
// ===========================================================================

int main(int argc, char ** argv);

int main(int argc, char ** argv)
{
    try {
	auto_ptr<creatidx> app(new creatidx("creatidx", argv[0]));
	app->run(argc, argv);
    }

    catch (...) {
cout << "main()" << endl;
	exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

// ***************************************************************************
