/*
 * $Id: input.hh,v 1.5 2003/01/11 20:33:40 logic Exp $
 */

#ifndef __INPUT_HH
#  define __INPUT_HH __INPUT_HH

#include <string>
#include <queue>
#include <list>
#include <map>
#include <termios.h>
#include "../config.h"
#include "../module.hh"

#ifdef HAVE_READLINE
#include "readlineinterface.hh"
#endif /* HAVE_READLINE */

class InputObject : public std::queue<std::string>, public Module {
    public:
	InputObject( const std::string &name ) : Module( name ) {}
	/* must be non-blocking */
	virtual std::string read() = 0;
	virtual ~InputObject() {}
};

class Input : public std::list<InputObject*> {
    public:
	Input();
	std::string read();
	~Input();
};

extern Input *input;

#endif

