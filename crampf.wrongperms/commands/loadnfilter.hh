//
// $Id: loadnfilter.hh,v 1.3 2002/06/01 17:27:37 logic Exp $
//

#ifndef LOADNFILTER_HH
#define LOADNFILTER_HH LOADNFILTER_HH

#include "../command.hh"
#include <string>

class LoadNFilter : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

