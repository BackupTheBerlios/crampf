//
// One class for each command. doit method called by commandmap
//

#ifndef VOL_HH
#define VOL_HH VOL_HH

#include <string>
#include "../command.hh"

class Soundcard {
    private:
	enum Type { STANDARD, ULTRASOUND, MAX_TYPE } type;
	char flag[MAX_TYPE];
    public:
	Soundcard();
	int getVolume();
	void setVolume( int vol );
};

class Vol : public Command {
    private:
	Soundcard sndcard;
    public:
	void doit( const std::string &s );
	void help( const std::string &s ) const;
	void description() const;
};

#endif
