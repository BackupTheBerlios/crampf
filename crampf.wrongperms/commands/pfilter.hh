//
// $Id: pfilter.hh,v 1.3 2002/06/01 17:27:37 logic Exp $
//

#ifndef PFILTER_HH
#define PFILTER_HH PFILTER_HH

#include <string>
#include "../command.hh"

class PFilter : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

