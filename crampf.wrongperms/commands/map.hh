//
// $Id: map.hh,v 1.3 2000/03/18 08:14:16 logic Exp $
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
    void description();
  private:
    CommandMap* cmap;
};

#endif

