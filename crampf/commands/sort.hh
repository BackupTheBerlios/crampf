//
// $Id: sort.hh,v 1.2 2002/06/01 17:27:37 logic Exp $
//

#ifndef SORT_HH
#define SORT_HH SORT_HH

#include "../command.hh"
#include <string>

class Sort : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

