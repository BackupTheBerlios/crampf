//
// $Id: loop.hh,v 1.1 2000/03/18 13:48:07 logic Exp $
//

#ifndef LOOP
#define LOOP LOOP

#include "../command.hh"
#include "../version_info.hh"
#include <string>

class Loop : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

