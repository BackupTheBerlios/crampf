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
 * $Id: addplayer.hh,v 1.1 2002/12/29 00:27:49 logic Exp $
 */

#ifndef __ADDPLAYER_HH
#  define __ADDPLAYER_HH __ADDPLAYER_HH

#include <string>
#include "../command.hh"

class AddPlayer : public Command {
  public:
    AddPlayer();
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
};

#endif

