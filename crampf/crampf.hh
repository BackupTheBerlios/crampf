//
// $Id: crampf.hh,v 1.10 2003/01/11 14:25:38 logic Exp $
//

#ifndef CRAMPF_HH
#define CRAMPF_HH CRAMPF_HH

#include "playlist.hh"
#include "player/player-interface.hh"
#include "options.hh"
#include "autocmd.hh"
#include "module.hh"
#include "iosubsys/output.hh"
#include "iosubsys/input.hh"

/* global variables */

Playlist* plist;
struct Options* opts;
AutocmdMap autocmdmap;
PlayerInterface *player;
Input *input;
Output *output;
Modules *modules;

#endif

