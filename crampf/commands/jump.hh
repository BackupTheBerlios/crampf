//
// $Id: jump.hh,v 1.7 2002/12/24 19:51:50 logic Exp $
//

#ifndef JUMP_HH
#define JUMP_HH JUMP_HH

#include <string>
#include "../command.hh"

class Jump : public Command {
  public:
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
};

#endif

