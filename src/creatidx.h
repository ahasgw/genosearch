#ifndef CREATIDX_H
#define CREATIDX_H 1
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

#ifndef STRING_INCLUDED
# define STRING_INCLUDED 1
# include <string>
#endif

namespace aki_at_gsc_riken_jp {

// ===========================================================================
// creatidx class
// ===========================================================================

class creatidx
{
    private:
	std::string d_program_name;
	std::string d_program_path;
	std::string d_program_file;
	
	bool	    d_help;
	bool	    d_usage;
	bool	    d_version;
	bool	    d_verbose;
	bool	    d_ignore_case;
	bool	    d_calc_lcp;
	bool	    d_replace_ext;

	std::string d_idx_suffix;
	std::string d_lcp_suffix;

    public:
	creatidx(const char * name, const char *path);
	~creatidx();

	void run(int argc, char ** argv);

    private:
	// These are not supported and are not implemented!
	creatidx(const creatidx & x);
	creatidx & operator=(const creatidx & x);

	void recv_option(int argc, char ** argv);
	void show_version() const;
	void show_usage() const;

	void process_file(const char * path);

	const std::string & get_program_name() const
	{ return d_program_name; }
	const std::string & get_program_path() const
	{ return d_program_path; }
	const std::string & get_program_file() const
	{ return d_program_file; }

	bool opt_help() const { return d_help; }
	bool opt_usage() const { return d_usage; }
	bool opt_version() const { return d_version; }
	bool opt_verbose() const { return d_verbose; }
	bool opt_ignore_case() const { return d_ignore_case; }
	bool opt_calc_lcp() const { return d_calc_lcp; }
	bool opt_replace_ext() const { return d_replace_ext; }
	const std::string& get_idx_suffix() const   { return d_idx_suffix; }
	const std::string& get_lcp_suffix() const   { return d_idx_suffix; }
};

} // namespace aki_at_gsc_riken_jp

// ***************************************************************************
#endif // CREATIDX_H
