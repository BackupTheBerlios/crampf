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
  if (player_pid!=0) {
    printf("execlp(%s, %s, %s)\n",(const char*)opts->playercmd.c_str(), 
          (const char*)opts->playercmd_args.c_str(), 
          (const char*)(*(*plist)).c_str());
    execlp((const char*)opts->playercmd.c_str(), 
        (const char*)opts->playercmd_args.c_str(), 
        (const char*)(*(*plist)).c_str());
    perror("execlp");
    exit(2);
  }
}

void player_stop( void )
{
  if (player_isrunning()) {
    kill(SIGTERM,player_pid);
    sleep(1);
    while (player_isrunning()) {
      kill(SIGKILL,player_pid);
    }
  }
}

void player_playerstop(int status)
{
  printf("got signaled: %d\n",status);
  wait(NULL);
  printf("starting next song\n");
  ++(*plist);
  player_play();
}

void player_pause()
{
  if (player_isrunning())
    kill(SIGSTOP,player_pid);
}

void player_continue()
{
  if (player_isrunning())
    kill(SIGCONT,player_pid);
}

bool player_isrunning( void )
{
  if (kill(0,player_pid)==0)
    return true;
  else
    return false;
}
