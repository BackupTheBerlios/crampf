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
#include "interface.hh"
#include <errno.h>

Config::Config(int argc, char** argv)
{
  initdefaults(&opts);
  getopts(argc, argv);
  setupkeys();
  readPositiveFilter(opts.positiveFilterFiles);
  readNegativeFilter(opts.negativeFilterFiles);
}

Config::initdefaults(struct options* op)
{
  op->randomOrder=true;
  op->readconfig=true;
  op->generateTitles=true;
  op->soundcard='w';
  op->loop=0;
  op->titlewidth=0;
  op->playercmd="amp";
  op->playercmd_args="-q";
  op->keytable["help"]="h";
  op->keytable["quit"]="q";
  op->keytable["next"]="n";
  op->keytable["prev"]="p";
  op->keytable["info"]="i";
  op->keytable["list"]="l";
  op->keytable["file"]="f";
  op->keytable["jump"]="j";
  /*
  op->keytable["pause"]="P";
  op->keytable["cont"]="C";
  */
  op->keytable["vol0"]="0";
  op->keytable["vol1"]="1";
  op->keytable["vol2"]="2";
  op->keytable["vol3"]="3";
  op->keytable["vol4"]="4";
  op->keytable["vol5"]="5";
  op->keytable["vol6"]="6";
  op->keytable["vol7"]="7";
  op->keytable["vol8"]="8";
  op->keytable["vol9"]="9";
  op->keytable["vol_up"]="+";
  op->keytable["vol_dn"]="-";
  op->keytable["cli"]=":";
}

Config::setupkeys()
{
  struct options* op;
  op = &opts;
  for (map<string, string>::iterator it = opts.keytable.begin();
      it != opts.keytable.end(); it++) {
    if (it->first=="help") {
      for (int i=0; i<it->second.size(); i++) {
        opts.keys[it->second[i]]=&Interface::help;
      }
      continue;
    }
    if (it->first=="quit") {
      for (int i=0; i<it->second.size(); i++) {
        opts.keys[it->second[i]]=&Interface::quit;
      }
      continue;
    }
    if (it->first=="next") {
      for (int i=0; i<it->second.size(); i++) {
        opts.keys[it->second[i]]=&Interface::next;
      }
      continue;
    }
    if (it->first=="prev") {
      for (int i=0; i<it->second.size(); i++) {
        opts.keys[it->second[i]]=&Interface::prev;
      }
      continue;
    }
    if (it->first=="info") {
      for (int i=0; i<it->second.size(); i++) {
        opts.keys[it->second[i]]=&Interface::info;
      }
      continue;
    }
    if (it->first=="list") {
      for (int i=0; i<it->second.size(); i++) {
        opts.keys[it->second[i]]=&Interface::list;
      }
      continue;
    }
    if (it->first=="file") {
      for (int i=0; i<it->second.size(); i++) {
        opts.keys[it->second[i]]=&Interface::file;
      }
      continue;
    }
    if (it->first=="jump") {
      for (int i=0; i<it->second.size(); i++) {
        opts.keys[it->second[i]]=&Interface::list;
      }
      continue;
    }
    /*
    if (it->first=="pause") {
      for (int i=0; i<it->second.size(); i++) {
        opts.keys[it->second[i]]=&Interface::pause;
      }
      continue;
    }
    if (it->first=="cont") {
      for (int i=0; i<it->second.size(); i++) {
        opts.keys[it->second[i]]=&Interface::cont;
      }
      continue;
    }
    */
    if (it->first=="vol0") {
      for (int i=0; i<it->second.size(); i++) {
        opts.keys[it->second[i]]=&Interface::vol0;
      }
      continue;
    }
    if (it->first=="vol1") {
      for (int i=0; i<it->second.size(); i++) {
        opts.keys[it->second[i]]=&Interface::vol1;
      }
      continue;
    }
    if (it->first=="vol2") {
      for (int i=0; i<it->second.size(); i++) {
        opts.keys[it->second[i]]=&Interface::vol2;
      }
      continue;
    }
    if (it->first=="vol3") {
      for (int i=0; i<it->second.size(); i++) {
        opts.keys[it->second[i]]=&Interface::vol3;
      }
      continue;
    }
    if (it->first=="vol4") {
      for (int i=0; i<it->second.size(); i++) {
        opts.keys[it->second[i]]=&Interface::vol4;
      }
      continue;
    }
    if (it->first=="vol5") {
      for (int i=0; i<it->second.size(); i++) {
        opts.keys[it->second[i]]=&Interface::vol5;
      }
      continue;
    }
    if (it->first=="vol6") {
      for (int i=0; i<it->second.size(); i++) {
        opts.keys[it->second[i]]=&Interface::vol6;
      }
      continue;
    }
    if (it->first=="vol7") {
      for (int i=0; i<it->second.size(); i++) {
        opts.keys[it->second[i]]=&Interface::vol7;
      }
      continue;
    }
    if (it->first=="vol8") {
      for (int i=0; i<it->second.size(); i++) {
        opts.keys[it->second[i]]=&Interface::vol8;
      }
      continue;
    }
    if (it->first=="vol9") {
      for (int i=0; i<it->second.size(); i++) {
        opts.keys[it->second[i]]=&Interface::vol9;
      }
      continue;
    }
    if (it->first=="vol_up") {
      for (int i=0; i<it->second.size(); i++) {
        opts.keys[it->second[i]]=&Interface::vol_up;
      }
      continue;
    }
    if (it->first=="vol_dn") {
      for (int i=0; i<it->second.size(); i++) {
        opts.keys[it->second[i]]=&Interface::vol_dn;
      }
      continue;
    }
    if (it->first=="cli") {
      for (int i=0; i<it->second.size(); i++) {
        opts.keys[it->second[i]]=&Interface::cli;
      }
      continue;
    }
  }
}

Config::getopts(int argc, char** argv)
{
  int option_index = 0;
  int c;
  struct options cmdopts;
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
      {"player"              , 1, 0, 'P'},
      {"player-args"         , 1, 0, 'a'},
      {"config-file"         , 1, 0, 'c'},
      {"ignore-config"       , 0, 0, 'i'},
      {"generate-titles"     , 0, 0, 'g'},
      {"dont-generate-titles", 0, 0, 'G'},
      {"title-width"         , 1, 0, 't'},
      {"help"                , 0, 0, 'h'},
      {0, 0, 0, 0}  // NULL marks end
    };
    c = getopt_long(argc, argv, "p:rRl::f:F:P:a:c:t:ihgG",
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
        printf("[ -g | --generate-titles              ]\n");
        printf("[ -G | --dont-generate-titles         ]\n");
        printf("[ -t | --title-width <title-width>    ]\n");
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
  if (cmdgenerateTitles)
    opts.generateTitles=cmdopts.generateTitles;
  if (cmdtitlewidth)
    opts.titlewidth=cmdopts.titlewidth;
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
      if (strncmp(option,"key_",4)==0) {
        opt = &option[4];
        val.erase(val.begin());
        val.erase(val.end()-1);
        /* Taste schonmal belegt? */
        for (map<string,string>::iterator it=opts.keytable.begin();
            it != opts.keytable.end(); it++)
          for (int i=0; i<val.size(); i++) 
            if (it->second.find(val[i])!=-1) 
              /* alte Belegung entfernen */
              it->second.erase(it->second.find(val[i]));
        opts.keytable[opt]=val;
        continue;
      }
      fprintf(stderr,"configfile: unknown option: %s\n",line);
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
