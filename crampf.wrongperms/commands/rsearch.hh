//
// $Id: rsearch.hh,v 1.4 2002/06/04 12:04:18 logic Exp $
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
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
  private:
    int rsearch( const string &s ) const;
    CommandMap* cmap;
};

#endif

