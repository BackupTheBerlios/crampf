/*
 * $Id: output.hh,v 1.2 2003/01/11 14:25:41 logic Exp $
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

class StdOutput : public OutputObject {
    public:
	StdOutput();
	void flush();
	~StdOutput();
	void configure( const std::string &s );
	void help( const std::string &s ) const;
	void description() const;
};

/* further ideas:
class SocketOutput : OutputObject {
};
*/

#endif

