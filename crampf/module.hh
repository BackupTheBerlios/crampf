/*
 * $Id: module.hh,v 1.1 2003/01/11 16:04:25 logic Exp $
 */

#ifndef __MODULE_HH
#  define __MODULE_HH __MODULE_HH

#include <string>
#include <map>

class Module;

typedef std::map<std::string,Module*> Modules;
extern Modules *modules;

/* abstract interface for modules (configurable through module command) */
class Module {
    public:
	Module( const std::string &name ) { (*modules)[name] = this; }
	/* called by module-command */
	virtual void configure( const std::string &s ) = 0;
	virtual void help( const std::string &s ) const = 0;
	virtual void description() const = 0;
	virtual ~Module() {}
};

#endif

