//
// $Id: loadplaylist.hh,v 1.5 2002/12/24 19:51:50 logic Exp $
//

#ifndef LOADPLAYLIST_HH
#define LOADPLAYLIST_HH LOADPLAYLIST_HH

#include "../command.hh"
#include <string>

class LoadPlaylist : public Command {
  public:
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
};
#endif

