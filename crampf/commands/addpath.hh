//
// $Id: addpath.hh,v 1.4 2000/07/16 23:00:56 logic Exp $
//

#ifndef ADDPATH
#define ADDPATH ADDPATH

#include <string>
#include "../command.hh"

class AddPath : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

