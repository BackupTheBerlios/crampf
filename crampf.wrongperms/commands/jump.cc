/*
 * Jump to position in playlist
 */

#include <stdlib.h>
#include <string>
#include "../playlist.hh"
#include "../player/player-interface.hh"
#include "jump.hh"

extern Playlist *plist;
extern PlayerInterface *player;

void
Jump::doit( const std::string &s )
{
  int pos;
  sscanf(s.c_str(),"%d",&pos);
  if (s[0]=='+' || s[0]=='-') 
    pos+=plist->pos();
  else
    pos--; /* first track is 1 for the user, 0 intern */
  try {
    plist->jump(pos);
  } catch (std::string error) {
    if (error=="empty playlist") 
      throw std::string("quit");
    if (error=="end of playlist") 
      throw std::string("quit");
    printf("jump error: %s\n",error.c_str());
  }
  player->play( (**plist).filename() );
}

void
Jump::help( const std::string &s ) const
{
  printf("format: jump <position>\n");
  printf("description: skips current track and jumps to track at\n");
  printf("position <position>. <position> may also be prefixed by\n");
  printf("+ or - resulting in a relative jump\n");
}

void 
Jump::description() const
{
  printf("jump to another song\n");
}
