//
// $Id: interface.hh,v 1.1 2000/03/10 07:16:58 logic Exp $
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
    showstatus();
    mainloop();
    struct termios terminal_settings; 
};

#endif

