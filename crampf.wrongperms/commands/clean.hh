//
// $Id: clean.hh,v 1.1 2002/12/30 22:24:47 logic Exp $
//

#ifndef CLEAN_HH
#define CLEAN_HH CLEAN_HH

#include "../command.hh"
#include <string>

class Clean : public Command {
  public:
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
};

#endif

