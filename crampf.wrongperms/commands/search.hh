//
// $Id: search.hh,v 1.5 2002/06/04 12:04:18 logic Exp $
//

#ifndef SEARCH_HH
#define SEARCH_HH SEARCH_HH

#include "../command.hh"
#include "../commandmap.hh"
#include <string>

class Search : public Command {
  public: 
    Search( CommandMap *c );
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
  private:
    CommandMap* cmap;
    int search( const string &s ) const;
};

#endif

