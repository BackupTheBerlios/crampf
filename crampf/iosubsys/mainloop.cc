#include "mainloop.hh"
#include "input.hh"
#include "output.hh"
#include "../options.hh"
#include <unistd.h>

void mainloop()
{
      while(1){
	  output->flush();
	  usleep(100);
	  std::string cmd = input->read();
	  try {
	      if( cmd.size() == 1 )
		  opts->cmdmap[cmd[0]];
	      else if( cmd.size() > 1 )
		  opts->cmdmap[cmd];
	  } catch (std::string error) {
	      if (error=="quit" || error=="exit")
		  throw error;
	      output->printf("error: `%s'\n",error.c_str());
	  } 
      }
}
