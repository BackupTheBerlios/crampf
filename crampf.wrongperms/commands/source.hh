//
// $Id: source.hh,v 1.2 2000/07/16 23:00:57 logic Exp $
//

#ifndef SOURCE
#define SOURCE SOURCE

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

