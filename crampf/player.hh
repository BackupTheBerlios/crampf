//
// $Id: player.hh,v 1.4 2000/03/18 04:38:09 logic Exp $
//

#ifndef player
#define player

#include "version_info.hh"
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
bool player_restarted( void );

#endif
