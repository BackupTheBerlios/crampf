//
// $Id: crampf.hh,v 1.9 2003/01/05 12:39:24 logic Exp $
//

#ifndef CRAMPF_HH
#define CRAMPF_HH CRAMPF_HH

#include "playlist.hh"
#include "player/player-interface.hh"
#include "options.hh"
#include "autocmd.hh"
#include "iosubsys/input.hh"
#include "iosubsys/output.hh"

/* global variables */

Playlist* plist;
struct Options* opts;
AutocmdMap autocmdmap;
PlayerInterface *player;
Input *input;
Output *output;

#endif

