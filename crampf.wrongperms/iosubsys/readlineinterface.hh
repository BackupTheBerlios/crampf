/*
 * This Class provides the ex-like interface
 */

#ifndef READLINEINTERFACE_HH
#define READLINEINTERFACE_HH READLINEINTERFACE_HH

class ReadLineInterface {
  public:
    ReadLineInterface();
    ~ReadLineInterface();
    void input();
    void input( const std::string &s );
  private:
    void initialize_readline();
};

#endif

