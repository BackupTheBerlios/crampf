/*
 * CommandMap -- funcname -> function
 */

#include <string>
#include <map>
#include "commandmap.hh"
#include "command.hh"
#include "commands.hh"

CommandMap::CommandMap()
{
  cmdmap["help"]       = new Help   (this);
  cmdmap["set"]        = new Set    (this);
  cmdmap["volume"]     = new Vol    ();
  cmdmap["info"]       = new Info   ();
  cmdmap["next"]       = new Next   ();
  cmdmap["previous"]   = new Prev   ();
  cmdmap["quit"]       = new Quit   ();
  cmdmap["status"]     = new Status ();
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
  if (cmdmap.count(c))
    cmdmap[c]->doit(p);
  else {
    Command* action = findFirst(c);
    if (action!=NULL) {
      action->doit(p);
      return;
    } else
      throw string("bad command");
  }
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
  string c = arg0(cmd);
  Command* action = findFirst(c);
  if (action==NULL)
    throw string("setKey: bad commandname");
  string p = args(cmd);
  keymap[key] = cmd;
}

void
CommandMap::help( string cmd )
{
  if (cmdmap.count(arg0(cmd)))
    cmdmap[arg0(cmd)]->help(args(cmd));
  else
    throw string("help: no such topic");
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
  else 
    return s.erase(0,sep+1);
}
