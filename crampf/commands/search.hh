//
// $Id: search.hh,v 1.3 2000/07/16 23:00:57 logic Exp $
//

#ifndef SEARCH
#define SEARCH SEARCH

#include "../command.hh"
#include "../commandmap.hh"
#include <string>

class Search : public Command {
  public: 
    Search( CommandMap *c );
    void doit( string s );
    void help( string s );
    void description();
  private:
    CommandMap* cmap;
    int search( string s );
};

#endif

