/*
 * $Id: output.hh,v 1.3 2003/01/11 20:33:40 logic Exp $
 */

#ifndef __OUTPUT_HH
#  define __OUTPUT_HH __OUTPUT_HH

#include <stdio.h>
#include <queue>
#include <list>
#include <string>
#include "../module.hh"

/* generic output backend */
class OutputObject : public std::queue<std::string>, public Module {
    public:
	OutputObject( const std::string &name ) : Module( name ) {}
	virtual void flush() = 0;
	virtual ~OutputObject() {}
};

/* this class is used by the end user */
class Output : public std::list<OutputObject*> {
    public:
	int printf( const char *fmt, ... );
	void flush();
	~Output();
};

extern Output *output;

/* further ideas:
class SocketOutput : OutputObject {
};
*/

#endif

