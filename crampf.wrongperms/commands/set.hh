//
// One class for each command. doit method called by commandmap
//

#ifndef SET_HH
#define SET_HH SET_HH

#include <string>
#include "../command.hh"
#include "../commandmap.hh"

class Set : public Command {
  public:
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
};

#endif
