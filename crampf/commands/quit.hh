//
// One class for each command. doit method called by commandmap
//

#ifndef QUIT_HH
#define QUIT_HH QUIT_HH

#include <string>
#include "../command.hh"

class Quit : public Command {
  public:
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
};

#endif
