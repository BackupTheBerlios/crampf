#include "stdplayer.hh"
#include "../../debug.hh"
#include "../../config.h"
#include "autocmd.hh"
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

StdPlayer *StdPlayer::self = NULL;

void player_sig_playerstop( int status )
{
      if( StdPlayer::self )
	  StdPlayer::self->signalHandler( status );
}

StdPlayer::StdPlayer()
{
      self = this;
      pid = 99999999;
      sigignore = false;
      newsong = false;
      first_track_damaged = false;
      has_finished = false;
      signal(SIGCHLD,player_sig_playerstop);
}

StdPlayer::~StdPlayer()
{
}

void
StdPlayer::play()
{
  printdebug( "starting player\n" );
  stop();
  if (first_track_damaged) {
    --(*plist);
    first_track_damaged = false;
  }
  pid=fork();
  if (pid==-1) {
    perror("fork");
    exit(1);
  }
  struct stat buf;
  if (stat((const char*)(*(*plist)).filename().c_str(),&buf)==-1) {
    if (pid == 0) {
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
  if (pid==0) {
      fclose(stdin);
      fclose(stdout);
      if( strcmp( PLAYER_CMD , "madplay" ) == 0
	      || strcmp( PLAYER_CMD, "mpg321" ) == 0
	      || strcmp( PLAYER_CMD, "amp" ) == 0
	      || strcmp( PLAYER_CMD, "alsaplayer" ) == 0)
	  fclose(stderr); /* TODO how to redirect stderr to /dev/null? */
      vector<string> args;
      int p=0;
      for (unsigned int i=opts->playercmd_args.find(" ",p); 
	      i < opts->playercmd_args.length(); 
	      p=++i, i=opts->playercmd_args.find(" ",p)) 
	  args.push_back( opts->playercmd_args.substr( p, i-p ) );
      args.push_back( opts->playercmd_args.substr( p ) );
      char *argv[ args.size() + 3 ];
      argv[0] = (char*)opts->playercmd.c_str();
      p=1;
      for (vector<string>::const_iterator it = args.begin();
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
  newsong = true;
}

void
StdPlayer::stop()
{
  printdebug( "stopping player\n" );
  sigignore = true;
  //printf("stopping pid %d\n",pid);
  if (isRunning()) {
    kill(pid,SIGTERM);
    sleep(1); /* wait for sigchld */
    while (isRunning()) {
      kill(pid,SIGKILL);
      sleep(1); /* wait for sigchld */
    }
    int pid = fork();
    if (pid==0) {
      fclose(stdin);
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
  sigignore = false;
}

void
StdPlayer::pause()
{
  if (isRunning())
    kill(pid,SIGSTOP);
}

void
StdPlayer::cont()
{
  if (isRunning())
    kill(pid,SIGCONT);
}

bool
StdPlayer::isRunning()
{
  if (kill(pid,0)==0)
    return true;
  else
    return false;
}

bool
StdPlayer::restarted()
{
  if (newsong) {
    newsong = false;
    return true;
  } else
    return false;
}

bool
StdPlayer::finished()
{
  return has_finished;
}

void
StdPlayer::signalHandler( int status )
{
  printdebug("got signaled: signal=%d\n",status);
  if (status!=SIGCHLD) 
    return;
  status = waitpid(-1,NULL,WNOHANG);
  printdebug("got signaled by %d\n",status);
  if (status==0)
    return;  /* no dead child */
  if (status != pid)
    return;
  if (sigignore)
    return;
  try {
    printdebug("sending 'next' event\n"); //++(*plist);
    autocmdmap["next"].trigger();
  } catch( string error )
  {
    printf( "%s\n", error.c_str() );
    has_finished = true;
    return;
  }
}
