/*
 * $Id: tcpio.hh,v 1.2 2003/01/11 14:25:41 logic Exp $
 */

#ifndef __TCPIO_H
#  define __TCPIO_H __TCPIO_H

#include "input.hh"
#include "output.hh"

class TcpIO : public InputObject, public OutputObject {
    private:
	int svrsockfd;
	std::list<int> sockfds; 
    public:
	TcpIO();
	~TcpIO();
	std::string read();
	void configure( const std::string &s );
	void flush();
};

#endif

