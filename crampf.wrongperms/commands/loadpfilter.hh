//
// $Id: loadpfilter.hh,v 1.3 2002/06/01 17:27:37 logic Exp $
//

#ifndef LOADPFILTER_HH
#define LOADPFILTER_HH LOADPFILTER_HH

#include "../command.hh"
#include <string>

class LoadPFilter : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

