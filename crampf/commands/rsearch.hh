//
// $Id: rsearch.hh,v 1.3 2002/06/01 17:27:37 logic Exp $
//

#ifndef RSEARCH_HH
#define RSEARCH_HH RSEARCH_HH

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

