#include "input.hh"
#include "output.hh"
#include "config.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include "../options.hh"
#include "../debug.hh"
#include "../commandmap.hh"

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

TermInput::TermInput() : InputObject( "terminal" )
{
      /* save terminal settings */
      if (tcgetattr(1,&terminal_settings)==-1) {
	  perror("tcgetattr");
      }
      singlekeyTerm();
      /* special keys */
      keynames["space"] = ' ';
      keynames["enter"] = '\n';
      keynames["tab"] = '\t';
      keynames["escape"] = '\e';
      /* default hotkeys */
      hotkeys['h'] = std::string( "module terminal hotkeys" );
      hotkeys['n'] = std::string( "search" );
      hotkeys['N'] = std::string( "rsearch" );
      hotkeys['i'] = std::string( "info" );
      hotkeys['q'] = std::string( "quit" );
      hotkeys['x'] = std::string( "exit" );
      hotkeys['s'] = std::string( "status" );
      hotkeys['v'] = std::string( "volume" );
      hotkeys['+'] = std::string( "volume +5" );
      hotkeys['-'] = std::string( "volume -5" );
      hotkeys['1'] = std::string( "volume 10" );
      hotkeys['2'] = std::string( "volume 20" );
      hotkeys['3'] = std::string( "volume 30" );
      hotkeys['4'] = std::string( "volume 40" );
      hotkeys['5'] = std::string( "volume 50" );
      hotkeys['6'] = std::string( "volume 60" );
      hotkeys['7'] = std::string( "volume 70" );
      hotkeys['8'] = std::string( "volume 80" );
      hotkeys['9'] = std::string( "volume 90" );
      hotkeys['0'] = std::string( "volume 00" );
      hotkeys['f'] = std::string( "filename" );
      hotkeys['p'] = std::string( "prev" );
      hotkeys['n'] = std::string( "next" );
      hotkeys[' '] = std::string( "next" );
      hotkeys['\n'] = std::string( "samedir" );
      hotkeys['\t'] = std::string( "samedir 2" );
      hotkeys['\e'] = std::string( "quit" );
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
	  case ':': return readline( ":" );
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
		  return hotkeys[c];
      }
}

void
TermInput::configure( const std::string &s )
{
      if( s.empty() || s == "hotkey" || s == "hotkeys" ||
	      s == "list" || s == "show" || s == "all" ){
	  output->printf( "---Special-Keys-(always-available)---\n" );
	  output->printf( "key ':' -> enter command\n" );
	  output->printf( "key '/' -> search forward\n" );
	  output->printf( "key '?' -> search backward\n" );
	  output->printf( "---Keymap-(user-definable)---\n" );
	  for( std::map<int,std::string>::const_iterator it = hotkeys.begin();
		  it != hotkeys.end(); it++ ){
	      std::map<std::string,int>::const_iterator at;
	      for( at = keynames.begin();
		      at != keynames.end(); at++ )
		  if( at->second == it->first ){
		      output->printf( "key '%s'\t-> '%s'\n", at->first.c_str(),
			      it->second.c_str() );
		      break;
		  }
	      if( at == keynames.end() )
		  output->printf( "key '%c' \t-> '%s'\n", it->first, it->second.c_str() );
	  }
      } else {
	  std::string cmd = CommandMap::arg0( s );
	  std::string args = CommandMap::args( s );
	  if( cmd == "hotkey" || cmd == "bind" ){
	      if( args.empty() )
		  configure( "show" );
	      else {
		  std::string key = CommandMap::arg0( args );
		  args = CommandMap::args( args );
		  if( args.empty() ){
		      if( key.size() == 1 ){
			  if( hotkeys.count( key[0] ) == 1 )
			      output->printf( "key '%c' -> '%s'\n",
				      key[0], hotkeys[key[0]].c_str() );
			  else
			      throw std::string( "key '" ) + key + "' undefined";
		      } else {
			  /* resolv special keyname */
			  if( keynames.count( key ) == 1 )
			      if( hotkeys.count( keynames[key] ) == 1 )
				  output->printf( "key '%s' -> '%s'\n",
					  keynames[key], hotkeys[key[0]].c_str() );
			      else
				  throw std::string( "key '" ) + key + "' undefined";
		      }
		  } else {
		      if( key.size() == 1 ){
			  printdebug( "assigning command '%s' to hotkey '%c'\n",
				  args.c_str(), key[0] );
			  hotkeys[key[0]] = args;
			  return;
		      } else {
			  /* TODO resolv special keyname */
		      }
		  }
	      }
	  }
      }
}

void
TermInput::help( const std::string &s ) const
{
      output->printf( "possible commands:\n" );
      output->printf( "bind <key> <command>  - bind key <key> to comand <command>\n" );
      output->printf( "show                  - show current configuration\n" );
      output->printf( "A key may be a letter (e.g. 'a', 'W' etc.) or one of the\n" );
      output->printf( "following special keynames:\n" );
      for( std::map<std::string,int>::const_iterator it = keynames.begin();
	      it != keynames.end(); it++ )
	  output->printf( "\t%s\n", it->first.c_str() );
}

void
TermInput::description() const
{
      output->printf( "terminal input module\n" );
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
