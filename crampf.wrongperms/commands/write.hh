//
// $Id: write.hh,v 1.3 2002/06/01 17:27:37 logic Exp $
//

#ifndef WRITE_HH
#define WRITE_HH WRITE_HH

#include "../command.hh"
#include <string>

class Write : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
  private:
    string filename;
    bool commit;
};

#endif

