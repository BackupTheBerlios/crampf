//
// $Id: stdplayer.hh,v 1.1 2002/06/04 21:18:44 logic Exp $
//

#ifndef __STDPLAYER_HH
#  define __STDPLAYER_HH __STDPLAYER_HH

#include "../player-interface.hh"
#include "../../playlist.hh"
#include "../../config.hh"

extern Playlist* plist;
extern struct options* opts;

class StdPlayer : public PlayerInterface {
    public:
	StdPlayer();
	~StdPlayer();
	void play();
	void stop();
	void pause();
	void cont();
	bool isRunning();
	bool restarted();
	bool finished();
	// hack: only for use with the signal handler
	void signalHandler( int status );
	static StdPlayer *self;
    private:
	int pid;
	bool sigignore;
	bool newsong;
	bool first_track_damaged;
	bool has_finished;
};

#endif

