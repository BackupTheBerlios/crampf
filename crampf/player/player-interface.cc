#include <unistd.h>
#include "player-interface.hh"
#include "../autocmd.hh"
#include "backends/execplayer/execplayer.hh"
#include "../options.hh"
#include "../autocmd.hh"

extern AutocmdMap autocmdmap;

PlayerInterface::PlayerInterface()
    : GenericPlayer( callback(*this,&PlayerInterface::backendStopped) )
{
      curPlayer = end();
      curPlayer_isPlaying = false;
      block_song_stop_event = false;
      push_back( new ExecPlayer( callback(*this,&PlayerInterface::backendStopped) ) );
}

PlayerInterface::~PlayerInterface()
{
}

bool
PlayerInterface::play( const std::string &filename )
{
      block_song_stop_event = true;
      while( curPlayer_isPlaying )
	  stop();
      block_song_stop_event = false;
      double score, bestscore = 0;
      iterator bestplayer = end();
      for( iterator it = begin(); it != end(); it++ ){
	  score = (*it)->supportedFormat( filename );
	  if( score > bestscore ){
	      bestscore = score;
	      bestplayer = it;
	  }
      }
      if( bestplayer != end() ){
	  if( (*bestplayer)->play( filename ) ){
	      curPlayer = bestplayer;
	      curPlayer_isPlaying = true;
	      autocmdmap["start"].trigger();
	      return true;
	  }
      } else {
	  printdebug( "unsupported fileformat %s\n", filename.c_str() );
      }
      autocmdmap["stop"].trigger();
      return false;
}

double
PlayerInterface::supportedFormat( const std::string &filename ) const
{
      double score, bestscore;
      const_iterator bestplayer = end();
      for( const_iterator it = begin(); it != end(); it++ ){
	  score = (*it)->supportedFormat( filename );
	  if( score > bestscore ){
	      bestscore = score;
	      bestplayer = it;
	  }
      }
      if( bestplayer != end() )
	  return bestscore;
      else
	  return 0.0;
}

bool
PlayerInterface::stop()
{
      if( curPlayer != end() && curPlayer_isPlaying ){
	  if( (*curPlayer)->stop() )
	      curPlayer = end();
	  else
	      throw std::string( "error stopping player" );
      }
      return true;
}

bool
PlayerInterface::isPlaying() const
{
      return curPlayer != end() && curPlayer_isPlaying;
}

void
PlayerInterface::backendStopped( const std::string &msg )
{
      curPlayer = end();
      curPlayer_isPlaying = false;
      if( ! block_song_stop_event ){
	  printdebug( "%s\n", "sending 'stop' event"); //++(*plist);
	  autocmdmap["stop"].trigger();
      } else {
	  printdebug( "%s", "IGNORING SIGNAL\n" );
      }
}
