#include "unify.hh"
#include <stdio.h>
#include <string>
#include <stack>
#include "../playlist.hh"
#include "../iosubsys/output.hh"

void
Unify::doit( const std::string &s )
{
  std::stack<Playlist::iterator> stck;
  for (Playlist::iterator it = plist->begin();
      it != plist->end(); it++) {
    Playlist::const_iterator at = it;
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
  map<string,Playlist::const_iterator> cmp;
  for (Playlist::const_iterator it = plist->begin();
      it != plist->end(); it++)
    if (cmp.count(it->filename())>0) {
      printf("removing %s (=%s)\n",it->title().c_str(),cmp[it->filename()]->title().c_str());
      plist->erase(it);
    } else
      cmp[it->filename()]=it;
}
      */

void
Unify::help( const std::string &s ) const
{
  output->printf("format: unify\n");
  output->printf("description: removes multiple entries in playlist\n");
}

void
Unify::description() const
{
  output->printf("removes multiple entries in playlist\n");
}
