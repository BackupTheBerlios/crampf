//
// $Id: echo.hh,v 1.2 2002/12/24 19:51:50 logic Exp $
//

#ifndef __ECHO_HH
#  define __ECHO_HH __ECHO_HH

#include "../command.hh"
#include <string>

class Echo : public Command {
  public:
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
};

#endif

