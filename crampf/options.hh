//
// $Id: options.hh,v 1.14 2000/07/03 02:02:29 logic Exp $
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
    readPositiveFilter(string filename);
    readPositiveFilter(vector<string> filenames);
    readNegativeFilter(string filename);
    readNegativeFilter(vector<string> filenames);
    struct options* returnopts();
    void configure(int argc, char** argv);
  private:
    getopts(int argc, char** argv);
    /* Achtung: Eventuell noch '\n' beim parsen beachten! */
    readconfig(string filename);
    initdefaults(struct options* op);
    readFilter(vector<string>* flt, string filename);
  
    struct options opts;
};

#endif

