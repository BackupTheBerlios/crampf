/*
 * List playlist
 */

#include <stdlib.h>
#include <string>
#include "../playlist.hh"
#include "../player.hh"
#include "listtracks.hh"
#include "../debug.hh"

extern Playlist* plist;

void
ListTracks::doit( string s )
{
  int pos;
  if( s.empty() )
      pos = plist->pos();
  else {
      sscanf(s.c_str(),"%d",&pos);
      if (s[0]=='+' || s[0]=='-') 
	  pos+=plist->pos();
      else
	  pos--; /* first track is 1 for the user, 0 intern */
  }
  int w=0;
  for( int i=1; i<pos+20; i*=10,w++ );
  char f[512];
  snprintf( f, 512, "%%%dd - %%s\n", w );
  printdebug( "listing tracks from %d to %d\n", pos, pos+20 );
  for(int i = pos; i<plist->size() && i<pos+20; i++ )
      printf( f, i, (*plist)[i].title().c_str() );
}

void
ListTracks::help( string s )
{
  printf("format: list [<position>]\n");
  printf("description: list 20 tracks starting at position\n");
  printf("If position is ommited the next 20 tracks are shown\n");
  printf("+ or - may be used for relative positions\n");
}

void 
ListTracks::description()
{
  printf("list tracks from playlist\n");
}
