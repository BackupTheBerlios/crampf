//
// $Id: nfilter.hh,v 1.3 2002/06/01 17:27:37 logic Exp $
//

#ifndef NFILTER_HH
#define NFILTER_HH NFILTER_HH

#include <string>
#include "../command.hh"

class NFilter : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

