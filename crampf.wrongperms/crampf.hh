//
// $Id: crampf.hh,v 1.7 2002/12/28 23:11:51 logic Exp $
//

#ifndef CRAMPF_HH
#define CRAMPF_HH CRAMPF_HH

#include "playlist.hh"
#include "player/player-interface.hh"
#include "config.hh"
#include "autocmd.hh"

/* global variables */

Playlist* plist;
struct options* opts;
AutocmdMap autocmdmap;
PlayerInterface *player;

#endif

