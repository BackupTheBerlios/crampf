//
// One class for each command. doit method called by commandmap
//

#ifndef VOL_HH
#define VOL_HH VOL_HH

#include <string>
#include "../command.hh"

class Vol : public Command {
  public:
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
};

#endif
