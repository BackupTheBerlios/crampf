/*
 * Here are all commands defined
 */


#include "../version_info.hh"
#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../playlist.hh"
#include "info.hh"

extern Playlist* plist;

void
Info::doit( string s )
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
Info::help( string s )
{
  printf("format: info\n");
  printf("description: shows information on current title\n");
}

