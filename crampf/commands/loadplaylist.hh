//
// $Id: loadplaylist.hh,v 1.2 2000/07/16 23:00:56 logic Exp $
//

#ifndef LOADPLAYLIST
#define LOADPLAYLIST LOADPLAYLIST

#include "../command.hh"
#include <string>

class LoadPlaylist : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};
#endif

