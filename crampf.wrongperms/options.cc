/*
 * Config Class -- reads and holds gobal config data
 */

#include <string.h>
#include <getopt.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "config.hh"
#include "interface.hh"
#include <errno.h>

Config::Config(int argc, char** argv)
{
  printf("geht ab, ey!\n");
  initdefaults(&opts);
  getopts(argc, argv);
  readPositiveFilter(opts.positiveFilterFiles);
  readNegativeFilter(opts.negativeFilterFiles);
}

Config::initdefaults(struct options* op)
{
  op->randomOrder=true;
  op->readconfig=true;
  op->loop=0;
  op->playercmd="amp";
  op->playercmd_args="-q";
  op->keys['h']=&Interface::help;
  op->keys['q']=&Interface::quit;
}

Config::getopts(int argc, char** argv)
{
  int option_index = 0;
  int c;
  struct options cmdopts;
  bool cmdrandom=false;         // set true if options specified
  bool cmdloop=false;
  while (1) {
    static struct option krampf_options[] =
    {
      {"playlist"        , 1, 0, 'p'},  // -p | --playlist <playlistfile>
      {"no-random"       , 0, 0, 'r'},  // -r | --no-random
      {"random"          , 0, 0, 'R'},  // -R | --random
      {"loop"            , 2, 0, 'l'},  // -l | --loop [times]
      {"negative-filter" , 1, 0, 'f'},  // -f | --negative-filter <filterfile>
      {"positive-filter" , 1, 0, 'F'},  // -F | --positive-filter <filterfile>
      {"player"          , 1, 0, 'P'},  // -P | --player <playercmd>
      {"player-args"     , 1, 0, 'a'},  // -s | --player-args <player-arguments>
      {"config-file"     , 1, 0, 'c'},  // -c | --config-file <cfgfile>
      {"ignore-config"   , 0, 0, 'i'},  // -i | --ignore-config
      {"help"            , 0, 0, 'h'},  // -h | --help
      {0, 0, 0, 0}  // NULL marks end
    };
    c = getopt_long(argc, argv, "p:rRl::f:F:P:a:c:ih",
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
      case 'P':
        cmdopts.playercmd = optarg;
        break;
      case 'a':
        cmdopts.playercmd_args = atoi(optarg);
        break;
      case 'c':
        cmdopts.configfile = optarg;
        break;
      case 'i':
        cmdopts.readconfig = false;
        break;
      case 'h':
        printf("      crampf developers version\n");
        printf("---------------------------------------\n");
        printf("[ -p | --playlist <playlist>          ]\n");
        printf("[ -r | --random                       ]\n");
        printf("[ -R | --no-random                    ]\n");
        printf("[ -l | --loop [times]                 ]\n");
        printf("[ -f | --negative-filter <filterfile> ]\n");
        printf("[ -F | --positive-filter <filterfile> ]\n");
        printf("[ -P | --player <playercmd>           ]\n");
        printf("[ -a | --player-args <player-args>    ]\n");
        printf("[ -c | --config-file <configfile>     ]\n");
        printf("[ -i | --ignore-config                ]\n");
        printf("[ -h | --help                         ]\n");
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
        readconfig(cmdopts.configfile)==-1;
      } catch (char* e) {
        fprintf(stderr,"config-error: %s\n", e);
      }
    } else { // using default
      try {
        readconfig("~/.crampfrc");
      } catch (char* e) {
       // fprintf(stderr,"config-error: %s\n", e);
      }
    }
  }
  /* overwrite cmdline options over configoptions */
  for (vector<string>::iterator it = cmdopts.mp3SearchPaths.begin();
      it != cmdopts.mp3SearchPaths.end(); it++)
    opts.mp3SearchPaths.push_back(*it);
  for (vector<string>::iterator it = cmdopts.negativeFilterFiles.begin();
      it != cmdopts.negativeFilterFiles.end(); it++)
    opts.negativeFilterFiles.push_back(*it);
  for (vector<string>::iterator it = cmdopts.positiveFilterFiles.begin();
      it != cmdopts.positiveFilterFiles.end(); it++)
    opts.positiveFilterFiles.push_back(*it);
  if (cmdopts.playercmd!="") 
    opts.playercmd=cmdopts.playercmd;
  if (cmdopts.playercmd_args!="") 
    opts.playercmd_args=cmdopts.playercmd_args;
  if (cmdloop) 
    opts.loop=cmdopts.loop;
  if (cmdrandom)
    opts.randomOrder=cmdopts.randomOrder;
}

Config::readconfig(string filename) 
{
  if (filename[0]=='~') { // replace ~ with users home
    filename.erase(filename.begin());
    filename = getenv("HOME") + filename;
  }
  FILE* fp = fopen((const char*)filename.c_str(), "r");
  if (fp == NULL) {
    /* perror((const char*)filename.c_str()); */
    throw strerror(errno);
  }
  char line[FILELINEWIDTH];
  char option[FILELINEWIDTH];
  char value[FILELINEWIDTH];
  int pos;
  while (fgets(line,FILELINEWIDTH,fp)) {
    if (line[0]!='#' && line[0]!='\n') {
      option[0]='\0'; value[0]='\0';
      sscanf(line,"%[a-zA-Z]%*[= ]%s",option,value);
      string opt = option; string val = value;   
      if (opt == "playercmd") {
        printf("player: %s\n", value);
        opts.playercmd = value;
        continue;
      } 
      if (opt == "playercmd_args") {
        printf("playercmd_firstArgs: %s\n", value);
        opts.playercmd_args = value;
        continue;
      } 
      fprintf(stderr,"configfile: options unknown: %s\n",line);
    }
  }
  fclose(fp);
}

Config::readFilter(vector<string>* flt, string filename)
{
  FILE* fp = fopen((const char*)filename.c_str(),"r");
  if (fp==NULL) {
    perror((const char*)filename.c_str());
    throw string("cannot open filterfile");
  }
  char line[FILELINEWIDTH];
  while (fgets(line,FILELINEWIDTH,fp)) {
    if (line[0]!='#' && line[0]!='\n') {
      line[strlen(line)-1]='\0'; /* remove '\n' */
      flt->push_back(line);
    }
  }
  fclose(fp);
}

Config::readPositiveFilter(string filename)
{
  readFilter(&opts.positiveFilter, filename);
}

Config::readPositiveFilter(vector<string> filenames)
{
  for (vector<string>::iterator it = filenames.begin();
      it != filenames.end(); it++)
    readPositiveFilter(*it);
}

Config::readNegativeFilter(string filename)
{
  readFilter(&opts.negativeFilter, filename);
}

Config::readNegativeFilter(vector<string> filenames)
{
  for (vector<string>::iterator it = filenames.begin();
      it != filenames.end(); it++)
    readNegativeFilter(*it);
}
  
struct options* 
Config::returnopts()
{
  return &opts;
}
