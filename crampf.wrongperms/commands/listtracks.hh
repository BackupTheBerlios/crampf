//
// $Id: listtracks.hh,v 1.2 2002/06/01 17:27:37 logic Exp $
//

#ifndef LISTTRACKS_HH
#define LISTTRACKS_HH LISTTRACKS_HH

#include <string>
#include "../command.hh"

class ListTracks : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

