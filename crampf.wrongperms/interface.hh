//
// $Id: interface.hh,v 1.17 2000/07/16 23:10:19 logic Exp $
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
    init();
    shutdown();
  private:
    ReadLineInterface rli;
    ReadLineInterface search_rli;
    void use_rli( void );
    void use_search_rli( string s );
    void singlekeyTerm();
    void restoreTerm();
    detectSoundCard();
    int getVolume();
    mainloop();
    changevol(int vol);
    struct termios terminal_settings; 
};

#endif

