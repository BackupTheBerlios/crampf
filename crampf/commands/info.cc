/*
 * Here are all commands defined
 */


#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../playlist.hh"
#include "info.hh"

extern Playlist* plist;

void
Info::doit( const string &s )
{
  int pid;
  pid = fork();
  if (pid==0) {
    execlp("mp3info","mp3info",(*(*plist)).filename().c_str(),"-F 2",NULL);
    perror("execlp(mp3info)");
    exit(1);
  }
}

void
Info::help( const string &s ) const
{
  printf("format: info\n");
  printf("description: shows information on current title\n");
  printf("see also: status, filename\n");
}

void 
Info::description() const
{
  printf("shows information on current title\n");
}
