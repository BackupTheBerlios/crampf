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
#include "debug.hh"
#include "autocmd.hh"

int player_pid = 999999; /* hope this pid never exists ;] */
bool player_sigignore;
bool player_newsong;
bool first_track_damaged;
bool player_has_finished;

void player_init()
{
  player_sigignore = false;
  player_newsong = false;
  first_track_damaged = false;
  player_has_finished = false;
  signal(SIGCHLD,player_playerstop);
}

void player_play( void )
{
  printdebug( "starting player\n" );
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
      vector<string> args;
      int p=0;
      for (int i=opts->playercmd_args.find(" ",p); 
	      i < opts->playercmd_args.length(); 
	      p=++i, i=opts->playercmd_args.find(" ",p)) 
	  args.push_back( opts->playercmd_args.substr( p, i-p ) );
      args.push_back( opts->playercmd_args.substr( p ) );
      char *argv[ args.size() + 3 ];
      argv[0] = (char*)opts->playercmd.c_str();
      p=1;
      for (vector<string>::iterator it = args.begin();
	      it != args.end(); it++)
	  argv[p++] = (char*)(it->c_str());
      argv[p++] = (char*)(*(*plist)).filename().c_str();
      argv[p] = NULL;
#ifdef DEBUG
      printdebug("execvp( %s, [", (const char*)opts->playercmd.c_str());
      for (int i=0; i<p; i++) {
	  printf("%s, ", argv[i]);
      }
      printf(", NULL] )\n");
#endif
      execvp( (const char*)opts->playercmd.c_str(), argv );
      perror("execvp");
      exit(2);
  } 
  player_newsong = true;
}

void player_stop( void )
{
  printdebug( "stopping player\n" );
  player_sigignore = true;
  //printf("stopping pid %d\n",player_pid);
  if (player_isrunning()) {
    kill(player_pid,SIGTERM);
    sleep(1); /* wait for sigchld */
    while (player_isrunning()) {
      kill(player_pid,SIGKILL);
      sleep(1); /* wait for sigchld */
    }
    int pid = fork();
    if (pid==0) {
      fclose(stdout); /* Hardcore */
      fclose(stderr); /* even harder */
      execlp("fuser","fuser","-k","/dev/dsp",NULL);
      perror("execlp(fuser)");
      exit(1);
    } 
  }
  int f;
  while ((f=open("/dev/dsp",O_WRONLY))==-1);
  close(f);
  printdebug("waiting one second...\n");
  sleep(1); /* just to be sure... */
  player_sigignore = false;
}

void player_playerstop(int status)
{
  printdebug("got signaled: signal=%d\n",status);
  if (status!=SIGCHLD) 
    return;
  status = waitpid(-1,NULL,WNOHANG);
  printdebug("got signaled by %d\n",status);
  if (status==0)
    return;  /* no dead child */
  if (status != player_pid)
    return;
  if (player_sigignore)
    return;
  try {
    printdebug("sending 'next' event\n"); //++(*plist);
    autocmdmap["next"].trigger();
  } catch( string error )
  {
    printf( "%s\n", error.c_str() );
    player_has_finished = true;
    return;
  }
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

bool player_finished( void )
{
  return player_has_finished;
}
