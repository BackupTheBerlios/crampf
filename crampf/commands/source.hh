//
// $Id: source.hh,v 1.3 2002/06/01 17:27:37 logic Exp $
//

#ifndef SOURCE_HH
#define SOURCE_HH SOURCE_HH

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

