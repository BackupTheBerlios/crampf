//
// $Id: loop.hh,v 1.3 2002/06/01 17:27:37 logic Exp $
//

#ifndef LOOP_HH
#define LOOP_HH LOOP_HH

#include "../command.hh"
#include <string>

class Loop : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

