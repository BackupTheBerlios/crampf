//
// $Id: interface.hh,v 1.14 2000/03/16 12:48:30 logic Exp $
//

#ifndef interface
#define interface

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
    void use_rli( void );
    void singlekeyTerm();
    void restoreTerm();
    detectSoundCard();
    int getVolume();
    mainloop();
    changevol(int vol);
    struct termios terminal_settings; 
};

#endif

