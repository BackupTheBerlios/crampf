//
// $Id: interface.hh,v 1.21 2002/06/10 02:15:02 logic Exp $
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
  private:
    ReadLineInterface rli;
    ReadLineInterface search_rli;
    void use_rli();
    void use_search_rli( const string &s );
    void singlekeyTerm() const;
    void restoreTerm() const;
    void detectSoundCard();
    int getVolume() const;
    void mainloop();
    struct termios terminal_settings; 
};

#endif

