//
// $Id: rsearch.hh,v 1.2 2000/07/16 23:00:57 logic Exp $
//

#ifndef RSEARCH
#define RSEARCH RSEARCH

#include "../command.hh"
#include "../commandmap.hh"
#include "search.hh"
#include <string>

class RSearch : public Command {
  public: 
    RSearch( CommandMap* c );
    void doit( string s );
    void help( string s );
    void description();
  private:
    int rsearch( string s );
    CommandMap* cmap;
};

#endif

