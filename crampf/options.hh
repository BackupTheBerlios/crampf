//
// $Id: options.hh,v 1.5 2000/03/10 18:28:35 logic Exp $
//

#ifndef config
#define config

#include <string>
#include <vector>
#include <map>
#include "interface.hh"

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
  /*
   * Als zweiten parameter fuer keys struct nehmen, der nicht nur
   * Funktionspointer, sondern auch einen Namen enthaelt
   * (um das Erstellen der Online-Hilfe zu erleichtern)
   */
  map<char, void(Interface::*)(void)> keys;
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

