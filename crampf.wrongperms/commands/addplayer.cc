#include "addplayer.hh"
#include "../player/player-interface.hh"
#include "../player/backends/execplayer/execplayer.hh"

extern PlayerInterface *player;

AddPlayer::AddPlayer()
{
}

void
AddPlayer::doit( const std::string &s )
{
      for( PlayerInterface::iterator it = player->begin();
	      it != player->end(); it++ )
	  if( ExecPlayer *p = dynamic_cast<ExecPlayer *>(*it) )
	      p->addPlayer( s );
}

void
AddPlayer::help( const std::string &s ) const
{
  printf("format: addplayer <playercmd> [<playercmd_args> ...] /<regex>/ <score> [...]\n");
  printf("description: adds a new playercommand to playerbackends\n");
  printf("If one of the given regular expressions match a filename thats\n");
  printf("to be played the player gets a score of <score> (a value between 0.0 and 1.0).\n");
  printf("The player with the highest score is used to play back the given filename.\n");
  printf("List of currently available external players:\n");
  for( PlayerInterface::const_iterator it = player->begin();
	  it != player->end(); it++ )
      if( const ExecPlayer *p = dynamic_cast<const ExecPlayer*>(*it) )
	  for( std::list<struct ExecPlayer::PlayCmds>::const_iterator at
		  = p->getPlayCmds().begin(); at != p->getPlayCmds().end(); at++ ){
	      printf( "\t%12s ", at->cmdname.c_str() );
	      for( std::list<std::string>::const_iterator ot = at->cmdargs.begin();
		      ot != at->cmdargs.end(); ot++ )
		  printf( "%s ", ot->c_str() );
	      for( std::list<std::pair<std::string,double> >::const_iterator ot
		      = at->supportedFilesRegExpAsStrings.begin();
		      ot != at->supportedFilesRegExpAsStrings.end(); ot++ )
		  printf( "/%s/ %2.2f ", ot->first.c_str(), ot->second );
	      putchar( '\n' );
	  }
}

void
AddPlayer::description() const
{
      printf( "add new player backends\n" );
}
