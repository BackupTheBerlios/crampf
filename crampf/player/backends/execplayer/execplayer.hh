/*
 * $PROJECT - $DESCRIPTION
 * Copyright (C) 2002-2003 Kevin Loos
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * 
 * $Id: execplayer.hh,v 1.2 2002/12/29 00:27:51 logic Exp $
 */

#ifndef __EXECPLAYER_HH
#  define __EXECPLAYER_HH __EXECPLAYER_HH

#include <list>
#include "../../genplayer.hh"
#include "../../../util/regex.hh"

class ExecPlayer : public GenericPlayer {
    public:
	typedef std::pair<RegEx*,double> SupportedFilesRegExp;
	typedef std::pair<std::string,double> SupportedFilesRegExpAsStrings;
	struct PlayCmds {
	    std:: string cmdname;
	    std::list<std::string> cmdargs;
	    std::list<SupportedFilesRegExp> supportedFilesRegExp;
	    std::list<SupportedFilesRegExpAsStrings> supportedFilesRegExpAsStrings;
	};
	
	ExecPlayer( const StopCB &cb );
	~ExecPlayer();
	virtual bool play( const std::string &filename );
	virtual bool stop();
	virtual double supportedFormat( const string &filename ) const;
	bool addPlayer( const std::string &cmdname,
		const std::list<std::string> &cmdargs, 
		const std::list<SupportedFilesRegExp> &supportedFilesRegExp,
		const std::list<SupportedFilesRegExpAsStrings> &supportedFilesRegExpAsStrings );
	bool addPlayer( const std::string &cfgstr );
	static ExecPlayer *self;
	bool isPlaying() const;
	void signalHandler( int status );
	const std::list<struct PlayCmds> &getPlayCmds() const;
    private:
	int pid;
	bool processSignals;
	std::list< struct PlayCmds > playCmds;
};

#endif

