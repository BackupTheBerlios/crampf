//
// $Id: filename.hh,v 1.1 2000/03/18 13:48:07 logic Exp $
//

#ifndef filename
#define filename filename

#include "../commands.hh"
#include <string>

class Filename : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

