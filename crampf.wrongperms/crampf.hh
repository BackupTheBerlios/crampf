//
// $Id: crampf.hh,v 1.8 2003/01/04 18:46:40 logic Exp $
//

#ifndef CRAMPF_HH
#define CRAMPF_HH CRAMPF_HH

#include "playlist.hh"
#include "player/player-interface.hh"
#include "options.hh"
#include "autocmd.hh"

/* global variables */

Playlist* plist;
struct options* opts;
AutocmdMap autocmdmap;
PlayerInterface *player;

#endif

