//
// $Id: jump.hh,v 1.6 2002/06/04 12:04:18 logic Exp $
//

#ifndef JUMP_HH
#define JUMP_HH JUMP_HH

#include <string>
#include "../command.hh"

class Jump : public Command {
  public:
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
};

#endif

