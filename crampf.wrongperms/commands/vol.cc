/*
 * Here are all commands defined
 */


#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../config.hh"
#include "vol.hh"

extern struct options* opts;

void
Vol::doit( string s )
{
  int value;
  if (s[0]=='+') {
    sscanf(s.c_str(),"+%d",&value);
    opts->volume+=value;
  } else if (s[0]=='-') {
    sscanf(s.c_str(),"-%d",&value);
    opts->volume-=value;
  } else {
    sscanf(s.c_str(),"%d",&value);
    opts->volume=value;
  }
  if (opts->volume<0)
    opts->volume=0;
  if (opts->volume>100)
    opts->volume=100;
  char arg[6];
  arg[0]='-';
  arg[1]=opts->soundcard;
  arg[2]=48+opts->volume%1000/100;
  arg[3]=48+opts->volume%100/10;
  arg[4]=48+opts->volume%10;
  arg[5]='\0';
  int pid = fork();
  if (pid==0) {
    execlp("aumix","aumix",arg,NULL);
    perror("execlp(aumix)");
    exit(1);
  } 
  // player will reap the child 
}

void
Vol::help( string s )
{
  printf("format: volume <value>\n");
  printf("description: changes volume to the value <value>\n");
  printf("if <value> is preceeded with a + ord - the change is\n");
  printf("done relative to the current volume\n");
}

