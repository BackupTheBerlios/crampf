//
// $Id: map.hh,v 1.5 2002/06/01 17:27:37 logic Exp $
//

#ifndef MAP_HH
#define MAP_HH MAP_HH

#include <string>
#include "../command.hh"
#include "../commandmap.hh"

class Map : public Command {
  public:
    Map( CommandMap* c );
    void doit( string s );
    void help( string s );
    void description();
  private:
    CommandMap* cmap;
};

#endif

