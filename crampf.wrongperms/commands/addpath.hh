//
// $Id: addpath.hh,v 1.5 2002/06/01 17:27:37 logic Exp $
//

#ifndef ADDPATH_HH
#define ADDPATH_HH ADDPATH_HH

#include <string>
#include "../command.hh"

class AddPath : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

