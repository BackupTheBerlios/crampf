//
// $Id: loadnfilter.hh,v 1.2 2000/07/16 23:00:56 logic Exp $
//

#ifndef LOADNFILTER
#define LOADNFILTER LOADNFILTER

#include "../command.hh"
#include <string>

class LoadNFilter : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

