#include "mainloop.hh"
#include "input.hh"
#include "output.hh"
#include "../options.hh"
#include "../debug.hh"
#include <unistd.h>

void mainloop()
{
      while(1){
	  output->flush();
	  usleep(100);
	  std::string cmd = input->read();
	  try {
	      if( ! cmd.empty() ){
		  printdebug( "executing command: '%s'\n", cmd.c_str() );
		  opts->cmdmap[cmd];
	      }
	  } catch (std::string error) {
	      if (error=="quit" || error=="exit")
		  throw error;
	      output->printf("error: `%s'\n",error.c_str());
	  } 
      }
}
