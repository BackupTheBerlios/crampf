#include "input.hh"
#include "output.hh"
#include "config.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include "options.hh"

Input::Input()
{
}

Input::~Input()
{
      for( iterator it = begin(); it != end(); it++ )
	  delete *it;
}

std::string
Input::read()
{
      std::string res;
      for( iterator it = begin(); it != end(); it++ ){
	  res = (*it)->read();
	  if( res != "" ) /* FIXME this is NOT fair queuing !!! */
	      return res;
      }
      return std::string( "" );
}

TermInput::TermInput()
{
      /* save terminal settings */
      if (tcgetattr(1,&terminal_settings)==-1) {
	  perror("tcgetattr");
      }
      singlekeyTerm();
}

TermInput::~TermInput()
{
      restoreTerm();
}

std::string
TermInput::read()
{
      int c = fgetc(stdin); 
      switch( c ){
	  case EOF: return std::string(""); /* no key pressed */
	  case ':': return readline( ":" ).insert( 0, ":" );
	  case '/':
	  case '?': {
		      char xx[2] = { c, '\0' };
		      std::string cmd = readline( xx );
		      if (c=='/')
			  cmd=std::string("search ") + cmd;
		      if (c=='?')
			  cmd="rsearch " + cmd;
		      return cmd;
		    }
	  default:
		  std::string res("x");
		  res[0] = c;
		  return res;
      }
}

void
TermInput::singlekeyTerm() const
{
  struct termios t;
  t = terminal_settings;
  t.c_lflag&=~(ICANON|ECHO);
  if (tcsetattr(1,TCSANOW,&t)==-1) {
    perror("tcsetattr");
  }
  if (fcntl(1,F_SETFL, O_NONBLOCK)==-1) {
    perror("fcntl");
  }
}

void
TermInput::restoreTerm() const
{
  if (tcsetattr(1,TCSANOW,&terminal_settings)==-1) {
    perror("tcsettatr");
  }
}


std::string
TermInput::readline( const char *prompt )
{
      restoreTerm();
#ifdef HAVE_READLINE
      std::string res = rli.input( prompt );
#else
      static char buf[BUFSIZ];
      int len = fread( buf, sizeof(char), BUFSIZ, stdin );
      buf[len] = '\0';
      std::string res( buf );
#endif
      singlekeyTerm();
      return res;
}
