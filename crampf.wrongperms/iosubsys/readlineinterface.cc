/*
 * This Class provides the ex-like interface
 */

#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
extern "C" {
#include <readline/readline.h>
#undef CTRL
#include <readline/history.h>
}
#include "config.hh"
#include "readlineinterface.hh"

extern struct options* opts;

char *crampf_command_generator( char *text, int state ){
    static map<string,Command*>::const_iterator cmd_it;
    static map<string,vector<string> >::const_iterator def_it;
    static int count, len;
    char *name;
    if( !state ){
	count = 0;
	cmd_it = opts->cmdmap.cmdmap.begin();
	def_it = opts->cmdmap.defmap.begin();
	len = strlen( text );
    }
    while( def_it != opts->cmdmap.defmap.end() ){
	if( strlen(text) == 0 || def_it->first.find( text ) == 0 )
	    return strdup((def_it++)->first.c_str());
	def_it++;
    }
    while( cmd_it != opts->cmdmap.cmdmap.end() ){
	if( strlen(text) == 0 || cmd_it->first.find( text ) == 0 )
	    return strdup((cmd_it++)->first.c_str());
	cmd_it++;
    }
    return (char*)NULL;
}

char **crampf_completion( char *text, int start, int end ){
    char **matches = (char**)NULL;
    if( start == 0 )
	matches = completion_matches( text, crampf_command_generator );
    return matches;
}

ReadLineInterface::ReadLineInterface()
{
  using_history();
  initialize_readline();
}

void
ReadLineInterface::initialize_readline()
{
  rl_readline_name = "crampf";
  rl_attempted_completion_function = (CPPFunction*)crampf_completion;
}

ReadLineInterface::~ReadLineInterface()
{
}

void
ReadLineInterface::input()
{
  char* cmd = readline(":");
  if (cmd && *cmd) {
    add_history(cmd);
    try {
      opts->cmdmap[cmd];
    } catch (string error) {
      if (error=="quit" || error=="exit")
        throw error;
      printf("error: `%s'\n",error.c_str());
    }
  }
  free(cmd);
}

void
ReadLineInterface::input( const string &s )
{
  string cmd;
  char prompt[ s.length() ];
  strcpy( prompt, s.c_str() );
  char *searchstr = readline( prompt );
  if (searchstr && *searchstr) 
    add_history(searchstr);
  try {
    string cmd = string(searchstr);;
    if (s[0]=='/')
      cmd=string("search ") + cmd;
    if (s[0]=='?')
      cmd="rsearch " + cmd;
    opts->cmdmap[cmd];
  } catch (string error) {
    if (error=="quit" || error=="exit")
      throw error;
    printf("error: `%s'\n",error.c_str());
  }
  free(searchstr);
}

