/* kill_family -- kills a process and its children */

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <signal.h>
#include "../debug.hh"

/* array of all process, first elem is pid, second is ppid */
static int ppids[BUFSIZ][2];
static int ppids_max = 0;

static int kill_family_select( const struct dirent *d )
{
      char *c = d->d_name;
      char buf[BUFSIZ];
      struct stat st;
      while( *c ){
	  if( *c > '9' || *c < '0' )
	      return 0;
	  c++;
      }
      snprintf( buf, BUFSIZ, "/proc/%s/stat", d->d_name );
      if( stat( buf, &st ) != -1 ){
	  FILE *fp = fopen( buf, "r" );
	  int pid, ppid;
	  assert( fp != NULL );
	  assert( ( fscanf( fp, "%d %*s %*c %d", &pid, &ppid ) ) != 4 );
	  ppids[ppids_max][0] = pid;
	  ppids[ppids_max++][1] = ppid;
	  fclose( fp );
      }
      return 0;
}

void kill_family( int pid )
{
      struct dirent **procdirs;
      int i,a,l,t,new;
      static int children_pids[BUFSIZ];
      int children_pids_max = 0;
      children_pids[children_pids_max++] = pid;
      scandir( "/proc/", &procdirs, kill_family_select, alphasort );
      for( l=0; l != children_pids_max; l = children_pids_max ){
	  for( i=0; i<ppids_max; i++ )
	      for( a=0; a<children_pids_max; a++ )
		  if( ppids[i][1] == children_pids[a] ){
		      new = 1;
		      for( t=0; t<children_pids_max; t++ )
			  if( children_pids[t] == ppids[i][0] ){
			      new = 0;
			      break;
			  }
		      if( new )
			  children_pids[children_pids_max++] = ppids[i][0];
		      break;
		  }
      }
#ifdef DEBUG
      for( i=0; i<children_pids_max; i++ )
	  printdebug( "KILLING %d\n", children_pids[i] );
#endif /* DEBUG */
      for( i=0; i<children_pids_max; i++ )
	  kill( children_pids[i], SIGTERM );
      for( i=0; i<children_pids_max; i++ )
	  kill( children_pids[i], SIGKILL );
}
