//
// $Id: mod.hh,v 1.1 2003/01/11 14:25:40 logic Exp $
//

#ifndef MOD_HH
#define MOD_HH MOD_HH

#include <string>
#include "../command.hh"

class Mod : public Command {
  public:
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
};

#endif

