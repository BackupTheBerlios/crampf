#include "tcpio.hh"
#include "../debug.hh"
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MYPORT 4321
#define BACKLOG 10

TcpIO::TcpIO()
{
      /* listen on crampf server io port */
      struct sockaddr_in my_addr;

      svrsockfd = socket( AF_INET, SOCK_STREAM, 0);
      if (svrsockfd == -1) {
	  fprintf(stderr,"Error opening socket!\n");
      }

      my_addr.sin_family = AF_INET; // host byte order
      my_addr.sin_port = htons( MYPORT );   // short network byte order
      my_addr.sin_addr.s_addr = INADDR_ANY; // autofill with my IP
      bzero(&(my_addr.sin_zero), 8);        // zero the rest of the struct

      if (bind(svrsockfd,(struct sockaddr *)&my_addr, sizeof(struct sockaddr))==-1) {
	  fprintf( stderr, "Error binding to port %d\n", MYPORT );
      }

      if (listen(svrsockfd,BACKLOG)==-1) {
	  fprintf( stderr, "Error listening on port %d\n", MYPORT );
      }
}

TcpIO::~TcpIO()
{
      close( svrsockfd );
      for( std::list<int>::iterator it = sockfds.begin();
	      it != sockfds.end(); it++ )
	  close( *it );
}

std::string
TcpIO::read()
{
      fd_set readfds;
      int maxfd = svrsockfd;
      FD_ZERO( &readfds );
      FD_SET( svrsockfd, &readfds );
      for( std::list<int>::iterator it = sockfds.begin();
	      it != sockfds.end(); it++ ){
	  if( *it > maxfd )
	      maxfd = *it;
	  FD_SET( *it, &readfds );
      }
      timeval tv = { 0, 0 };
      select( maxfd+1, &readfds, NULL, NULL, &tv );
      if( FD_ISSET( svrsockfd, &readfds ) ){
	  /* accept new connection */
	  /* FIXME connection could be removed already, have to set NONBLOCKING flag on svrsockfd */
	  struct sockaddr their_addr;
	  socklen_t sin_size = sizeof(struct sockaddr);
	  int newfd = accept( svrsockfd, &their_addr, &sin_size );
	  if( newfd == -1 )
	      perror( "accept" );
	  else {
	      printdebug( "%s\n", "accepted new connection" );
	      sockfds.push_back( newfd );
	  }
      }
      for( std::list<int>::iterator it = sockfds.begin();
	      it != sockfds.end(); it++ ){
	  if( FD_ISSET( *it, &readfds ) ){
	      char buf[BUFSIZ];
	      size_t len = ::read( *it, buf, BUFSIZ );
	      if( len > 2 && buf[len-2] == '\r' && buf[len-1] == '\n' ){
		  buf[len-2] = '\0'; /* strip \r\n */
		  printf( "DEBUG: read from socket '%s'\n", buf );
		  return std::string( buf );
	      } else if( len == -1 ){
		  perror( "read" );
		  /* FIXME remove connection */
	      }
	  }
      }
      return std::string( "" );
}

void
TcpIO::flush()
{
      while( !OutputObject::empty() ){
	  for( std::list<int>::iterator it = sockfds.begin();
		  it != sockfds.end(); it++ )
	      write( *it, OutputObject::front().c_str(), OutputObject::front().size() );
	  OutputObject::pop();
      }
}
