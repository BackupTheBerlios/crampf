/*
 * Here are all commands defined
 */


#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../playlist.hh"
#include "../options.hh"
#include "status.hh"
#include "../iosubsys/output.hh"

void
Status::doit( const std::string &s )
{
      if( plist->size() <= plist->pos() )
	  plist->jump( plist->pos() );
      if ((*plist).size() > 0) {
	  if (opts->titlewidth==0) {
	      output->printf("\n[%d/%d] - %s\n",plist->pos()+1,plist->size(),
		      (*(*plist)).title().c_str());
	  } else {
#define MAXTITLEWIDTH 1024
	      char title[MAXTITLEWIDTH];
	      sprintf(title,"\n[%d/%d] - %s\n",plist->pos()+1,plist->size(),
		      (*(*plist)).title().c_str());
	      if (strlen(title)>opts->titlewidth) {
		  unsigned int i;
		  for (i=0; i<opts->titlewidth/3; i++)
		      output->printf("%c",title[i]);
		  output->printf("...");
		  i=strlen(title)-i*2-1;
		  for (;i<strlen(title);i++)
		      output->printf("%c",title[i]);
	      } else 
		  output->printf("%s",title);
	  }
      } else 
	  output->printf("playlist empty\n");
}

void
Status::help( const std::string &s ) const
{
  output->printf("format: status\n");
  output->printf("description: shows track number and title\n");
  output->printf("see also: filename, titlewidth, info\n");
}

void 
Status::description() const
{
  output->printf("shows track number and title\n");
}
