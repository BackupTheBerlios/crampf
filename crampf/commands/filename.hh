//
// $Id: filename.hh,v 1.3 2000/07/16 23:00:56 logic Exp $
//

#ifndef FILENAME
#define FILENAME FILENAME

#include "../command.hh"
#include <string>

class Filename : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

