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
  Config cfg(argc, argv);
  opts=cfg.returnopts();
  plist = new Playlist();
  plist->addPath(opts->mp3SearchPaths);
  plist->positiveFilter(opts->positiveFilter);
  plist->negativeFilter(opts->negativeFilter);
  /*
  for (Playlist::iterator it = plist->begin();
      it != plist->end(); it++)
    printf("%s\n",(const char*)it->filename().c_str());
  */
  Interface iface;
  printf("tschoess\n");
  return 0;
}
