//
// $Id: map.hh,v 1.1 2000/03/18 02:17:15 logic Exp $
//

#ifndef map
#define map map

#include <string>
#include "../command.hh"
#include "../commandmap.hh"

class Map : public Command {
  public:
    Map( CommandMap* c );
    void doit( string s );
    void help( string s );
  private:
    CommandMap* cmap;
};

#endif

