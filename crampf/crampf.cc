/*
 * crampf -- Crampf Random Audio Mp3 Player Frontend
 */

#include <stdio.h>
#include "playlist.hh"
#include "config.hh"
#include "player.hh"
#include "crampf.hh"
#include "interface.hh"

int main(int argc, char** argv)
{
  plist = new Playlist();
  Config cfg;
  opts=cfg.returnopts();
  cfg.configure(argc, argv);
  plist->addPath(opts->mp3SearchPaths);
  plist->addPlaylist(opts->playlistfiles);
  plist->positiveFilter(opts->positiveFilter);
  plist->negativeFilter(opts->negativeFilter);
  if (opts->randomOrder) {
    plist->shuffle();
  }
  if (plist->empty()) {
    fprintf(stderr,"No mp3s found!\n");
    exit(2);
  }
  try {
    Interface iface;
  } catch (string m) {
    printf("%s\n",(const char*)m.c_str());
  }
  return 0;
}
