/*
 * Here are all commands defined
 */


#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../playlist.hh"
#include "../config.hh"
#include "status.hh"

extern Playlist* plist;
extern struct options* opts;

void
Status::doit( const string &s )
{
      if( plist->size() <= plist->pos() )
	  plist->jump( plist->pos() );
      if ((*plist).size() > 0) {
	  if (opts->titlewidth==0) {
	      printf("\n[%d/%d] - %s\n",plist->pos()+1,plist->size(),
		      (*(*plist)).title().c_str());
	  } else {
#define MAXTITLEWIDTH 1024
	      char title[MAXTITLEWIDTH];
	      sprintf(title,"\n[%d/%d] - %s\n",plist->pos()+1,plist->size(),
		      (*(*plist)).title().c_str());
	      if (strlen(title)>opts->titlewidth) {
		  int i;
		  for (i=0; i<opts->titlewidth/3; i++)
		      printf("%c",title[i]);
		  printf("...");
		  i=strlen(title)-i*2-1;
		  for (;i<strlen(title);i++)
		      printf("%c",title[i]);
	      } else 
		  printf("%s",title);
	  }
      } else 
	  printf("playlist empty\n");
}

void
Status::help( const string &s ) const
{
  printf("format: status\n");
  printf("description: shows track number and title\n");
  printf("see also: filename, titlewidth, info\n");
}

void 
Status::description() const
{
  printf("shows track number and title\n");
}
