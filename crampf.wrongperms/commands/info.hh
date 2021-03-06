//
// One class for each command. doit method called by commandmap
//

#ifndef INFO_HH
#define INFO_HH INFO_HH

#include <string>
#include "../command.hh"

class Info : public Command {
  public:
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
};

#endif
