/*
 * Here are all commands defined
 */


#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../options.hh"
#include "../config.h"
#include "vol.hh"
#include "../iosubsys/output.hh"

void
Vol::doit( const std::string &s )
{
      int value;
      if (s.empty()) {
	  output->printf("volume: %d%%\n", sndcard.getVolume() );
      } else if (s[0]=='+') {
	  sscanf(s.c_str(),"+%d",&value);
	  sndcard.setVolume( sndcard.getVolume() + value );
      } else if (s[0]=='-') {
	  sscanf(s.c_str(),"-%d",&value);
	  sndcard.setVolume( sndcard.getVolume() - value );
      } else {
	  sscanf(s.c_str(),"%d",&value);
	  sndcard.setVolume( value );
      }
}

void
Vol::help( const std::string &s ) const
{
  output->printf("format: volume <value>\n");
  output->printf("description: changes volume to the value <value>\n");
  output->printf("if <value> is preceeded with a + ord - the change is\n");
  output->printf("done relative to the current volume\n");
}


void 
Vol::description() const
{
  output->printf("changes playback volume\n");
}

Soundcard::Soundcard()
{
      flag[STANDARD] = 'w';
      flag[ULTRASOUND] = 's';
      flag[MAX_TYPE] = '\0';
      /* TODO add HAVE_DEV_SNDSTAT */
      type = STANDARD;
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
	      type = ULTRASOUND;
      }
      fclose(fp);
}

int
Soundcard::getVolume()
{
      FILE* fp = popen("aumix -q","r");
      char line[LINEWIDTH];
      char rs[5];
      char ls[5];
      int ri=40; /* default setting */
      int li=40;
      while (fgets(line,LINEWIDTH,fp)) {
	  if (strncmp("synth",line,5)==0) {
	      /*
	      sscanf(line,"%*[a-z]%*[\t ]%[0-9]%*[, ]%[0-9]\n",ls,rs);
	      ri=atoi(rs);
	      li=atoi(ls);
	      */
	      sscanf( line, "%*[a-z]%*[\t ]%d%*[, ]%d\n", &ri, &li );
	  }
      }
      pclose(fp);
      return ((ri+li)/2);
}

void
Soundcard::setVolume( int vol )
{
      if( vol > 100 )
	  vol = 100;
      else if( vol < 0 )
	  vol = 0;

      char arg1[3] = { '-', flag[type], '\0' },
	   arg2[4] = { vol%1000/100+'0', vol%100/10+'0', vol%10+'0', '\0' };

      int pid = fork();
      if (pid==0) {
	  execlp("aumix","aumix",arg1,arg2,NULL);
	  perror("execlp(aumix)");
	  exit(1);
      } 
      // player will reap the child 
}
