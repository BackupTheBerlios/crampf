//
// $Id: options.hh,v 1.12 2000/03/18 04:38:09 logic Exp $
//

#ifndef config
#define config

#include "version_info.hh"
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
    Config(int argc, char** argv);
    readPositiveFilter(string filename);
    readPositiveFilter(vector<string> filenames);
    readNegativeFilter(string filename);
    readNegativeFilter(vector<string> filenames);
    struct options* returnopts();
  private:
    getopts(int argc, char** argv);
    /* Achtung: Eventuell noch '\n' beim parsen beachten! */
    readconfig(string filename);
    initdefaults(struct options* op);
    readFilter(vector<string>* flt, string filename);
  
    struct options opts;
};

#endif

