/*
 * Standard textmode interface
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string>
#include <map>
#include "interface.hh"
#include "options.hh"
#include "debug.hh"
#include "config.h"
#include "readlineinterface.hh"
#include "player/player-interface.hh"

extern PlayerInterface *player;

Interface::Interface()
{
  printf("welcome to the crampf %s\n", VERSION );
  detectSoundCard();
  opts->volume = getVolume();
  /* save terminal settings */
  if (tcgetattr(1,&terminal_settings)==-1) {
    perror("tcgetattr");
  }
  singlekeyTerm();
}
  
Interface::~Interface()
{
  restoreTerm();
  printf("Thank you for using crampf!\n");
}

void Interface::mainloop()
{
      printdebug( "start playing %s\n", (**plist).filename().c_str() );
      player->play( (**plist).filename() );
      printdebug( "isPlaying %d\n", player->isPlaying() );
      try {
	  char c;
	  while (player->isPlaying()) {
	      usleep(100); /* FIXME remove */
	      c = fgetc(stdin); 
	      if (c!=EOF) {
		  switch (c) {
		      case ':':
			  use_rli();
			  break;
		      case '/':
		      case '?':
			  char xx[2];
			  xx[0]=c;
			  xx[1]='\0';
			  use_search_rli(xx);
			  break;
		      default:
			  try {
			      opts->cmdmap[c];
			  } catch (std::string error) {
			      if (error=="quit" || error=="exit")
				  throw error;
			      printf("error: `%s'\n",error.c_str());
			  } 
		  } 
	      } 
	  }
      } catch (std::string error) {
	  if (error!="quit" && error!="exit")
	      printf("error: `%s'\n",error.c_str());
	  if (error!="exit")
	      player->stop();
      }
}
#if 0
void Interface::mainloop()
{
      player->play( (**plist).filename() );
      try {
	  char c;
	  while (!player->finished()) {
	      if (player->restarted()) {
		  opts->cmdmap["status"];
	      }
	      usleep(100);
	      c = fgetc(stdin); 
	      if (c!=EOF) {
		  switch (c) {
		      case ':':
			  use_rli();
			  break;
		      case '/':
		      case '?':
			  char xx[2];
			  xx[0]=c;
			  xx[1]='\0';
			  use_search_rli(xx);
			  break;
		      default:
			  try {
			      opts->cmdmap[c];
			  } catch (std::string error) {
			      if (error=="quit" || error=="exit")
				  throw error;
			      printf("error: `%s'\n",error.c_str());
			  } 
		  } 
	      } 
	  }
      } catch (std::string error) {
	  if (error!="quit" && error!="exit")
	      printf("error: `%s'\n",error.c_str());
	  if (error!="exit")
	      player->stop();
      }
}
#endif

void
Interface::singlekeyTerm() const
{
  struct termios t;
  t = terminal_settings;
  t.c_lflag&=~(ICANON|ECHO);
  if (tcsetattr(1,TCSANOW,&t)==-1) {
    perror("tcsetattr");
  }
  if (fcntl(1,F_SETFL, O_NONBLOCK)==-1) {
    perror("fcntl");
  }
}

void
Interface::restoreTerm() const
{
  if (tcsetattr(1,TCSANOW,&terminal_settings)==-1) {
    perror("tcsettatr");
  }
}

void
Interface::use_rli()
{
  restoreTerm();
  rli.input();
  singlekeyTerm();
}

void
Interface::use_search_rli( const std::string &s )
{
  restoreTerm();
  search_rli.input(s);
  singlekeyTerm();
}

void Interface::detectSoundCard()
{
  opts->soundcard='w'; /* default */
  FILE* fp = fopen("/dev/sndstat","r");
  if (fp==NULL) {
    perror("sndstat");
    return;
  }
#define LINEWIDTH 128
  char line[LINEWIDTH];
  std::string l;
  while (fgets(line,LINEWIDTH,fp)) {
    l=line;
    if ((signed)(l.find("UltraSound"))!=-1)
      opts->soundcard='s';
  }
  fclose(fp);
}

int
Interface::getVolume() const
{
  FILE* fp = popen("aumix -q","r");
  char line[LINEWIDTH];
  char rs[5];
  char ls[5];
  int ri=40; /* default setting */
  int li=40;
  while (fgets(line,LINEWIDTH,fp)) {
    if (strncmp("synth",line,5)==0) {
      sscanf(line,"%*[a-z]%*[\t ]%[0-9]%*[, ]%[0-9]\n",ls,rs);
      ri=atoi(rs);
      li=atoi(ls);
    }
  }
  pclose(fp);
  return ((ri+li)/2);
}

