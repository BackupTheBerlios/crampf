/*
 * $Id: input.hh,v 1.1 2003/01/05 12:39:29 logic Exp $
 */

#ifndef __INPUT_HH
#  define __INPUT_HH __INPUT_HH

#include <string>
#include <queue>
#include <list>
#include <termios.h>
#include "config.h"

#ifdef HAVE_READLINE
#include "readlineinterface.hh"
#endif /* HAVE_READLINE */

class InputObject : public std::queue<std::string> {
    public:
	virtual std::string read() = 0;
	virtual int getFD() const = 0;
	virtual ~InputObject() {}
};

class Input : public std::list<InputObject*> {
    public:
	Input();
	std::string read();
	~Input();
};

extern Input *input;

class TermInput : public InputObject {
    private:
	struct termios terminal_settings;
#ifdef HAVE_READLINE
	ReadLineInterface rli;
#endif /* HAVE_READLINE */
	void restoreTerm() const;
	void singlekeyTerm() const;
	std::string readline( const char *prompt );
    public:
	TermInput();
	std::string read();
	int getFD() const;
	~TermInput();
};

#endif

