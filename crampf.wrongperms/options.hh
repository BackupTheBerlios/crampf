//
// $Id: options.hh,v 1.16 2000/12/09 15:52:30 logic Exp $
//

#ifndef CONFIG
#define CONFIG CONFIG

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
    void readPositiveFilter(string filename);
    void readPositiveFilter(vector<string> filenames);
    void readNegativeFilter(string filename);
    void readNegativeFilter(vector<string> filenames);
    struct options* returnopts();
    void configure(int argc, char** argv);
  private:
    void getopts(int argc, char** argv);
    /* Achtung: Eventuell noch '\n' beim parsen beachten! */
    void readconfig(string filename);
    void initdefaults(struct options* op);
    void readFilter(vector<string>* flt, string filename);
  
    struct options opts;
};

#endif

