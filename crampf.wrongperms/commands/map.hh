//
// $Id: map.hh,v 1.7 2002/12/24 19:51:50 logic Exp $
//

#ifndef MAP_HH
#define MAP_HH MAP_HH

#include <string>
#include "../command.hh"
#include "../commandmap.hh"

class Map : public Command {
  public:
    Map( CommandMap* c );
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
  private:
    CommandMap* cmap;
};

#endif

