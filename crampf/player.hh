//
// $Id: player.hh,v 1.1 2000/03/09 01:33:18 logic Exp $
//

#ifndef player
#define player

#include <string>
#include "playlist.hh"

class Player {
  public:
    Player(string playercmd, string playercmd_args,Playlist* pl);
    play();
    stop();
    pause();
    cont();
    next();
    prev();
  private:
    int pid;
    Playlist* plist;
    void signalhandler(int status);
    string playercmd;
    string playercmd_args;
    string filename; /* mp3 filename used by playerthread */
};

#endif

