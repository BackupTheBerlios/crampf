//
// $Id: samedir.hh,v 1.1 2002/12/30 23:06:58 logic Exp $
//

#ifndef SAMEDIR_HH
#define SAMEDIR_HH SAMEDIR_HH

#include "../command.hh"
#include "../commandmap.hh"
#include <string>

class SameDir : public Command {
  public: 
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
};

#endif

