/*
 * Here are all commands defined
 */


#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../playlist.hh"
#include "info.hh"
#include "../config.h"
#include <malloc.h>

#ifdef LIBID3TAG
#include <id3tag.h>
#include "genre.dat"
# define NGENRES (sizeof(genre_table) / sizeof(genre_table[0]))

const char* get_frame_description( struct id3_frame *frame )
{
      if( strncmp( ID3_FRAME_TITLE, frame->id, 4 ) == 0 )
	  return "Title";
      else if( strncmp( ID3_FRAME_TRACK, frame->id, 4 ) == 0 )
	  return "Track No";
      else if( strncmp( ID3_FRAME_ARTIST, frame->id, 4 ) == 0 )
	  return "Artist";
      else if( strncmp( ID3_FRAME_GENRE, frame->id, 4 ) == 0 )
	  return "Genre";
      else if( strncmp( "TLEN", frame->id, 4 ) == 0 )
	  return "Length";
      else if( strncmp( ID3_FRAME_ALBUM, frame->id, 4 ) == 0 )
	  return "Album";
      else if( strncmp( ID3_FRAME_YEAR, frame->id, 4 ) == 0 )
	  return "Year";
      else if( strncmp( ID3_FRAME_COMMENT, frame->id, 4 ) == 0 )
	  return "Comment";
      else return frame->description;
}

void show_frame( struct id3_frame *frame )
{
      if( !frame ) return;
      unsigned int i,a;
      int f=0;
#define MAX_CONTENT 8192
      char descr[512], content[MAX_CONTENT];
      id3_latin1_t *frptr[8192];
      /* snprintf( descr, 512, "%4s %-12s:", frame->id, get_frame_description( frame ) ); */
      snprintf( descr, 512, "%-9s:", get_frame_description( frame ) );
      for( i=0; i<frame->nfields; i++ ){
	  switch( frame->fields[i].type ){
	      case ID3_FIELD_TYPE_STRING:
		  frptr[f] = id3_ucs4_latin1duplicate( id3_field_getstring( frame->fields+i ) );
		  if( frptr[f] && frptr[f][0] )
		      snprintf( content, MAX_CONTENT, "%s", frptr[f++] );
		  break;
	      case ID3_FIELD_TYPE_STRINGFULL:
		  frptr[f] = id3_ucs4_latin1duplicate( id3_field_getfullstring( frame->fields+i ) );
		  if( frptr[f] && frptr[f][0] )
		      snprintf( content, MAX_CONTENT, "%s", frptr[f++] );
		  break;
	      case ID3_FIELD_TYPE_STRINGLIST:
		  for( a=0; a<id3_field_getnstrings( frame->fields+i); a++ ){
		      frptr[f] = id3_ucs4_latin1duplicate( id3_field_getstrings( \
				  frame->fields+i, a ) );
		      if( frptr[f] && frptr[f][0] )
			  snprintf( content, MAX_CONTENT-strlen(content),
				  "%s%s ", content, frptr[f++] );
		  }
		  break;
	      case ID3_FIELD_TYPE_INT8:
	      case ID3_FIELD_TYPE_INT16:
	      case ID3_FIELD_TYPE_INT24:
	      case ID3_FIELD_TYPE_INT32:
		  a = id3_field_getint( frame->fields+i );
		  if( (signed)a != -1 ) snprintf( content, MAX_CONTENT, "%d", a );
		  break;
	      case ID3_FIELD_TYPE_LANGUAGE:
	      case ID3_FIELD_TYPE_FRAMEID:
	      case ID3_FIELD_TYPE_DATE:
	      case ID3_FIELD_TYPE_INT32PLUS:
	      case ID3_FIELD_TYPE_BINARYDATA:
	      case ID3_FIELD_TYPE_TEXTENCODING:
	      case ID3_FIELD_TYPE_LATIN1:
	      case ID3_FIELD_TYPE_LATIN1FULL:
	      case ID3_FIELD_TYPE_LATIN1LIST:
	      default: /* printf( "unknown tag type %d", frame->fields[i].type ) */ ;
	  }
	  // printf( "field type: %d\n", frame->fields[i].type );
	  /* FIXME id3_ucs4_t != (id3_ucs4_t) id3_latin1_t; */
	  if( strncmp( ID3_FRAME_GENRE, frame->id, 4 ) == 0 ){
	      int number;
	      if( sscanf( content, "%d", &number ) == 1 )
		  if( number < (signed)NGENRES ){
		      frptr[f] = id3_ucs4_latin1duplicate( genre_table[number] );
		      snprintf( content, MAX_CONTENT, "%s", frptr[f++] );
		  }
	  }
	  if( (unsigned)strlen( content ) > a ) printf( "%s %s\n", descr, content );
	  while(f-->0)
	      free(frptr[f]);
      }
}

#endif

extern Playlist* plist;

void
Info::doit( const string &s )
{
#ifdef LIBID3TAG
  struct id3_file *file = id3_file_open( (*(*plist)).filename().c_str(), ID3_FILE_MODE_READONLY );
  if( !file ){
      fprintf( stderr, "error reading id3 tags\n" );
      return;
  }
  struct id3_tag *tag = id3_file_tag( file );
  if( !tag ){
      fprintf( stderr, "error reading id3 tags\n" );
      return;
  }
      struct id3_frame *frame;
      int i=0;
  while( (frame = id3_tag_findframe( tag, NULL, i++ )) )
      show_frame( frame );
  if( i == 1 )
      printf( "id3tag empty\n" );
  id3_file_close( file );
#else
#  ifdef MP3INFO_CMD
  int pid;
  pid = fork();
  if (pid==0) {
    execlp(MP3INFO_CMD,"mp3info",(*(*plist)).filename().c_str(),MP3INFO_CMD_ARGS,NULL);
    perror("execlp(mp3info)");
    exit(1);
  }
#  endif
#endif
}

void
Info::help( const string &s ) const
{
  printf("format: info\n");
  printf("description: shows information on current title\n");
  printf("see also: status, filename\n");
}

void 
Info::description() const
{
  printf("shows information on current title\n");
}
