//
// $Id: search.hh,v 1.4 2002/06/01 17:27:37 logic Exp $
//

#ifndef SEARCH_HH
#define SEARCH_HH SEARCH_HH

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

