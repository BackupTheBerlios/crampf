/*
 * Jump to position in playlist
 */

#include <string>
#include "../playlist.hh"
#include "jump.hh"

extern Playlist* plist;

void
Jump::doit( string s )
{
  int pos;
  sscanf(s.c_str(),"%d",&pos);
  plist->jump(pos);
}

void
Jump::help( string s )
{
  printf("jump <position>\n");
  printf("jumps to position <position> in playlist\n");
}
