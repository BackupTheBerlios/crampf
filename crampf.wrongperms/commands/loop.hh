//
// $Id: loop.hh,v 1.2 2000/07/16 23:00:57 logic Exp $
//

#ifndef LOOP
#define LOOP LOOP

#include "../command.hh"
#include <string>

class Loop : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

