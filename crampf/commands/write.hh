//
// $Id: write.hh,v 1.1 2000/03/19 12:44:21 logic Exp $
//

#ifndef write
#define write write

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

