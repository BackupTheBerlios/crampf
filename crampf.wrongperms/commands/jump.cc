/*
 * Jump to position in playlist
 */

#include "../version_info.hh"
#include <stdlib.h>
#include <string>
#include "../playlist.hh"
#include "../player.hh"
#include "jump.hh"

extern Playlist* plist;

void
Jump::doit( string s )
{
  int pos;
  sscanf(s.c_str(),"%d",&pos);
  if (s[0]=='+' || s[0]=='-') 
    pos+=plist->pos();
  else
    pos--; /* first track is 1 for the user, 0 intern */
  plist->jump(pos);
  player_play();
}

void
Jump::help( string s )
{
  printf("format: jump <position>\n");
  printf("description: skips current track and jumps to track at\n");
  printf("position <position>. <position> may also be prefixed by\n");
  printf("+ or - resulting in a relative jump\n");
}
