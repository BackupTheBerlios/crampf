//
// $Id: interface.hh,v 1.13 2000/03/16 06:54:34 logic Exp $
//

#ifndef interface
#define interface

#include <termios.h>
#include "playlist.hh"

extern Playlist* plist;
extern struct options* opts;

class Interface {
  public:
    Interface( void );
    ~Interface();
    init();
    shutdown();
  private:
    void rli( void );
    void singlekeyTerm();
    void restoreTerm();
    detectSoundCard();
    int getVolume();
    mainloop();
    changevol(int vol);
    struct termios terminal_settings; 
};

#endif

