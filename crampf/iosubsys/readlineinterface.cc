/*
 * This Class provides the ex-like interface
 */

#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <config.h>
#ifdef HAVE_RL_COMPLETION_MATCHES
#  include <readline/readline.h>
#  include <readline/history.h>
#else
  /* Backwards compatibility hack for rh6.0 systems :( */
  extern "C" {
#  include <readline/readline.h>
#  define rl_completion_matches completion_matches
#  undef CTRL
#  include <readline/history.h>
  }
#endif

#include "options.hh"
#include "readlineinterface.hh"


extern struct options* opts;

char *crampf_command_generator( const char *text, int state ){
    static std::map<std::string,Command*>::const_iterator cmd_it;
    static std::map<std::string,std::vector<std::string> >::const_iterator def_it;
    static int count, len;
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

char **crampf_completion( const char *text, int start, int end ){
    char **matches = (char**)NULL;
    if( start == 0 )
	matches = rl_completion_matches( text, crampf_command_generator );
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
#if !defined (_RL_FUNCTION_TYPEDEF)
  /* Backwards compatibility hack for rh6.0 systems :( */
  rl_attempted_completion_function = (CPPFunction*)crampf_completion;
#else
  rl_attempted_completion_function = (rl_completion_func_t*)crampf_completion;
#endif
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
    } catch (std::string error) {
      if (error=="quit" || error=="exit")
        throw error;
      printf("error: `%s'\n",error.c_str());
    }
  }
  free(cmd);
}

void
ReadLineInterface::input( const std::string &s )
{
  std::string cmd;
  char prompt[ s.length() ];
  strcpy( prompt, s.c_str() );
  char *searchstr = readline( prompt );
  if (searchstr && *searchstr) 
    add_history(searchstr);
  try {
    std::string cmd = std::string(searchstr);;
    if (s[0]=='/')
      cmd=std::string("search ") + cmd;
    if (s[0]=='?')
      cmd="rsearch " + cmd;
    opts->cmdmap[cmd];
  } catch (std::string error) {
    if (error=="quit" || error=="exit")
      throw error;
    printf("error: `%s'\n",error.c_str());
  }
  free(searchstr);
}

#ifndef HAVE_RL_COMPLETION_MATCHES
  /* Backwards compatibility hack for rh6.0 systems :( */
#  undef rl_completion_matches
#endif
