/*
 * $Id: terminal.hh,v 1.1 2003/01/11 20:33:40 logic Exp $
 */

#ifndef __TERMINAL_HH
#  define __TERMINAL_HH __TERMINAL_HH

#include "input.hh"

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
	std::map<std::string,int> keynames;
    public:
	TermInput();
	std::string read();
	void configure( const std::string &s );
	void help( const std::string &s ) const;
	void description() const;
	~TermInput();
};

#endif

