//
// $Id: shuffle.hh,v 1.5 2002/06/01 17:27:37 logic Exp $
//

#ifndef SHUFFLE_HH
#define SHUFFLE_HH SHUFFLE_HH

#include <string>
#include "../command.hh"

class Shuffle : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};
#endif

