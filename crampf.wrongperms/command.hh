//
// all commands are derived from this base class
//

#ifndef COMMAND_HH
#define COMMAND_HH COMMAND_HH

#include <string>
#include <stdio.h>

class Command {
  public:
    virtual ~Command() {}
    virtual void doit( const string &s ) = 0;
    virtual void help( const string &s ) const = 0;
    virtual void description() const = 0;
};

#endif

