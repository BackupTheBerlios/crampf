/*
 * Standard textmode interface
 */

#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include "interface.hh"
#include "config.hh"

Interface::Interface( void )
{
  printf("WELCOME TO THE CRAMPF!\n");
  struct termios t;
  tcgetattr(1,&terminal_settings);
  t = terminal_settings;
  t.c_lflag&=~(ICANON|ECHO);
  tcsetattr(1,TCSANOW,&t);
  showstatus();
  mainloop();
}

Interface::~Interface()
{
  tcsetattr(1,TCSANOW,&terminal_settings);
  printf("Thank you for using crampf!\n");
}

Interface::mainloop()
{
  char c;
  do {
    showstatus();
    c = fgetc(stdin); 
    if (opts->keys["next"].find(c)!=-1)
      ++(*plist);
    else if (opts->keys["prev"].find(c)!=-1)
      --(*plist);
    else if (opts->keys["help"].find(c)!=-1)
      printf("\nHELP\n");
  } while (opts->keys["quit"].find(c)==-1);
}

Interface::showstatus()
{
  printf("[%d/%d] - %s\n",plist->pos(),plist->size(),
      (*(*plist)).title().c_str());
}
