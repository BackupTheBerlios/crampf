#include <string>
#include "../playlist.hh"
#include "../config.hh"
#include "../commandmap.hh"
#include "../player/player-interface.hh"
#include "../util/regex.hh"
#include "search.hh"
#include <stdio.h>

extern Playlist* plist;
extern struct options* opts;
extern PlayerInterface *player;

Search::Search( CommandMap* c )
{
  cmap = c;
}

void
Search::doit( const std::string &s )
{
  int newpos;
  if (!s.empty())
    cmap->searchstr = s;
  if (cmap->searchstr.empty())
    throw std::string("search: no searchstring");
  try {
    newpos = search(cmap->searchstr);
    plist->jump(newpos);
    player->play( (**plist).filename() );
  } catch (std::string error) {
    printf("search: %s\n",error.c_str());
  }
}

void
Search::help( const std::string &s ) const
{
  printf("format: search [<substring>]\n");
  printf("description: searches for the next occurence of <substring>\n");
  printf("in the playlist. if search is successful skips to the found\n");
  printf("track. If <substring> is ommitted the last keyword is used\n");
  printf("again.\n");
  printf("see also: rsearch, regexp, case, loop\n");
}

void
Search::description() const
{
  printf("search forward in the playlist\n");
}

int
Search::search( const std::string &s ) const
{
  if (opts->regexp || !opts->casesensivity) {
      /* new regexp part */
      int flags = REG_NOSUB;
      if (!opts->casesensivity)
	  flags = flags | REG_ICASE;
      if (opts->regexp==2)
	  flags = flags | REG_EXTENDED;
      RegEx re = RegEx( s, flags );
      for (unsigned int i=plist->pos()+1; i<plist->size(); i++)
	  if ( re.match( (*plist)[i].title().c_str() ) ) {
	      return i;
	  }
      if (opts->loop!=0) {
	  for (unsigned int i=0; i<plist->pos(); i++)
	      if ( re.match( (*plist)[i].title().c_str() ) ) {
		  return i;
	      }
      }
  } else {
      /* old stl string search function */
      /* TODO kick it! */
      for (unsigned int i=plist->pos()+1; i<plist->size(); i++)
	  if ((signed)((*plist)[i].title().find(s))!=-1)
	      return i;
      if (opts->loop!=0) {
	  for (unsigned int i=0; i<plist->pos(); i++)
	      if ((signed)((*plist)[i].title().find(s))!=-1) {
		  opts->loop--;
		  return i;
	      }
      }
  }
  throw std::string("pattern not found");
}
