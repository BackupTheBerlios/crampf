//
// $Id: map.hh,v 1.4 2000/07/16 23:00:57 logic Exp $
//

#ifndef MAP
#define MAP MAP

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

