//
// $Id: write.hh,v 1.2 2000/07/16 23:00:57 logic Exp $
//

#ifndef WRITE
#define WRITE WRITE

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

