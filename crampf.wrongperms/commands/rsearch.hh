//
// $Id: rsearch.hh,v 1.1 2000/03/19 06:58:24 logic Exp $
//

#ifndef rsearch
#define rsearch rsearch

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

