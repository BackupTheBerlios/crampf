/*
 * CommandMap -- funcname -> function
 */

#include <string>
#include <map>
#include "commandmap.hh"
#include "command.hh"
#include "commands.hh"
#include "debug.hh"
#include "config.h"

unsigned int CommandMap::objcnt = 0;

CommandMap::CommandMap()
{
  if( ! objcnt++ ){
      cmdmap["help"]           = new Help           (this);
      cmdmap["map"]            = new Map            (this);
      cmdmap["titlewidth"]     = new TitleWidth     ();
      cmdmap["loop"]           = new Loop           ();
#ifdef MIXER_CMD
      cmdmap["volume"]         = new Vol            ();
#endif
#if defined(LIBID3TAG) || defined(MP3INFO_CMD)
      cmdmap["info"]           = new Info           ();
#endif
      cmdmap["autocommand"]    = new Autocommand    ();
      cmdmap["quit"]           = new Quit           ();
      cmdmap["status"]         = new Status         ();
      cmdmap["jump"]           = new Jump           ();
      cmdmap["addpath"]        = new AddPath        ();
      cmdmap["shuffle"]        = new Shuffle        ();
      cmdmap["version"]        = new Version        ();
      cmdmap["loadplaylist"]   = new LoadPlaylist   ();
      cmdmap["pfilter"]        = new PFilter        ();
      cmdmap["nfilter"]        = new NFilter        ();
      cmdmap["loadnfilter"]    = new LoadNFilter    ();
      cmdmap["loadpfilter"]    = new LoadPFilter    ();
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
      cmdmap["case"]	       = new Case	    ();
      cmdmap["regexp"]	       = new RegExp	    ();
      cmdmap["exit"]   	       = new Exit	    ();
      cmdmap["sort"]   	       = new Sort	    ();
      cmdmap["list"]   	       = new ListTracks	    ();
      cmdmap["echo"]   	       = new Echo	    ();
  }
}

CommandMap::~CommandMap()
{
  for (map<string, Command*>::const_iterator it = cmdmap.begin();
      it != cmdmap.end(); it++)
    delete it->second;
}

void
CommandMap::operator[](const string &cmd)
{
      vector<string> cmds = splitCommands( cmd );
      for( vector<string>::iterator it = cmds.begin();
	      it != cmds.end(); it++ ){
	  string c = arg0(*it);
	  string p = args(*it);
	  printdebug( "CommandMap: command '%s', parameter '%s'\n", c.c_str(), p.c_str() );
	  if (cmdmap.count(c)) {
	      cmdmap[c]->doit(p);
	  } else if (defmap.count(c)) {
	      cmdmap["calldef"]->doit(c + " " + p);
	  } else {
	      try {
		  string macro = findFirstDef(c);
		  cmdmap["calldef"]->doit(macro + " " + p);
	      } catch (string error) {
		  Command* action = findFirst(c);
		  if (action!=NULL) {
		      action->doit(p);
		      return;
		  } else
		      throw string("bad command");
	      }
	  }
      }
}

string
CommandMap::findFirstDef( const string &c ) const
{
  for (map<string, vector<string> >::const_iterator it = defmap.begin();
      it != defmap.end(); it++)
    if (it->first.find(c)==0) 
      return it->first;
  throw string("bad command");
}

Command*
CommandMap::findFirst( const string &c ) const
{
  for (map<string, Command*>::const_iterator it = cmdmap.begin();
      it != cmdmap.end(); it++)
    if (it->first.find(c)==0) 
      return it->second;
  return NULL;
}

void
CommandMap::setKey(char key, const string &cmd)
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
CommandMap::help( const string &cmd )
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
CommandMap::arg0(string s) const
{
  while( s.size() > 0 && s[0] == ' ' )
      s.erase( 0, 1 );
  int sep = s.find(" ");
  if (sep==-1) 
    return s;
  else 
    return s.erase(sep,s.size());
}

string
CommandMap::args(string s) const
{
  while( s.size() > 0 && s[0] == ' ' )
      s.erase( 0, 1 );
  int sep = s.find(" ");
  if (sep==-1) 
    return "";
  s.erase(0,sep+1);
  for (sep=s.size()-1; s[sep]==' '; sep--)
    s.erase(sep);
  return s;
}

vector<string>
CommandMap::splitCommands( string s )
{
      vector<string> cmds;
      size_t start = 0, end;
      for( end = start; end < s.size(); end++ ){
#ifdef I_KNOW_WHAT_IAM_DOING
	  /* this breaks compatibility with \012 notation used for mapping
	     special keys :-( */
	  if( s[end] == '\\' ){
	      s.erase( end, 1 );
	      continue;
	  }
#endif /* I_KNOW_WHAT_IAM_DOING */
	  if( s[end] == ';' ){
	      cmds.push_back( s.substr( start, end-start ) );
	      printdebug( "multicommand: '%s'\n", cmds.back().c_str() );
	      start = end+1;
	  }
      }
      cmds.push_back( s.substr( start, end-start ) );
#ifdef DEBUG
      if( cmds.size() != 1 )
	  for( vector<string>::const_iterator it = cmds.begin();
		  it != cmds.end(); it++ ){
	      printdebug( "cmd: '%s'\n", it->c_str() );
	  }
#endif /* DEBUG */

      return cmds;
}
