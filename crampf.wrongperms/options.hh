//
// $Id: options.hh,v 1.19 2002/07/01 19:01:47 logic Exp $
//

#ifndef CONFIG_HH
#define CONFIG_HH CONFIG_HH

#include <string>
#include <vector>
#include <map>
#include "interface.hh"
#include "commandmap.hh"

#define FILELINEWIDTH 128    /* max config and filter file linewidth */

struct options {
  string                configfile;
  bool                  readconfig;
  vector<string>        playlistfiles;
  bool                  randomOrder;
  bool                  generateTitles;
  int                   loop;
  int                   titlewidth;
  int                   volume;
  int			regexp;	/* regexp level (0=no, 1=std, 2=extended)*/
  bool			casesensivity;
  char                  soundcard; /* s = UltraSound, w = SB-Clone */
  vector<string>        negativeFilterFiles;
  vector<string>        negativeFilter;
  vector<string>        positiveFilterFiles;
  vector<string>        positiveFilter;
  string                playercmd;
  string                playercmd_args;
  vector<string>        mp3SearchPaths;
  CommandMap            cmdmap;
};

class Config {
  public:
    struct options* returnopts();
    void configure(int argc, char** argv);
  private:
    void getopts(int argc, char** argv);
    /* Achtung: Eventuell noch '\n' beim parsen beachten! */
    void readconfig( string filename );
    void initdefaults(struct options* op);
  
    struct options opts;
};

#endif

