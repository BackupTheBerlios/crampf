/*
 * $Id: input.hh,v 1.3 2003/01/11 14:25:41 logic Exp $
 */

#ifndef __INPUT_HH
#  define __INPUT_HH __INPUT_HH

#include <string>
#include <queue>
#include <list>
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

class TermInput : public InputObject {
    private:
	struct termios terminal_settings;
#ifdef HAVE_READLINE
	ReadLineInterface rli;
#endif /* HAVE_READLINE */
	void restoreTerm() const;
	void singlekeyTerm() const;
	std::string readline( const char *prompt );
	std::map<int,std::string> hotkeys;
    public:
	TermInput();
	std::string read();
	void configure( const std::string &s );
	void help( const std::string &s ) const;
	void description() const;
	~TermInput();
};

#endif

