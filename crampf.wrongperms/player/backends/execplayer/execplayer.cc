#include "execplayer.hh"
#include "../../../options.hh"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../../../debug.hh"
#include "../../../iosubsys/output.hh"
#include "../../../util/kill_family.h"

ExecPlayer *ExecPlayer::self = NULL;

#define NOT_A_PID 999999999

void execplayer_sigchld_handler( int status )
{
      if( ExecPlayer::self )
	  ExecPlayer::self->signalHandler( status );
}


static inline
bool which( const std::string &cmdname, char *result_path, int result_path_len )
{
      char *path = getenv( "PATH" );
      size_t start = 0, end = 0;
      while( end++ < strlen( path ) ){
	  if( path[end] == ':' && end-start < result_path_len-cmdname.size()-2 ){
	      memcpy( result_path, path+start, end-start );
	      result_path[end-start] = '/';
	      memcpy( result_path+end-start+1, cmdname.c_str(), cmdname.size() );
	      result_path[end-start+1+cmdname.size()] = '\0';
	      if( access( result_path, X_OK ) == 0 )
		  return true;
	      start = end + 1;
	  }
      }
      return false;
}

static inline
bool splitwords( const char *str, int str_len, char *head, int head_len, char *tail, int tail_len )
{
      assert( head_len >= str_len );
      assert( tail_len >= str_len );
      *head = *tail = '\0';
      while( ( str_len > 0 && *str != '\0' ) && ( *str == ' ' || *str == '\t' ) ){
	  str++;
	  str_len--;
      }
      while( ( str_len > 0 && *str != '\0' ) && *str != ' ' && *str != '\t' ){
	  *head++ = *str++;
	  str_len--;
      }
      *head = '\0';
      while( ( str_len > 0 && *str != '\0' ) && ( *str == ' ' || *str == '\t' ) ){
	  str++;
	  str_len--;
      }
      while( ( str_len > 0 && *str != '\0' ) ){
	  *tail++ = *str++;
	  str_len--;
      }
      *tail = '\0';
      return *str == '\0';
}

ExecPlayer::ExecPlayer( const StopCB &cb )
    : GenericPlayer( cb )
{
      self = this;
      pid = NOT_A_PID;
      signal(SIGCHLD,execplayer_sigchld_handler);
      addPlayer( "madplay /\\.mp3$/ 0.9" );
      addPlayer( "alsaplayer /\\.mp3$/ 0.8" );
      addPlayer( "mpg321 /\\.mp3$/ 0.7" );
      addPlayer( "amp /\\.mp3$/ 0.6" );
      addPlayer( "mpg123 -q /\\.mp3$/ 0.5" );
      addPlayer( "ogg123 /\\.ogg$/ 0.9" );
      addPlayer( "mplayer -vo null /\\.wma$/ 0.5 /\\.wav$/ 0.5 /\\.mp3$/ 0.5 /\\.mpg$/ 0.5 /\\.mpeg$/ 0.5 /\\.avi$/ 0.5 /\\.mov$/ 0.5" );
}

void
ExecPlayer::signalHandler( int status )
{
      printdebug("got signaled: signal=%d\n",status);
      if (status!=SIGCHLD) 
	  return;
      status = waitpid(-1,NULL,WNOHANG);
      if (status==0)
	  return;  /* no dead child */
      if (status != pid)
	  return; /* unknown child */
      pid = NOT_A_PID;
      try {
	  stopCB("");
      } catch( std::string error ){
	  output->printf( "%s\n", error.c_str() );
      }
}

bool
ExecPlayer::addPlayer( const std::string &cmdname,
		const std::list<std::string> &cmdargs, 
		const std::list<SupportedFilesRegExp> &supportedFilesRegExp,
		const std::list<SupportedFilesRegExpAsStrings> &supportedFilesRegExpAsStrings )
{
      char buf[BUFSIZ];
      if( which( cmdname, buf, BUFSIZ ) ){
	  struct PlayCmds cmd;
	  cmd.cmdname = cmdname;
	  cmd.cmdargs = cmdargs;
	  cmd.supportedFilesRegExp = supportedFilesRegExp;
	  cmd.supportedFilesRegExpAsStrings = supportedFilesRegExpAsStrings;
	  playCmds.push_back( cmd );
	  return true;
      } else
	  return false;
	  //throw std::string( std::string( "player " ) + cmdname + " not found" );
}

bool
ExecPlayer::addPlayer( const std::string & cfgstr )
{
      char cfgline[BUFSIZ], word[BUFSIZ], buf[BUFSIZ], regexp[BUFSIZ];
      enum State { CMDNAME, CMDARGS, REGEXP, SCORE } state = CMDNAME;
      double score;
      char *endptr;
      size_t re_start, re_stop;
      struct PlayCmds cmd;
      int re_flags = REG_NOSUB;
      /* aren't filesuffixes always are case insensitive ?
      if (!opts->casesensivity)
      */
      re_flags |= REG_ICASE; /* FIXME REG_ICASE ignores ^ and $ !!! */
      if (opts->regexp==2)
	  re_flags |= REG_EXTENDED; /* FIXME REG_EXTENDED ignores ^ and $ !!! */
      *regexp = '\0';
      assert( cfgstr.size() < BUFSIZ );
      memcpy( cfgline, cfgstr.c_str(), cfgstr.size() );
      cfgline[cfgstr.size()] = '\0';
      for(;;){
	  splitwords( cfgline, strlen( cfgline ), word, BUFSIZ, buf, BUFSIZ );
	  if( *word == '\0' )
	      break;
	  switch( state ){
	      case CMDNAME:
		  cmd.cmdname = word;
		  printdebug( "PlayerCmd: %s\n", cmd.cmdname.c_str() );
		  memcpy( cfgline, buf, BUFSIZ );
		  state = CMDARGS;
		  break;
	      case CMDARGS:
		  if( *word != '/' ){
		      cmd.cmdargs.push_back( word );
		      printdebug( "PlayerArgs: %s\n", word );
		      memcpy( cfgline, buf, BUFSIZ );
		      break;
		  }
	      case REGEXP:
		  if( *word != '/' ){
		      output->printf( "parsing error 1: '%s'\n", cfgstr.c_str() );
		      output->printf( "should be '/', but is '%c'\n", *word );
		      return false;
		  }
		  {
		    re_start = 0;
		    while( cfgline[re_start] != '/' ){
			re_start++;
			if( re_start >= strlen( cfgline ) ){
			    output->printf( "parsing error 2: '%s'\n", cfgstr.c_str() );
			    return false;
			}
			if( cfgline[re_start] == '/' && re_start > 0 &&
				cfgline[re_start-1] == '\\' )
			    re_start++; /* ignore backslashed (escaped) slashes */
		    }
		    re_start++;
		    re_stop = re_start+1;
		    while( cfgline[re_stop] != '/' ){
			re_stop++;
			if( re_stop >= strlen( cfgline ) ){
			    output->printf( "parsing error 3: '%s'\n", cfgstr.c_str() );
			    return false;
			}
			if( cfgline[re_stop] == '/' && re_stop > 0 &&
				cfgline[re_stop-1] == '\\' )
			    re_stop++; /* ignore backslashed (escaped) slashes */
		    }
		    memcpy( regexp, cfgline+re_start, re_stop-re_start );
		    regexp[re_stop-re_start] = '\0';
		    re_stop++;
		    memcpy( buf, cfgline+re_start+re_stop, strlen( cfgline+re_start+re_stop ) );
		    memcpy( cfgline, buf, strlen( buf ) + 1 );
		  }
		  state = SCORE;
		  break;
	      case SCORE:
		  score = strtod( word, &endptr );
		  if( word == endptr || *regexp == '\0' ){
		      output->printf( "parsing error 4: '%s'\n", cfgstr.c_str() );
		      return false;
		  }
		  cmd.supportedFilesRegExp.push_back(
			  SupportedFilesRegExp( new RegEx( regexp, re_flags ), score ) );
		  cmd.supportedFilesRegExpAsStrings.push_back(
			  SupportedFilesRegExpAsStrings( regexp, score ) );
		  printdebug( "PlayerRegExp/Score: %3.3f '%s'\n", score, regexp );
		  *regexp = '\0';
		  memcpy( cfgline, buf, BUFSIZ );
		  state = REGEXP;
		  break;
	      default:
		  output->printf( "parsing error 5: '%s'\n", cfgstr.c_str() );
		  return false;
	  }
      }
      return addPlayer( cmd.cmdname, cmd.cmdargs, cmd.supportedFilesRegExp,
	     cmd.supportedFilesRegExpAsStrings );
}

ExecPlayer::~ExecPlayer()
{
      for( std::list<struct PlayCmds>::const_iterator it = playCmds.begin();
	      it != playCmds.end(); it++ )
	  for( std::list<SupportedFilesRegExp>::const_iterator at =
		  it->supportedFilesRegExp.begin();
		  at != it->supportedFilesRegExp.end(); at++ )
	      delete at->first;
      self = NULL;
#if 0
      printf( "Available Players:\n" );
      for( std::list<struct PlayCmds>::const_iterator it = playCmds.begin();
	      it != playCmds.end(); it++ ){
	  printf( "cmd: '%s'\n", it->cmdname.c_str() );
	  printf( "\targs: " );
	  for( std::list<string>::const_iterator at = it->cmdargs.begin();
		  at != it->cmdargs.end(); at++ )
	      printf( "'%s' ", at->c_str() );
	  printf( "\n\tregexpscores:\n" );
	  for( std::list<SupportedFilesRegExp>::const_iterator at =
		  it->supportedFilesRegExp.begin();
		  at != it->supportedFilesRegExp.end(); at++ )
	      printf( "\t'%20s' %5.3f\n", at->first.c_str(), at->second );
      }
#endif
}

bool
ExecPlayer::play( const std::string &filename )
{
      printdebug( "play( \"%s\" )\n", filename.c_str() );
      /* FIXME this is an *UGLY* hack !!! */
      // system( "fuser -k /dev/dsp >/dev/null 2>&1" );
      double bestscore = 0;
      std::list<struct PlayCmds>::const_iterator bestplayer = playCmds.end();

      std::string myfile( filename );
      if( myfile[myfile.size()] != '\n' )
	  myfile += '\n';

      for( std::list<struct PlayCmds>::const_iterator it = playCmds.begin();
	      it != playCmds.end(); it++ )
	  for( std::list<SupportedFilesRegExp>::const_iterator at =
		  it->supportedFilesRegExp.begin();
		  at != it->supportedFilesRegExp.end(); at++ )
	      if( at->first->match( filename.c_str() ) )
		  if( at->second > bestscore ){
		      bestscore = at->second;
		      bestplayer = it;
		  }
      if( bestplayer != playCmds.end() ){
	  printdebug( "play::CMD:%8s %s\n", bestplayer->cmdname.c_str(), filename.c_str() );
	  pid = fork();
	  if (pid==-1) {
	      perror("fork");
	      exit(1);
	  } else if( pid ){
	      printdebug( "fork()=%d\n", pid );
	      return true;
	  } else {
	      char cmd[BUFSIZ];
	      which( bestplayer->cmdname.c_str(), cmd, BUFSIZ );
	      char *argv[ bestplayer->cmdargs.size() + 3 ];
	      int i=0;
	      argv[i++] = (char*)bestplayer->cmdname.c_str();
	      for( std::list<std::string>::const_iterator it = 
		      bestplayer->cmdargs.begin();
		      it != bestplayer->cmdargs.end(); it++ )
		  argv[i++] = (char*)(it->c_str());
	      argv[i++] = (char*)filename.c_str();
	      argv[i] = NULL;
	      printdebug( "execvp: %s\n", argv[0] );
	      fclose( stdin );
	      fclose( stdout );
	      fclose( stderr );
	      fopen( "/dev/null", "r" ); /* stdin */
	      fopen( "/dev/null", "w" ); /* stdout */
	      fopen( "/dev/null", "w" ); /* stderr */
	      execvp( cmd, argv );
	      perror( "execvp" );
	      exit(2);
	  }
      }
      return false;
}

bool
ExecPlayer::stop()
{
      printdebug( "stop() %d\n", pid != NOT_A_PID );
      if( pid != NOT_A_PID ){
#ifdef HAVE_PROC_STAT
	  kill_family( pid );
#else /* HAVE_PROC_STAT */
	  kill( pid,  SIGTERM );
#endif /* HAVE_PROC_STAT */
#if 0
	  if( pid != NOT_A_PID && kill(pid,SIGTERM) == 0 ){
	      usleep( 500 );
	      if( pid != NOT_A_PID && kill(pid,SIGKILL) == 0 ){
		  system( "fuser -k /dev/dsp" );
		  usleep( 500 );
	      }
	  }
#endif
      }
      return true;
}

double
ExecPlayer::supportedFormat( const std::string &filename ) const
{
      double bestscore = 0;
      std::list<struct PlayCmds>::const_iterator bestplayer = playCmds.end();

      std::string myfile( filename );
      if( myfile[myfile.size()] != '\n' )
	  myfile += '\n';

      for( std::list<struct PlayCmds>::const_iterator it = playCmds.begin();
	      it != playCmds.end(); it++ )
	  for( std::list<SupportedFilesRegExp>::const_iterator at =
		  it->supportedFilesRegExp.begin();
		  at != it->supportedFilesRegExp.end(); at++ )
	      if( at->first->match( myfile ) ){
		  if( at->second > bestscore ){
		      bestscore = at->second;
		      bestplayer = it;
		  }
	      }
      
      if( bestplayer == playCmds.end() )
	  return 0.0;
      else
	  return bestscore;
}

bool
ExecPlayer::isPlaying() const
{
      printdebug( "isPlaying() = %d\n", pid != NOT_A_PID );
      return pid != NOT_A_PID;
}

const std::list<struct ExecPlayer::PlayCmds> &
ExecPlayer::getPlayCmds() const
{
      return playCmds;
}
