#include "player.hh"
#include "player/stdplayer/stdplayer.hh"

PlayerInterface *player_init()
{
      return new StdPlayer();
}
