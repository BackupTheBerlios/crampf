#include <string>
#include "../playlist.hh"
#include "../config.hh"
#include "../commandmap.hh"
#include "../player/player-interface.hh"
#include "../util/regex.hh"
#include "samedir.hh"
#include <stdio.h>

extern Playlist* plist;
extern struct options* opts;
extern PlayerInterface *player;

void
SameDir::doit( const std::string &s )
{
      long dirlevel = 1;
      if( !s.empty() )
	  dirlevel = strtol( s.c_str(), NULL, 10 );
      if( dirlevel > 0 ){
	  int i = (**plist).filename().size();
	  while( i-- > 0 ){
	      if( (**plist).filename()[i] == '/' ){
		  dirlevel--;
		  if( dirlevel == 0 ){
		      /* skip to next song */
		      std::string dirname = (**plist).filename().substr( 0, i+1 );
		      for (unsigned int i=plist->pos()+1; i<plist->size(); i++)
			  if( (*plist)[i].filename().find(dirname) == 0 &&
				  player->supportedFormat( (*plist)[i].filename() ) != 0.0 ){
			      plist->jump( i );
			      player->play( (**plist).filename() );
			      return;
			  }
		      if (opts->loop!=0) 
			  for (unsigned int i=0; i<plist->pos(); i++)
			      if( (*plist)[i].filename().find(dirname) == 0 &&
				      player->supportedFormat( (*plist)[i].filename() ) != 0.0 ){
				  plist->jump( i );
				  player->play( (**plist).filename() );
				  return;
			      }
		      throw std::string( "not found" );
		  }
	      }
	  }
      }
      throw std::string("failed");
}

void
SameDir::help( const std::string &s ) const
{
  printf("format: samedir [<dirlevel>]\n");
  printf("description: searches for next file within the same directory.\n");
  printf("the optional <dirlevel> argument specifies what directory should\n");
  printf("be used. It defaults to 1 which means same directory as current\n");
  printf("song.\n");
  printf("Example: if the current song played is /data/mp3/Artist/Album/track.mp3\n");
  printf("a <dirlevel> of 2 would mean search for the next song in directory\n");
  printf("/data/mp3/Artist\n");
}

void
SameDir::description() const
{
  printf("search for next song in the same directory as current song\n");
}
