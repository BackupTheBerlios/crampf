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
      if (error=="quit")
        throw error;
      printf("error: `%s'\n",error.c_str());
    }
  }
  free(cmd);
}

