#ifndef BDF_H_
#define BDF_H_

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GLFW/glfw3.h>

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

#define ENCODING            65533
#define BITMAP_WIDTH        9
#define BITMAP_HEIGHT       18
extern unsigned int fontData[ ENCODING ][ BITMAP_HEIGHT ];

typedef enum bool
{
   F = 0,
   T = ( ! 0 )
} bool;

typedef struct _BDF BDF;

struct _BDF
{
   GLFWwindow  *window;
   int          width;
   int          height;
   const char  *title;
   bool         closeFlag;
   unsigned int background;
};

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
// API functions
BDF *CreateWindow( int width, int height, const char *title );
bool  MainLoop( BDF *pBDF );
void  BeginDrawing( BDF *pBDF );
void  EndDrawing( const BDF *pBDF );
int   CloseAll( BDF *pBDF );
void  Background( BDF *pBDF, unsigned int color );
void  PollEvents();
void  WaitEvents();
void  WaitEventsTimeout( double timeout );

//--- Text
int  LoadBDFFont( const char *file_path );
void DrawBDFText( int x, int y, const char *text, unsigned int background, unsigned int foreground );

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
// internal
void set_color_from_hex( unsigned int hexColor );

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
// macros
#define BEGINDRAWING( pBDF ) do { BeginDrawing( pBDF )
#define ENDDRAWING( pBDF ) EndDrawing( pBDF ); } while( 0 )

#define MAX( a, b ) ( ( a ) < ( b ) ? ( b ) : ( a ) )
#define MIN( a, b ) ( ( a ) < ( b ) ? ( a ) : ( b ) )
#define UNUSED( n ) ( ( void )( n ) )
#define LEN( n ) ( sizeof( n ) / sizeof( n )[ 0 ] )

#endif /* End BDF_H_ */
