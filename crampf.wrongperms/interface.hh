//
// $Id: interface.hh,v 1.15 2000/03/18 04:38:09 logic Exp $
//

#ifndef interface
#define interface

#include "version_info.hh"
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

