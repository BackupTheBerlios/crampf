//
// all commands are derived from this base class
//

#ifndef COMMAND_HH
#define COMMAND_HH COMMAND_HH

#include <string>
#include <stdio.h>

class Command {
  public:
    Command();
    ~Command();
    virtual void doit( string s ) = 0;
    virtual void help( string s ) = 0;
    virtual void description() = 0;
};

#endif

