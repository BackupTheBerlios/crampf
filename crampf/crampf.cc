/*
 * crampf -- Crampf Random Audio Mp3 Player Frontend
 */

#include <stdio.h>
#include "crampf.hh"
#include "interface.hh"

int main(int argc, char** argv)
{
      try {
	  autocmdmap.newEvent( "next", "called before the next track gets played" );
	  autocmdmap.newEvent( "exit", "called on exit" );
	  autocmdmap.newEvent( "start", "called after initialization, right before playback starts" );
	  plist = new Playlist();
	  Config cfg;
	  opts=cfg.returnopts();
	  cfg.configure(argc, argv);
	  plist->addPath(opts->mp3SearchPaths);
	  plist->addPlaylist(opts->playlistfiles);
	  plist->positiveFilter(opts->positiveFilter);
	  plist->negativeFilter(opts->negativeFilter);
	  plist->loadNegativeFilter( opts->negativeFilterFiles );
	  plist->loadPositiveFilter( opts->positiveFilterFiles );
	  if (opts->randomOrder) {
	      plist->shuffle();
	  }
	  if (plist->empty()) {
	      fprintf(stderr,"No mp3s found!\n");
	      exit(2);
	  }
	  player = player_init();
	  Interface iface;
	  autocmdmap["start"].trigger();
	  iface.mainloop();
	  autocmdmap["exit"].trigger();
      } catch (std::string m) {
	  printf("%s\n",(const char*)m.c_str());
      }
      return 0;
}
