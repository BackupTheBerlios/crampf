/*
 * Config Class -- reads and holds gobal config data
 */

#include <string.h>
#include <getopt.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include "config.hh"
#include "config.h"
#include "interface.hh"
#include <errno.h>

void
Config::configure(int argc, char** argv)
{
  initdefaults(&opts);
  getopts(argc, argv);
}

void Config::initdefaults(struct options* op)
{
  op->randomOrder=true;
  op->readconfig=true;
  op->generateTitles=true;
  op->soundcard='w';
  op->loop=0;
  op->casesensivity=true;
  op->regexp=0;
  op->titlewidth=0;
  try {
    op->cmdmap["map h map"];
    op->cmdmap["define next=jump +1"];
    op->cmdmap["define prev=jump -1"];
    op->cmdmap["map n next"];
    op->cmdmap["map p prev"];
    op->cmdmap["map i info"];
    op->cmdmap["map q quit"];
    op->cmdmap["map s status"];
    op->cmdmap["map + vol +5"];
    op->cmdmap["map - vol -5"];
    op->cmdmap["map 1 vol 10"];
    op->cmdmap["map 2 vol 20"];
    op->cmdmap["map 3 vol 30"];
    op->cmdmap["map 4 vol 40"];
    op->cmdmap["map 5 vol 50"];
    op->cmdmap["map 6 vol 60"];
    op->cmdmap["map 7 vol 70"];
    op->cmdmap["map 8 vol 80"];
    op->cmdmap["map 9 vol 90"];
    op->cmdmap["map 0 vol 00"];
    op->cmdmap["map f filename"];
    op->cmdmap["map \040 next"];
  } catch (std::string error) {
    printf("keytable init error: `%s'\n",error.c_str());
  }
}

void Config::getopts(int argc, char** argv)
{
  int option_index = 0;
  int c;
  struct options cmdopts;
  cmdopts.readconfig = true;
  bool cmdrandom=false;         // set true if options specified
  bool cmdloop=false;
  bool cmdgenerateTitles=false;
  bool cmdtitlewidth = false;
  while (1) {
    static struct option krampf_options[] =
    {
      {"playlist"            , 1, 0, 'p'},
      {"no-random"           , 0, 0, 'r'},
      {"random"              , 0, 0, 'R'},
      {"loop"                , 2, 0, 'l'},
      {"negative-filter"     , 1, 0, 'f'},
      {"positive-filter"     , 1, 0, 'F'},
      {"config-file"         , 1, 0, 'c'},
      {"ignore-config"       , 0, 0, 'i'},
      {"generate-titles"     , 0, 0, 'g'},
      {"dont-generate-titles", 0, 0, 'G'},
      {"title-width"         , 1, 0, 't'},
      {"help"                , 0, 0, 'h'},
      {"version"             , 0, 0, 'v'},
      {0, 0, 0, 0}  // NULL marks end
    };
    c = getopt_long(argc, argv, "p:rRl::f:F:P:a:c:t:ihvgG",
        krampf_options, &option_index);
    if (c==EOF)
      break;
    switch (c) {
      case 'p':
        cmdopts.playlistfiles.push_back(optarg);
        break;
      case 'r':
        cmdopts.randomOrder = 1;
        cmdrandom=true;
        break;
      case 'R':
        cmdopts.randomOrder = 0;
        cmdrandom=true;
        break;
      case 'l':
        cmdopts.loop = -1;     // -1 means endless
        if (optarg) {
          cmdopts.loop = atoi(optarg);
        }
        cmdloop=true;
        break;
      case 'f':
        cmdopts.negativeFilterFiles.push_back(optarg);
        break;
      case 'F':
        cmdopts.positiveFilterFiles.push_back(optarg);
        break;
      case 'c':
        cmdopts.configfile = optarg;
        cmdopts.readconfig = true;
        break;
      case 'i':
        cmdopts.readconfig = false;
        break;
      case 'g':
        cmdopts.generateTitles = true;
        cmdgenerateTitles = true;
        break;
      case 'G':
        cmdopts.generateTitles = false;
        cmdgenerateTitles = true;
        break;
      case 't':
        cmdopts.titlewidth = atoi(optarg);
        cmdtitlewidth = true;
        break;
      case 'h':
        printf("    crampf %s\n", VERSION);
        printf("---------------------------------------\n");
        printf("[ -p | --playlist <playlist>          ]\n");
        printf("[ -r | --random                       ]\n");
        printf("[ -R | --no-random                    ]\n");
        printf("[ -l | --loop [times]                 ]\n");
        printf("[ -f | --negative-filter <filterfile> ]\n");
        printf("[ -F | --positive-filter <filterfile> ]\n");
        printf("[ -c | --config-file <configfile>     ]\n");
        printf("[ -i | --ignore-config                ]\n");
        printf("[ -g | --generate-titles              ]\n");
        printf("[ -G | --dont-generate-titles         ]\n");
        printf("[ -t | --title-width <title-width>    ]\n");
        printf("[ -h | --help                         ]\n");
        printf("[ -v | --version                      ]\n");
        exit(0);
      case 'v':
        printf("crampf %s\n", VERSION);
        exit(0);
      case '?':
        // missing parameter (getopts generates the output)
        break;
      case ':':
        fprintf(stderr , "missing parameter for %s\n", argv[optind]);
        break;
      default:
        fprintf(stderr , "error reading parameter (0%o)\n", c);
    }
  }
  if (optind < argc) {
    while (optind < argc) {
      cmdopts.mp3SearchPaths.push_back(argv[optind++]);
    }
  }
  /* do we have to read a config file? */
  if (cmdopts.readconfig) {
    if (!cmdopts.configfile.empty()) {
      try {
        readconfig(cmdopts.configfile);
      } catch (std::string error) {
        fprintf(stderr,"config-error: %s\n", error.c_str());
      }
    } else { // using default
      try {
        readconfig("~/.crampfrc");
      } catch (std::string error) {
        fprintf(stderr,"config-error: %s\n", error.c_str());
      }
    }
  }
  /* overwrite cmdline options over configoptions */
  for (std::vector<std::string>::const_iterator it = cmdopts.mp3SearchPaths.begin();
      it != cmdopts.mp3SearchPaths.end(); it++)
    opts.mp3SearchPaths.push_back(*it);
  for (std::vector<std::string>::const_iterator it = cmdopts.negativeFilterFiles.begin();
      it != cmdopts.negativeFilterFiles.end(); it++)
    opts.negativeFilterFiles.push_back(*it);
  for (std::vector<std::string>::const_iterator it = cmdopts.positiveFilterFiles.begin();
      it != cmdopts.positiveFilterFiles.end(); it++)
    opts.positiveFilterFiles.push_back(*it);
  for (std::vector<std::string>::const_iterator it = cmdopts.playlistfiles.begin();
      it != cmdopts.playlistfiles.end(); it++)
    opts.playlistfiles.push_back(*it);
  if (cmdloop) 
    opts.loop=cmdopts.loop;
  if (cmdrandom)
    opts.randomOrder=cmdopts.randomOrder;
  if (cmdgenerateTitles)
    opts.generateTitles=cmdopts.generateTitles;
  if (cmdtitlewidth)
    opts.titlewidth=cmdopts.titlewidth;
}

void Config::readconfig( std::string filename ) 
{
  filename = "source " + filename;
  opts.cmdmap[filename];
  /*
  if (filename[0]=='~') { // replace ~ with users home
    filename.erase(filename.begin());
    filename = getenv("HOME") + filename;
  }
  FILE* fp = fopen((const char*)filename.c_str(), "r");
  if (fp == NULL) {
    //perror((const char*)filename.c_str()); 
    throw strerror(errno);
  }
  char line[FILELINEWIDTH];
  char option[FILELINEWIDTH];
  char value[FILELINEWIDTH];
  int pos;
  while (fgets(line,FILELINEWIDTH,fp)) {
    if (line[0]!='#' && line[0]!='\n') {
      option[0]='\0'; value[0]='\0';
      sscanf(line,"%[a-zA-Z_]%*[=\t ]%[^\n]\n",option,value);
      string opt = option; string val = value;   
      if (opt == "playercmd") {
        opts.playercmd = value;
        continue;
      } 
      if (opt == "playercmd_args") {
        opts.playercmd_args = value;
        continue;
      } 
      if (opt == "random") {
        if (value[0]=='y' || value[0]=='Y') {
          opts.randomOrder = true;
        } else if (value[0]=='n' || value[0]=='N') {
          opts.randomOrder = false;
        } else {
          fprintf(stderr,"unknown option `random %s'\n",value);
        }
        continue;
      }
      if (opt == "loop") {
        if (value[0]=='y' || value[0]=='Y') {
          opts.loop = -1;
        } else if (value[0]=='n' || value[0]=='N') {
          opts.loop = 1;
        } else {
          opts.loop = atoi(value);
        }
        continue;
      }
      if (opt == "titlewidth") {
        opts.titlewidth = atoi(value);
        continue;
      }
      if (opt == "generateTitles") {
        if (value[0]=='y' || value[0]=='Y') {
          opts.generateTitles=true;
        } else {
          opts.generateTitles=false;
        }
      }
      fprintf(stderr,"configfile: unknown option: %s\n",line);
    }
  }
  fclose(fp);
  */
}

struct options* 
Config::returnopts()
{
  return &opts;
}
