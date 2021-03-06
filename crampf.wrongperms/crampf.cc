/*
 * crampf -- Crampf Random Audio Mp3 Player Frontend
 */

#include <stdio.h>
#include "crampf.hh"
#include "player/player-interface.hh"
#include "iosubsys/mainloop.hh"
#include "iosubsys/tcpio.hh"
#include "iosubsys/terminal.hh"
#include "iosubsys/stdout.hh"

int main( int argc, char **argv )
{
      try {
	  modules = new Modules();
	  output = new Output();
	  output->push_back( new StdOutput() );
	  input = new Input();
	  input->push_back( new TermInput() );
	  autocmdmap.newEvent( "start", "called whenever a new song gets played" );
	  autocmdmap.newEvent( "stop", "called immediately after playback of a song finishes" );
	  autocmdmap.newEvent( "exit", "called on exit" );
	  autocmdmap.newEvent( "init", "called after initialization, right before playback starts" );
	  plist = new Playlist();
	  Config cfg;
	  opts=cfg.returnopts();
	  player = new PlayerInterface();
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
	  player->play( (**plist).filename() );
#if 0
	  TcpIO *t = new TcpIO();
	  input->push_back( t );
	  output->push_back( t ); /* FIXME ~Input and ~Output delete their contents !! */
#endif
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
      delete modules;
      return 0;
}
