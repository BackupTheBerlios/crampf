/*
 * Standard textmode interface
 */

#include "version_info.hh"
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
#include "player.hh"
#include "config.hh"
#include "readlineinterface.hh"

Interface::Interface( void )
{
  printf("welcome to the crampf %s (%s)\n", VERSION, RELEASENAME);
  detectSoundCard();
  opts->volume = getVolume();
  /* save terminal settings */
  if (tcgetattr(1,&terminal_settings)==-1) {
    perror("tcgetattr");
  }
  singlekeyTerm();
  mainloop();
}
  
Interface::~Interface()
{
  restoreTerm();
  printf("Thank you for using crampf!\n");
}

Interface::mainloop()
{
      player_init();
      player_play();
      try {
	  char c;
	  while (!player_finished()) {
	      if (player_restarted()) {
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
			  } catch (string error) {
			      if (error=="quit" || error=="exit")
				  throw error;
			      printf("error: `%s'\n",error.c_str());
			  } 
		  } 
	      } 
	  }
      } catch (string error) {
	  if (error!="quit" && error!="exit")
	      printf("error: `%s'\n",error.c_str());
	  if (error!="exit")
	      player_stop();
      }
}

void
Interface::singlekeyTerm() 
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
Interface::restoreTerm()
{
  if (tcsetattr(1,TCSANOW,&terminal_settings)==-1) {
    perror("tcsettatr");
  }
}

void
Interface::use_rli( void )
{
  restoreTerm();
  rli.input();
  singlekeyTerm();
}

void
Interface::use_search_rli( string s )
{
  restoreTerm();
  search_rli.input(s);
  singlekeyTerm();
}

Interface::detectSoundCard()
{
  opts->soundcard='w'; /* default */
  FILE* fp = fopen("/dev/sndstat","r");
  if (fp==NULL) {
    perror("sndstat");
    return -1;
  }
#define LINEWIDTH 128
  char line[LINEWIDTH];
  string l;
  while (fgets(line,LINEWIDTH,fp)) {
    l=line;
    if (l.find("UltraSound")!=-1)
      opts->soundcard='s';
  }
  fclose(fp);
}

int
Interface::getVolume()
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

