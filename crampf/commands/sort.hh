//
// $Id: sort.hh,v 1.1 2002/04/28 00:41:24 logic Exp $
//

#ifndef SORT
#define SORT SORT

#include "../command.hh"
#include <string>

class Sort : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

