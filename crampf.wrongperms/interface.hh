//
// $Id: interface.hh,v 1.5 2000/03/10 23:04:46 logic Exp $
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
    void next( void );
    void prev( void );
    void jump( void );
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
    void vol_down( void );
  private:
    showstatus();
    mainloop();
    struct termios terminal_settings; 
    bool userexit;
};

#endif

