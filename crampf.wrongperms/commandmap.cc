/*
 * CommandMap -- funcname -> function
 */

#include "version_info.hh"
#include <string>
#include <map>
#include "commandmap.hh"
#include "command.hh"
#include "commands.hh"

CommandMap::CommandMap()
{
  cmdmap["help"]           = new Help           (this);
  cmdmap["map"]            = new Map            (this);
  cmdmap["titlewidth"]     = new TitleWidth     ();
  cmdmap["loop"]           = new Loop           ();
  cmdmap["volume"]         = new Vol            ();
  cmdmap["info"]           = new Info           ();
  cmdmap["quit"]           = new Quit           ();
  cmdmap["status"]         = new Status         ();
  cmdmap["jump"]           = new Jump           ();
  cmdmap["addpath"]        = new AddPath        ();
  cmdmap["shuffle"]        = new Shuffle        ();
  cmdmap["version"]        = new Version        ();
  cmdmap["loadplaylist"]   = new LoadPlaylist   ();
  cmdmap["pfilter"]        = new PFilter        ();
  cmdmap["nfilter"]        = new NFilter        ();
  cmdmap["generatetitles"] = new GenerateTitles ();
  cmdmap["filename"]       = new Filename       ();
  cmdmap["define"]         = new Define         (this);
  cmdmap["calldef"]        = new CallDef        (this);
  cmdmap["source"]         = new Source         (this);
  cmdmap["search"]         = new Search         (this);
  cmdmap["rsearch"]        = new RSearch        (this);
  cmdmap["playercmd"]      = new PlayerCMD      ();
  cmdmap["playercmd_args"] = new PlayerCMD_Args ();
  cmdmap["randomorder"]    = new RandomOrder    ();
  cmdmap["write"]          = new Write          ();
  cmdmap["kill"]           = new Kill           ();
  cmdmap["unify"]          = new Unify          ();
}

CommandMap::~CommandMap()
{
  for (map<string, Command*>::iterator it = cmdmap.begin();
      it != cmdmap.end(); it++)
    delete it->second;
}

void
CommandMap::operator[](string cmd)
{
  string c = arg0(cmd);
  string p = args(cmd);
  if (cmdmap.count(c)) {
    cmdmap[c]->doit(p);
    return;
  } else if (defmap.count(c)) {
    cmdmap["calldef"]->doit(c + " " + p);
    return;
  } else {
    try {
      string macro = findFirstDef(c);
      cmdmap["calldef"]->doit(macro + " " + p);
      return;
    } catch (string error) {
    }
    Command* action = findFirst(c);
    if (action!=NULL) {
      action->doit(p);
      return;
    } else
      throw string("bad command");
  }
}

string
CommandMap::findFirstDef( string c )
{
  for (map<string, vector<string> >::iterator it = defmap.begin();
      it != defmap.end(); it++)
    if (it->first.find(c)==0) 
      return it->first;
  throw string("bad command");
}

Command*
CommandMap::findFirst( string c )
{
  for (map<string, Command*>::iterator it = cmdmap.begin();
      it != cmdmap.end(); it++)
    if (it->first.find(c)==0) 
      return it->second;
  return NULL;
}

void
CommandMap::setKey(char key, string cmd)
{
  try {
    string c = findFirstDef(arg0(cmd));
    keymap[key] = cmd;
  } catch (string error) {
    Command* action = findFirst(arg0(cmd));
    if (action==NULL)
      throw string("setKey: bad commandname");
    keymap[key] = cmd;
  }
}

void
CommandMap::help( string cmd )
{
  if (cmdmap.count(arg0(cmd))) 
    cmdmap[arg0(cmd)]->help(args(cmd));
  else {
    Command* action = findFirst(arg0(cmd));
    if (action!=NULL)
      action->help(args(cmd));
    else
      throw string("help: no such topic");
  }
}

void
CommandMap::operator[](char key)
{
  (*this)[keymap[key]];
}

string
CommandMap::arg0(string s)
{
  int sep = s.find(" ");
  if (sep==-1) 
    return s;
  else 
    return s.erase(sep,s.size());
}

string
CommandMap::args(string s)
{
  int sep = s.find(" ");
  if (sep==-1) 
    return "";
  s.erase(0,sep+1);
  for (sep=s.size()-1; s[sep]==' '; sep--)
    s.erase(sep);
  return s;
}
