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
      fd_set set;
      FD_ZERO( &set );
      int maxfd = -1, fd;
      for( iterator it = begin(); it != end(); it++ ){
	  fd = (*it)->getFD();
	  FD_SET( fd, &set );
	  if( fd > maxfd )
	      maxfd = fd;
      }
      if( maxfd == -1 )
	  return std::string( "" );
      struct timeval tv = { 0, 0 };
      select( maxfd+1, &set, NULL, NULL, &tv );
      for( iterator it = begin(); it != end(); it++ )
	  if( FD_ISSET( (*it)->getFD(), &set ) )
	      return (*it)->read(); /* FIXME this is not fair queuing !!! */
      return std::string( "" );
#if 0
      std::string res;
      if( rrp == end() ) /* FIXME what happens with the iterator
			    if an element was removed after rpp == end() ? */
	  rrp = begin();
      while( rrp != end() ){
	  res = (*rrp++)->read();
	  if( res != "" )
	      return res;
      }
      return std::string("");
#endif
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
	  case ':': /* TBD read full command string and execute */
		    return readline( ":" );
		    break;
	  case '/':
	  case '?': /* TBD read search string and search */
		    {
		      char xx[2] = { c, '\0' };
		      std::string cmd = readline( xx );
		      if (c=='/')
			  cmd=std::string("search ") + cmd;
		      if (c=='?')
			  cmd="rsearch " + cmd;
		      return cmd;
		    }
		  break;
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


int
TermInput::getFD() const
{
      return 0;
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
