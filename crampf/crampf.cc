/*
 * crampf -- Crampf Random Audio Mp3 Player Frontend
 */

#include <stdio.h>
#include "playlist.hh"
#include "config.hh"
#include "player.hh"

int main(int argc, char** argv)
{
  Config cfg(argc, argv);
  struct options* opts=cfg.returnopts();
  Playlist plist;
  plist.addPath(opts->mp3SearchPaths);
  plist.positiveFilter(opts->positiveFilter);
  plist.negativeFilter(opts->negativeFilter);
//  plist.shuffle();
  for (vector<string>::iterator it = plist.begin();
      it != plist.end(); it++)
    printf("%s\n",(const char*)it->c_str());
  Player play(opts->playercmd, opts->playercmd_args, &plist);
  play.play();
}
