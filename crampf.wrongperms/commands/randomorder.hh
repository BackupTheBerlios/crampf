//
// $Id: randomorder.hh,v 1.3 2002/06/01 17:27:37 logic Exp $
//

#ifndef RANDOMORDER_HH
#define RANDOMORDER_HH RANDOMORDER_HH

#include "../command.hh"
#include <string>

class RandomOrder : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

