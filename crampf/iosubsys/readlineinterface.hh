/*
 * This Class provides the ex-like interface
 */

#ifndef readlineinterface
#define readlineinterface readlineinterface
#include "version_info.hh"
#include "version_info.hh"

class ReadLineInterface {
  public:
    ReadLineInterface();
    ~ReadLineInterface();
    void input();
    void input( string s );
  private:
    void initialize_readline();
};

#endif

