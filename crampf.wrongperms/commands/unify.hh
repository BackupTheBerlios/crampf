//
// $Id: unify.hh,v 1.1 2000/03/19 15:00:57 logic Exp $
//

#ifndef unify
#define unify unify

#include "../command.hh"
#include <string>

class Unify : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

