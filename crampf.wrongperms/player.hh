//
// $Id: player.hh,v 1.8 2002/06/04 19:06:43 logic Exp $
//

#ifndef PLAYER_HH
#define PLAYER_HH PLAYER_HH

#include <string>
#include "playlist.hh"
#include "config.hh"

extern Playlist* plist;
extern struct options* opts;

void player_init( void );
void player_play( void );
void player_stop( void );
void player_sig_playerstop( int status );
void player_pause( void );
void player_continue( void );
bool player_isrunning( void );
bool player_restarted( void );
bool player_finished( void );

#endif
