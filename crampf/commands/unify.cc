#include "unify.hh"
#include <stdio.h>
#include <string>
#include <stack>
#include "../playlist.hh"

extern Playlist* plist;

void
Unify::doit( string s )
{
  stack<Playlist::iterator> stck;
  for (Playlist::iterator it = plist->begin();
      it != plist->end(); it++) {
    Playlist::iterator at = it;
    for ( at++; at != plist->end(); at++)
      if (it->filename() == at->filename()) {
          stck.push(it);
      }
  }
  while (!stck.empty()) {
    plist->erase(stck.top());
    stck.pop();
  }
}
  /*
  map<string,Playlist::iterator> cmp;
  for (Playlist::iterator it = plist->begin();
      it != plist->end(); it++)
    if (cmp.count(it->filename())>0) {
      printf("removing %s (=%s)\n",it->title().c_str(),cmp[it->filename()]->title().c_str());
      plist->erase(it);
    } else
      cmp[it->filename()]=it;
}
      */

void
Unify::help( string s )
{
  printf("format: unify\n");
  printf("description: removes multiple entries in playlist\n");
}

void
Unify::description()
{
  printf("removes multiple entries in playlist\n");
}
