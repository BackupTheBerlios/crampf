//
// $Id: player-interface.hh,v 1.1 2002/06/04 21:30:05 logic Exp $
//

#ifndef __PLAYER_INTERFACE_HH
#  define __PLAYER_INTERFACE_HH __PLAYER_INTERFACE_HH

class PlayerInterface {
    public:
	virtual ~PlayerInterface() {};
	virtual void play() = 0;
	virtual void stop() = 0;
	virtual void pause() = 0;
	virtual void cont() = 0;
	virtual bool isRunning() = 0;
	virtual bool restarted() = 0;
	virtual bool finished() = 0;
};

#endif

