//
// $Id: map.hh,v 1.2 2000/03/18 04:38:11 logic Exp $
//

#ifndef map
#define map map

#include "../version_info.hh"
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

