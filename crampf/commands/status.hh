//
// One class for each command. doit method called by commandmap
//

#ifndef STATUS_HH
#define STATUS_HH STATUS_HH

#include <string>
#include "../command.hh"

class Status : public Command {
  public:
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
};

#endif
