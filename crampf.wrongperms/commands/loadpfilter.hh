//
// $Id: loadpfilter.hh,v 1.2 2000/07/16 23:00:56 logic Exp $
//

#ifndef LOADPFILTER
#define LOADPFILTER LOADPFILTER

#include "../command.hh"
#include <string>

class LoadPFilter : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

