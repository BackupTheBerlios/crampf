//
// $Id: addpath.hh,v 1.1 2000/03/16 12:48:37 logic Exp $
//

#ifndef addpath
#define addpath addpath

#include <string>
#include "../command.hh"

class AddPath : public Command {
  public:
    void doit( string s );
    void help( string s );
};

#endif

