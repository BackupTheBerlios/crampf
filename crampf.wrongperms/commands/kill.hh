//
// $Id: kill.hh,v 1.4 2002/12/24 19:51:50 logic Exp $
//

#ifndef KILL_HH
#define KILL_HH KILL_HH

#include "../command.hh"
#include <string>

class Kill : public Command {
  public:
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
};

#endif

