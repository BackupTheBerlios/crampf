//
// $Id: crampf.hh,v 1.6 2002/06/04 21:18:36 logic Exp $
//

#ifndef CRAMPF_HH
#define CRAMPF_HH CRAMPF_HH

#include "playlist.hh"
#include "player.hh"
#include "config.hh"
#include "autocmd.hh"

/* global variables */

Playlist* plist;
struct options* opts;
AutocmdMap autocmdmap;
PlayerInterface *player;

#endif

