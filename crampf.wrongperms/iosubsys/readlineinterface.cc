/*
 * This Class provides the ex-like interface
 */

#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
extern "C" {
#include <readline/readline.h>
#include <readline/history.h>
}
#include "config.hh"
#include "readlineinterface.hh"

extern struct options* opts;

ReadLineInterface::ReadLineInterface()
{
  using_history();
  initialize_readline();
}

void
ReadLineInterface::initialize_readline()
{
  rl_readline_name = "crampf";
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
ReadLineInterface::input( string s )
{
  string cmd;
  char* searchstr = readline(s.c_str());
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

