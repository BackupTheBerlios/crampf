/*
 * This Class provides the ex-like interface
 */

#ifndef READLINEINTERFACE
#define READLINEINTERFACE READLINEINTERFACE

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

