//
// $Id: options.hh,v 1.2 2000/03/10 07:16:58 logic Exp $
//

#ifndef config
#define config

#include <string>
#include <vector>

#define FILELINEWIDTH 128    /* max config and filter file linewidth */

struct options {
  string                configfile;
  bool                  readconfig;
  vector<string>        playlistfiles;
  bool                  randomOrder;
  int                   loop;
  vector<string>        negativeFilterFiles;
  vector<string>        negativeFilter;
  vector<string>        positiveFilterFiles;
  vector<string>        positiveFilter;
  string                playercmd;
  string                playercmd_args;
  vector<string>        mp3SearchPaths;
  struct keys {
    string      next;
    string      prev;
    string      pause;
    string      cont;
    string      info;
    string      list;
    string      help;
    string      quit;
    string      vol0;
    string      vol1;
    string      vol2;
    string      vol3;
    string      vol4;
    string      vol5;
    string      vol6;
    string      vol7;
    string      vol8;
    string      vol9;
    string      vol_up;
    string      vol_down;
  } key;
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

