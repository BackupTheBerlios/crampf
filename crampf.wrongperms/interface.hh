//
// $Id: interface.hh,v 1.18 2000/12/09 15:52:30 logic Exp $
//

#ifndef INTERFACE
#define INTERFACE INTERFACE

#include <termios.h>
#include "playlist.hh"
#include "readlineinterface.hh"

extern Playlist* plist;
extern struct options* opts;

class Interface {
  public:
    Interface( void );
    ~Interface();
    void init();
    void shutdown();
  private:
    ReadLineInterface rli;
    ReadLineInterface search_rli;
    void use_rli( void );
    void use_search_rli( string s );
    void singlekeyTerm();
    void restoreTerm();
    void detectSoundCard();
    int getVolume();
    void mainloop();
    void changevol(int vol);
    struct termios terminal_settings; 
};

#endif

