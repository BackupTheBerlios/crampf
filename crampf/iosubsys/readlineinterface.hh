/*
 * This Class provides the ex-like interface
 */

#ifndef readlineinterface
#define readlineinterface readlineinterface

class ReadLineInterface {
  public:
    ReadLineInterface();
    ~ReadLineInterface();
    void input();
  private:
    void initialize_readline();
};

#endif

