//
// $Id: interface.hh,v 1.11 2000/03/13 04:01:36 logic Exp $
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
    void info( void );
    void list( void );
    void file( void );
    void next( void );
    void prev( void );
    void jump( void );
    void pause( void );
    void cont( void );
    void vol0( void );
    void vol1( void );
    void vol2( void );
    void vol3( void );
    void vol4( void );
    void vol5( void );
    void vol6( void );
    void vol7( void );
    void vol8( void );
    void vol9( void );
    void vol_up( void );
    void vol_dn( void );
    void cli( void );
  private:
    showstatus();
    void singlekeyTerm();
    void restoreTerm();
    detectSoundCard();
    int getVolume();
    mainloop();
    changevol(int vol);
    struct termios terminal_settings; 
    int volume;
};

#endif

