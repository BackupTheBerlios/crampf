//
// $Id: player.hh,v 1.2 2000/03/09 21:55:24 logic Exp $
//

#ifndef player
#define player

#include <string>
#include "playlist.hh"
#include "config.hh"

extern Playlist* plist;
extern struct options* opts;

void player_init( void );
void player_play( void );
void player_stop( void );
void player_playerstop( int status );
void player_pause( void );
void player_continue( void );
bool player_isrunning( void );

#endif
