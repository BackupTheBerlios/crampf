//
// $Id: options.hh,v 1.24 2003/01/05 12:39:24 logic Exp $
//

#ifndef OPTIONS_HH
#define OPTIONS_HH OPTIONS_HH

#include <string>
#include <vector>
#include <map>
#include "interface.hh"
#include "commandmap.hh"

#define FILELINEWIDTH 128    /* max config and filter file linewidth */

struct Options {
  std::string              configfile;
  bool                     readconfig;
  std::vector<std::string> playlistfiles;
  bool                     randomOrder;
  bool                     generateTitles;
  int                      loop;
  unsigned int             titlewidth;
  unsigned int             volume;
  int                      regexp;	/* regexp level (0=no, 1=std, 2=extended)*/
  bool                     casesensivity;
  char                     soundcard; /* s = UltraSound, w = SB-Clone */
  std::vector<std::string> negativeFilterFiles;
  std::vector<std::string> negativeFilter;
  std::vector<std::string> positiveFilterFiles;
  std::vector<std::string> positiveFilter;
  std::vector<std::string> mp3SearchPaths;
  CommandMap               cmdmap;
};

class Config {
  public:
    struct Options* returnopts();
    void configure(int argc, char** argv);
  private:
    void getopts(int argc, char** argv);
    /* Achtung: Eventuell noch '\n' beim parsen beachten! */
    void readconfig( std::string filename );
    void initdefaults(struct Options* op);
  
    struct Options opts;
};

extern struct Options* opts;

#endif

