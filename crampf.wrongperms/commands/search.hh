//
// $Id: search.hh,v 1.6 2002/12/24 19:51:50 logic Exp $
//

#ifndef SEARCH_HH
#define SEARCH_HH SEARCH_HH

#include "../command.hh"
#include "../commandmap.hh"
#include <string>

class Search : public Command {
  public: 
    Search( CommandMap *c );
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
  private:
    CommandMap* cmap;
    int search( const std::string &s ) const;
};

#endif

