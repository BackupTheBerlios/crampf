#include "terminal.hh"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include "../options.hh"
#include "../debug.hh"
#include "../commandmap.hh"
#include "../config.h"
#include "output.hh"

TermInput::TermInput() : InputObject( "terminal" )
{
      /* save terminal settings */
      if (tcgetattr(1,&terminal_settings)==-1) {
	  perror("tcgetattr");
      }
      singlekeyTerm();
      /* key sequences for special keys (e.g. cursor keys ) */
      /* taken from linux console (is there a standard for this?) */
      escseqs["up"]	= "\e[A";
      escseqs["down"]	= "\e[B";
      escseqs["left"]	= "\e[C";
      escseqs["right"]	= "\e[D";
      escseqs["F1"]	= "\e[[A";
      escseqs["F2"]	= "\e[[B";
      escseqs["F3"]	= "\e[[C";
      escseqs["F4"]	= "\e[[D";
      escseqs["F5"]	= "\e[[E";
      escseqs["F6"]	= "\e[[17~";
      escseqs["F7"]	= "\e[[18~";
      escseqs["F8"]	= "\e[[19~";
      escseqs["F9"]	= "\e[[20~";
      escseqs["F10"]	= "\e[[21~";
      escseqs["F11"]	= "\e[[23~";
      escseqs["F12"]	= "\e[[24~";
      escseqs["home"]	= "\e[1~";
      escseqs["insert"]	= "\e[2~";
      escseqs["delete"]	= "\e[3~";
      escseqs["end"]	= "\e[4~";
      escseqs["pageup"]	= "\e[5~";
      escseqs["pagedown"]= "\e[6~";
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
      //hotkeys['\e'] = std::string( "quit" );
      /* default special keys */
      hotseqs[escseqs["left"]]	= std::string( "volume +5" );
      hotseqs[escseqs["right"]]	= std::string( "volume -5" );
      hotseqs[escseqs["up"] ]	= std::string( "prev" );
      hotseqs[escseqs["down"]]	= std::string( "next" );
      hotseqs[escseqs["F1"]]	= std::string( "help" );
      /* reverse mappings (for faster lookups) */
      for( std::map<std::string,int>::const_iterator it = keynames.begin();
	      it != keynames.end(); it++ )
	  keynames_rev[it->second] = it->first;
      for( std::map<std::string,std::string>::const_iterator it = escseqs.begin();
	      it != escseqs.end(); it++ )
	  escseqs_rev[it->second] = it->first;
}

TermInput::~TermInput()
{
      restoreTerm();
}

std::string
TermInput::read()
{
      static int buf[BUFSIZ];
      int i, seqpos;
      buf[0] = fgetc(stdin); 
      switch( buf[0] ){
	  case EOF: return std::string(""); /* no key pressed */
	  case ':': return readline( ":" );
	  case '/':
	  case '?': {
		      char xx[2] = { buf[0], '\0' };
		      std::string cmd = readline( xx );
		      if (buf[0]=='/')
			  cmd=std::string("search ") + cmd;
		      if (buf[0]=='?')
			  cmd="rsearch " + cmd;
		      return cmd;
		    }
	  default:
		  seqpos = 0;
		  while(1){
		      /* Try to read escape sequence (e.g. cursor keys) */
		      i = 0;
		      for( std::map<std::string,std::string>::const_iterator
			      it = hotseqs.begin(); it != hotseqs.end(); it++ )
			  if( it->first[seqpos] == buf[seqpos] )
			      i++;
		      assert( ++seqpos < BUFSIZ );
		      if( i > 1 )
			  buf[seqpos] = fgetc(stdin);
		      else
			  break;
		  }
		  if( i == 1 ){
		      static char cbuf[BUFSIZ];
		      buf[seqpos] = '\0';
		      while( seqpos-- ){
			  cbuf[seqpos] = buf[seqpos];
		      }
		      return hotseqs[cbuf];
		  } else {
		      if( seqpos > 1 ){
			  printdebug( "WARNING: read %d characters but found no escseqs\n", seqpos );
		      }
		      return hotkeys[buf[0]];
		  }
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
		  it != hotkeys.end(); it++ )
	      if( keynames_rev.count( it->first ) == 1 )
		      output->printf( "key '%s'\t-> '%s'\n", keynames_rev[it->first].c_str(),
			      it->second.c_str() );
	      else
		  output->printf( "key '%c' \t-> '%s'\n", it->first, it->second.c_str() );
	  for( std::map<std::string,std::string>::const_iterator it = hotseqs.begin();
		  it != hotseqs.end(); it++ )
	      if( escseqs_rev.count( it->first ) == 1 )
		  output->printf( "key '%s'\t-> '%s'\n", escseqs_rev[it->first].c_str(),
			  it->second.c_str() );
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
					  key.c_str(), hotkeys[keynames[key]].c_str() );
			      else
				  throw std::string( "key '" ) + key + "' undefined";
			  else if( escseqs.count( key ) == 1 )
			      if( hotseqs.count( key ) == 1 )
				  output->printf( "key '%s' -> '%s'\n",
					  key.c_str(), hotseqs[key].c_str() );
			      else
				  throw std::string( "key '" ) + key + "' undefined";
			  else
			      throw std::string( "unknown key '" ) + key + "'";
		      }
		  } else {
		      if( key.size() == 1 ){
			  printdebug( "assigning command '%s' to hotkey '%c'\n",
				  args.c_str(), key[0] );
			  hotkeys[key[0]] = args;
			  return;
		      } else {
			  /* resolv special keyname */
			  if( keynames.count( key ) == 1 ){
			      printdebug( "assigning command '%s' to hotkey '%s'\n",
				      args.c_str(), key.c_str() );
			      hotkeys[ keynames[ key ] ] = args;
			  } else if( escseqs.count( key ) == 1 ){
			      printdebug( "assigning command '%s' to hotkey '%s'\n",
				      args.c_str(), key.c_str() );
			      hotseqs[ escseqs[ key ] ] = args;
			  } else
			      throw std::string( "unknown key '" ) + key + "'";
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
      for( std::map<std::string,std::string>::const_iterator it = escseqs.begin();
	      it != escseqs.end(); it++ )
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
