/*
 * player.cc -- Controls the mp3player itself
 */

#include <string>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include "player.hh"
#include "playlist.hh"

int player_pid = 999999; /* hope this pid never exists ;] */

void player_init()
{
  signal(SIGCHLD,player_playerstop);
}

void player_play( void )
{
  player_stop();
  player_pid=fork();
  if (player_pid==-1) {
    perror("fork");
    exit(1);
  }
  if (player_pid==0) {
    /* printf("execlp(%s, %s, %s)\n",(const char*)opts->playercmd.c_str(), 
          (const char*)opts->playercmd_args.c_str(), 
          (const char*)(*(*plist)).filename().c_str()); */
    execlp((const char*)opts->playercmd.c_str(),
        (const char*)opts->playercmd.c_str(),
        (const char*)opts->playercmd_args.c_str(), 
        (const char*)(*(*plist)).filename().c_str(),
        NULL);
    perror("execlp");
    exit(2);
  }
  printf("new playerprocess %d\n",player_pid);
}

void player_stop( void )
{
  printf("stopping pid %d\n",player_pid);
  if (player_isrunning()) {
    kill(player_pid,SIGTERM);
    sleep(1);
    while (player_isrunning()) {
      kill(player_pid,SIGKILL);
    }
  }
}

void player_playerstop(int status)
{
  if (status!=SIGCHLD)
    return;
  status = wait(NULL);
  printf("got signaled: %d\n",status);
  if (status != player_pid)
    return;
  printf("starting next song\n");
  ++(*plist);
  player_play();
}

void player_pause()
{
  if (player_isrunning())
    kill(player_pid,SIGSTOP);
}

void player_continue()
{
  if (player_isrunning())
    kill(player_pid,SIGCONT);
}

bool player_isrunning( void )
{
  if (kill(player_pid,0)==0)
    return true;
  else
    return false;
}
