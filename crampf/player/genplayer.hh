/*
 * crampf - generic player interface
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
 * $Id: genplayer.hh,v 1.1 2002/12/28 23:11:59 logic Exp $
 */

#ifndef __GENPLAYER_HH
#  define __GENPLAYER_HH __GENPLAYER_HH

#include <string>
#include "../cb/tcalback.hh"

typedef TCallBack<void,const string &> StopCB;

class GenericPlayer {
    protected:
	StopCB stopCB;
    public:
	GenericPlayer( const StopCB &cb ) : stopCB( cb ) {}
	virtual ~GenericPlayer() {}
	virtual bool play( const std::string &filename ) = 0;
	virtual bool stop() = 0;
	/** returns score on how well the backend can play the given filename
	    (0.0 means i cannot play this song, 1.0 means i am the best backend
	     for this)
	 */
	virtual double supportedFormat( const string &filename ) const = 0;
	/* this method should be *very* fast 'cause it gets called OFTEN! */
	virtual bool isPlaying() const = 0;
	/*
	virtual void pause() = 0;
	virtual void cont() = 0;
	virtual bool isRunning() = 0;
	virtual bool restarted() = 0;
	virtual bool finished() = 0;
	*/
	/* Events:
	       "stop"
	 */
};

#endif

