//
// $Id: loop.hh,v 1.5 2002/12/24 19:51:50 logic Exp $
//

#ifndef LOOP_HH
#define LOOP_HH LOOP_HH

#include "../command.hh"
#include <string>

class Loop : public Command {
  public:
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
};

#endif

