/*
 * This Class provides the ex-like interface
 */

#ifndef READLINEINTERFACE_HH
#define READLINEINTERFACE_HH READLINEINTERFACE_HH

class ReadLineInterface {
  public:
    ReadLineInterface();
    ~ReadLineInterface();
    std::string input( const char *prompt );
  private:
    void initialize_readline();
};

#endif

