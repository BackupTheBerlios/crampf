//
// $Id: pfilter.hh,v 1.2 2000/07/16 23:00:57 logic Exp $
//

#ifndef PFILTER
#define PFILTER PFILTER

#include <string>
#include "../command.hh"

class PFilter : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

