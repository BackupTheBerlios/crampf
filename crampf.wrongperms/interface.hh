//
// $Id: interface.hh,v 1.23 2002/12/24 19:51:48 logic Exp $
//

#ifndef INTERFACE_HH
#define INTERFACE_HH INTERFACE_HH

#include <termios.h>
#include "playlist.hh"
#include "readlineinterface.hh"

extern Playlist* plist;
extern struct options* opts;

class Interface {
  public:
    Interface();
    ~Interface();
    void init();
    void mainloop();
  private:
    ReadLineInterface rli;
    ReadLineInterface search_rli;
    void use_rli();
    void use_search_rli( const std::string &s );
    void singlekeyTerm() const;
    void restoreTerm() const;
    void detectSoundCard();
    int getVolume() const;
    struct termios terminal_settings; 
};

#endif

