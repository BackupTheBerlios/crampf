//
// $Id: loadplaylist.hh,v 1.3 2002/06/01 17:27:37 logic Exp $
//

#ifndef LOADPLAYLIST_HH
#define LOADPLAYLIST_HH LOADPLAYLIST_HH

#include "../command.hh"
#include <string>

class LoadPlaylist : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};
#endif

