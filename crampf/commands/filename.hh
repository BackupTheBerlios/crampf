//
// $Id: filename.hh,v 1.4 2002/06/01 17:27:37 logic Exp $
//

#ifndef FILENAME_HH
#define FILENAME_HH FILENAME_HH

#include "../command.hh"
#include <string>

class Filename : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

