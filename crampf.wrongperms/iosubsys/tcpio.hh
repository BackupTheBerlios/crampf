/*
 * $Id: tcpio.hh,v 1.1 2003/01/09 09:15:41 logic Exp $
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
	void flush();
};

#endif

