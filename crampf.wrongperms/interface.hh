//
// $Id: interface.hh,v 1.4 2000/03/10 18:28:35 logic Exp $
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
    void help( void );
    void quit( void );
  private:
    showstatus();
    mainloop();
    struct termios terminal_settings; 
    bool userexit;
};

#endif

