//
// $Id: listtracks.hh,v 1.1 2002/04/28 01:19:10 logic Exp $
//

#ifndef LISTTRACKS
#define LISTTRACKS LISTTRACKS

#include <string>
#include "../command.hh"

class ListTracks : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

