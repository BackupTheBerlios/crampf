//
// $Id: map.hh,v 1.6 2002/06/04 12:04:18 logic Exp $
//

#ifndef MAP_HH
#define MAP_HH MAP_HH

#include <string>
#include "../command.hh"
#include "../commandmap.hh"

class Map : public Command {
  public:
    Map( CommandMap* c );
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
  private:
    CommandMap* cmap;
};

#endif

