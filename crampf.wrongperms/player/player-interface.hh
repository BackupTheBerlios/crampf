//
// $Id: player-interface.hh,v 1.4 2003/01/05 12:39:30 logic Exp $
//

#ifndef __PLAYER_INTERFACE_HH
#  define __PLAYER_INTERFACE_HH __PLAYER_INTERFACE_HH

#include <vector>
#include <sys/time.h>
#include "genplayer.hh"

class PlayerInterface : public std::vector< GenericPlayer* >, public GenericPlayer {
    private:
	iterator curPlayer;
	bool block_song_stop_event,
	     curPlayer_isPlaying;
    public:
	PlayerInterface();
	~PlayerInterface();
	bool play( const std::string &filename );
	bool stop();
	double supportedFormat( const std::string &filename ) const;
	bool isPlaying() const;
	void backendStopped( const std::string &msg );
	/*
	virtual void pause() = 0;
	virtual void cont() = 0;
	virtual bool isRunning() = 0;
	virtual bool restarted() = 0;
	virtual bool finished() = 0;
	*/
	/* Events:
	       "stop"
	 */
};

extern PlayerInterface *player;

#endif
