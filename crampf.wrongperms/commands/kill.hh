//
// $Id: kill.hh,v 1.3 2002/06/04 12:04:18 logic Exp $
//

#ifndef KILL_HH
#define KILL_HH KILL_HH

#include "../command.hh"
#include <string>

class Kill : public Command {
  public:
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
};

#endif

