//
// $Id: filename.hh,v 1.2 2000/03/19 07:17:24 logic Exp $
//

#ifndef filename
#define filename filename

#include "../command.hh"
#include <string>

class Filename : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

