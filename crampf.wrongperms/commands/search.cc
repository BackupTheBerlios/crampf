#include <string>
#include "../playlist.hh"
#include "../config.hh"
#include "../commandmap.hh"
#include "../player.hh"
#include "search.hh"
#include <stdio.h>

extern Playlist* plist;
extern struct options* opts;

Search::Search( CommandMap* c )
{
  cmap = c;
}

void
Search::doit( string s )
{
  int newpos;
  if (!s.empty())
    cmap->searchstr = s;
  if (cmap->searchstr.empty())
    throw string("search: no searchstring");
  try {
    newpos = search(cmap->searchstr);
    plist->jump(newpos);
    player_play();
  } catch (string error) {
    printf("search: %s\n",error.c_str());
  }
}

void
Search::help( string s )
{
  printf("format: search [<substring>]\n");
  printf("description: searches for the next occurence of <substring>\n");
  printf("in the playlist. if search is successful skips to the found\n");
  printf("track. If <substring> is ommitted the last keyword is used\n");
  printf("again.\n");
}

void
Search::description()
{
  printf("search forward in the playlist\n");
}

int
Search::search( string s )
{
  for (int i=plist->pos()+1; i<plist->size(); i++)
    if ((*plist)[i].title().find(s)!=-1)
      return i;
  if (opts->loop>0) {
  for (int i=0; i<plist->pos(); i++)
    if ((*plist)[i].title().find(s)!=-1) {
      opts->loop--;
      return i;
    }
  }
  throw string("pattern not found");
}
