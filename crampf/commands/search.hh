//
// $Id: search.hh,v 1.2 2000/07/03 02:02:40 logic Exp $
//

#ifndef search
#define search search

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

