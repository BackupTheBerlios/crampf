//
// $Id: source.hh,v 1.1 2000/03/19 04:18:50 logic Exp $
//

#ifndef source
#define source source

#include "../command.hh"
#include "../commandmap.hh"
#include <string>

class Source : public Command {
  public:
    Source( CommandMap* c );
    void doit( string s );
    void help( string s );
    void description();
  private:
    CommandMap* cmap;
};

#endif

