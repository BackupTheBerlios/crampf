//
// $Id: loadplaylist.hh,v 1.4 2002/06/04 12:04:18 logic Exp $
//

#ifndef LOADPLAYLIST_HH
#define LOADPLAYLIST_HH LOADPLAYLIST_HH

#include "../command.hh"
#include <string>

class LoadPlaylist : public Command {
  public:
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
};
#endif

