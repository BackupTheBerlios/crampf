//
// $Id: interface.hh,v 1.16 2000/03/19 07:17:23 logic Exp $
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

