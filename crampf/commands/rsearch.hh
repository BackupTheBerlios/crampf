//
// $Id: rsearch.hh,v 1.5 2002/12/24 19:51:50 logic Exp $
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
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
  private:
    int rsearch( const std::string &s ) const;
    CommandMap* cmap;
};

#endif

