//
// $Id: nfilter.hh,v 1.2 2000/07/16 23:00:57 logic Exp $
//

#ifndef NFILTER
#define NFILTER NFILTER

#include <string>
#include "../command.hh"

class NFilter : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

