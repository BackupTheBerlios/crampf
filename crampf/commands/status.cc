/*
 * Here are all commands defined
 */


#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../commandmap.hh"
#include "../player.hh"
#include "../playlist.hh"
#include "status.hh"

extern Playlist* plist;

void
Status::doit( string s )
{
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
}

void
Status::help( string s )
{
  printf("shows track number and title\n");
}
