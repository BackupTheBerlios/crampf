//
// $Id: echo.hh,v 1.1 2002/07/01 14:38:46 logic Exp $
//

#ifndef __ECHO_HH
#  define __ECHO_HH __ECHO_HH

#include "../command.hh"
#include <string>

class Echo : public Command {
  public:
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
};

#endif

