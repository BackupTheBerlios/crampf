/*
 * player.cc -- Controls the mp3player itself
 */

#include <string>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include "player.hh"
#include "playlist.hh"

int player_pid = 999999; /* hope this pid never exists ;] */
bool player_sigignore;
bool player_newsong;
bool first_track_damaged;

void player_init()
{
  player_sigignore = false;
  player_newsong = false;
  first_track_damaged = false;
  signal(SIGCHLD,player_playerstop);
}

void player_play( void )
{
  player_stop();
  if (first_track_damaged) {
    --(*plist);
    first_track_damaged = false;
  }
  player_pid=fork();
  if (player_pid==-1) {
    perror("fork");
    exit(1);
  }
  struct stat buf;
  if (stat((const char*)(*(*plist)).filename().c_str(),&buf)==-1) {
    if (player_pid == 0) {
      perror((const char*)(*(*plist)).filename().c_str());
    } else {
      plist->erase(&(*plist)[plist->pos()]);
      try {
        --(*plist);
      } catch (string e) {
        first_track_damaged = true;
      }
      return;
    }
  } 
  if (player_pid==0) {
    /*  printf("execlp(%s, %s, %s)\n",(const char*)opts->playercmd.c_str(), 
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
  player_newsong = true;
}

void player_stop( void )
{
  player_sigignore = true;
  //printf("stopping pid %d\n",player_pid);
  if (player_isrunning()) {
    kill(player_pid,SIGTERM);
    sleep(1);
    while (player_isrunning()) {
      kill(player_pid,SIGKILL);
    }
    int pid = fork();
    if (pid==0) {
      execlp("fuser","fuser","-k","/dev/dsp",NULL);
      perror("execlp(fuser)");
      exit(1);
    } 
  }
  int f;
  while ((f=open("/dev/dsp",O_WRONLY))==-1);
  close(f);
  player_sigignore = false;
}

void player_playerstop(int status)
{
  if (status!=SIGCHLD)
    return;
  status = wait(NULL);
  //printf("got signaled by %d\n",status);
  if (status != player_pid)
    return;
  if (player_sigignore)
    return;
  //printf("starting next song\n");
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

bool player_restarted( void )
{
  if (player_newsong) {
    player_newsong = false;
    return true;
  } else
    return false;
}
