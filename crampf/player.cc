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

Player::Player(string cmd, string args,Playlist* pl)
{
  playercmd = cmd;
  playercmd_args = args;
  plist = pl;
  signal(SIGCHLD,this->signalhandler);
}

Player::play()
{
  printf("start playing $%s$\n",(const char*)(*(*plist)).c_str());
  stop();
  pid=fork();
  if (pid==-1) {
    perror("fork");
    throw string("cannot fork");
  }
  if (pid!=0) {
    /* child starts playing */
    exit(1);
    extern char** environ;
    if (execle((const char*)playercmd.c_str(), (const char*)playercmd_args.c_str(), (const char*)(*(*plist)).c_str(), environ)==-1) {
      printf("wir sinds nur\n");
      perror("exec");
      printf("%s\n",(const char*)playercmd.c_str());
      printf("%s\n",(const char*)playercmd_args.c_str());
      printf("%s\n", (const char*)(*(*plist)).c_str());
      exit(2);
    }
  } else {
    printf("DAD!\n");
    while (1)
      ;
  }
}

Player::pause()
{
  if (kill(0,pid)==0)
    kill(SIGSTOP,pid);
}

Player::cont()
{
  if (kill(0,pid)==0)
    kill(SIGCONT,pid);
}

Player::stop()
{
  if (kill(0,pid)==0) {
    kill(SIGTERM,pid);
  }
  while (kill(0,pid)==0) {
    /* player still running, shoot him */
    kill(SIGKILL,pid);
  }
}

Player::prev()
{
  --(*plist);
  play();
}

Player::next()
{
  ++(*plist);
  play();
}

void
Player::signalhandler(int status)
{
  printf("HAHAHAHAHA\n");
  wait(NULL);
}

