/*
 * crampf -- Crampf Random Audio Mp3 Player Frontend
 */

#include <stdio.h>
#include "crampf.hh"
#include "player/player-interface.hh"
#include "iosubsys/output.hh"
#include "iosubsys/input.hh"
#include "iosubsys/mainloop.hh"

int main( int argc, char **argv )
{
      try {
	  output = new Output();
	  output->push_back( new StdOutput() );
	  autocmdmap.newEvent( "start", "called whenever a new song gets played" );
	  autocmdmap.newEvent( "stop", "called immediately after playback of a song finishes" );
	  autocmdmap.newEvent( "exit", "called on exit" );
	  autocmdmap.newEvent( "init", "called after initialization, right before playback starts" );
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
	  player = new PlayerInterface();
	  player->play( (**plist).filename() );
	  input = new Input();
	  input->push_back( new TermInput() );
	  autocmdmap["init"].trigger();
	  mainloop();
	  autocmdmap["exit"].trigger();
      } catch (std::string error) {
	  if (error!="quit" && error!="exit")
	      output->printf("error: `%s'\n",error.c_str());
	  if (error!="exit")
	      player->stop();
      } catch( ... ){
	  fprintf( stderr, "caught unknown exception: shutting down...\n" );
	  return 1;
      }
      delete plist;
      delete player;
      delete input;
      delete output;
      return 0;
}
