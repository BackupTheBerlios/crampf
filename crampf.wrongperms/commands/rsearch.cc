#include <string>
#include "../playlist.hh"
#include "../config.hh"
#include "../player.hh"
#include "../commandmap.hh"
#include "rsearch.hh"
#include "search.hh"
#include <stdio.h>

extern Playlist* plist;
extern struct options* opts;

RSearch::RSearch( CommandMap* c )
{
  cmap = c;
}

void
RSearch::doit( string s )
{
  int newpos;
  if (!s.empty())
    cmap->searchstr = s;
  if (cmap->searchstr.empty())
    throw string("rsearch: no searchstring");
  try {
    newpos = rsearch(cmap->searchstr);
    plist->jump(newpos);
    player_play();
  } catch (string error) {
    printf("rsearch: %s\n",error.c_str());
  }
}

void
RSearch::help( string s )
{
  printf("format: rsearch [<substring>]\n");
  printf("description: searches backward for the occurence of <substring>\n");
  printf("in the playlist. if rsearch is successful skips to the found\n");
  printf("track. If <substring> is ommitted the last keyword is used\n");
  printf("again.\n");
}

void
RSearch::description()
{
  printf("rsearch backward in the playlist\n");
}

int
RSearch::rsearch( string s )
{
  for (int i=plist->pos()-1; i>=0; i--)
    if ((*plist)[i].title().find(s)!=-1)
      return i;
  if (opts->loop!=0) {
  for (int i=plist->size()-1; i>plist->pos(); i--)
    if ((*plist)[i].title().find(s)!=-1) {
      opts->loop++;
      return i;
    }
  }
  throw string("pattern not found");
}

