//
// $Id: loadplaylist.hh,v 1.1 2000/03/18 08:14:16 logic Exp $
//

#ifndef loadplaylist
#define loadplaylist loadplaylist

#include "../version_info.hh"
#include "../command.hh"
#include <string>

class LoadPlaylist : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};
#endif

