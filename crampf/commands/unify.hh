//
// $Id: unify.hh,v 1.3 2002/06/01 17:27:37 logic Exp $
//

#ifndef UNIFY_HH
#define UNIFY_HH UNIFY_HH

#include "../command.hh"
#include <string>

class Unify : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

