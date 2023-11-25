/*
 *
 */

#include "bdf.h"

unsigned int fontData[ ENCODING ][ BITMAP_HEIGHT ];

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
// static
static void window_size_callback( GLFWwindow *window, int width, int height )
{
   BDF *pBDF = glfwGetWindowUserPointer( window );

   pBDF->width  = width;
   pBDF->height = height;
}

static void set_clear_color_from_hex( unsigned int hexColor )
{
   if( ( hexColor <= 0xffffff ) )
   {
      float r, g, b;
      r = ( ( hexColor >> 16 ) & 0xFF ) / 255.0;
      g = ( ( hexColor >> 8 )  & 0xFF ) / 255.0;
      b = (   hexColor         & 0xFF ) / 255.0;
      glClearColor( r, g, b, 1.0 );
   }
   else if( ( hexColor <= 0xffffffff ) )
   {
      float r, g, b, a;
      r = ( ( hexColor >> 24 ) & 0xFF ) / 255.0;
      g = ( ( hexColor >> 16 ) & 0xFF ) / 255.0;
      b = ( ( hexColor >> 8 )  & 0xFF ) / 255.0;
      a = (   hexColor         & 0xFF ) / 255.0;
      glClearColor( r, g, b, a );
   }
   else
   {
      fprintf( stderr, "An invalid hexadecimal color value was passed." );
   }
}

static void draw_point( float x, float y )
{
   glPointSize( 1.0 );
   glBegin( GL_POINTS );
      glVertex2f( x, y + 1 - BITMAP_HEIGHT );
   glEnd();
}

static void draw_bdf_char( float x, float y, unsigned int codepoint, unsigned int background, unsigned int foreground )
{
   unsigned int *bitmap = fontData[ codepoint ];

   set_color_from_hex( background );
   glBegin( GL_QUADS );
      glVertex2f( x - 1, y );
      glVertex2f( x + BITMAP_WIDTH, y );
      glVertex2f( x + BITMAP_WIDTH, y - BITMAP_HEIGHT );
      glVertex2f( x - 1, y - BITMAP_HEIGHT );
   glEnd();

   set_color_from_hex( foreground );
   for( int row = 0; row < BITMAP_HEIGHT; row++ )
   {
      unsigned int value = bitmap[ row ];
      for( int col = 0; col < BITMAP_WIDTH; col++ )
      {
         if( value & ( 1 << ( 15 - col ) ) )
         {
            draw_point( x + col, y + row );
         }
      }
   }
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
// internal
void set_color_from_hex( unsigned int hexColor )
{
   if( ( hexColor <= 0xffffff ) )
   {
      float r, g, b;
      r = ( ( hexColor >> 16 ) & 0xFF ) / 255.0f;
      g = ( ( hexColor >> 8 )  & 0xFF ) / 255.0f;
      b = (   hexColor         & 0xFF ) / 255.0f;
      glColor3f( r, g, b );
   }
   else if( ( hexColor <= 0xffffffff ) )
   {
      float r, g, b, a;
      r = ( ( hexColor >> 24 ) & 0xFF ) / 255.0f;
      g = ( ( hexColor >> 16 ) & 0xFF ) / 255.0f;
      b = ( ( hexColor >> 8 )  & 0xFF ) / 255.0f;
      a = (   hexColor         & 0xFF ) / 255.0f;
      glColor4f( r, g, b, a );
   }
   else
   {
      fprintf( stderr, "An invalid hexadecimal color value was passed." );
   }
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
// API functions
BDF *CreateWindow( int width, int height, const char *title )
{
   if( ! glfwInit() )
   {
      exit( EXIT_FAILURE );
   }

   BDF *pBDF = malloc( sizeof( BDF ) );
   if( ! pBDF )
   {
      fprintf( stderr, "Memory allocation failed for BDF structure.\n" );
      return NULL;
   }

   memset( pBDF, 0, sizeof( BDF ) );

   pBDF->width  = width;
   pBDF->height = height;
   pBDF->title  = title;
   pBDF->background = 0x323232;

   pBDF->window = glfwCreateWindow( pBDF->width, pBDF->height, pBDF->title, NULL, NULL );
   if( ! pBDF->window )
   {
      glfwTerminate();
      return NULL;
   }

   glfwMakeContextCurrent( pBDF->window );
   glfwSetWindowUserPointer( pBDF->window, pBDF );
   glfwSwapInterval( 1 );

   glfwSetWindowSizeCallback( pBDF->window, window_size_callback );

   glfwSetWindowSizeLimits( pBDF->window, pBDF->width, pBDF->height, GLFW_DONT_CARE , GLFW_DONT_CARE );

   return pBDF;
}

bool MainLoop( BDF *pBDF )
{
   bool state;

   pBDF->closeFlag = glfwWindowShouldClose( pBDF->window );
   glfwSetWindowShouldClose( pBDF->window, GLFW_FALSE );

   state = glfwGetWindowAttrib( pBDF->window, GLFW_ICONIFIED );
   if( state == T )
   {
      while( state == T )
      {
         state = glfwGetWindowAttrib( pBDF->window, GLFW_ICONIFIED );

         glfwWaitEventsTimeout( 0.5 );
      }
   }
   return pBDF->closeFlag;
}

void BeginDrawing( BDF *pBDF )
{
   glfwGetFramebufferSize( pBDF->window, &pBDF->width, &pBDF->height );

   glViewport( 0, 0, pBDF->width, pBDF->height );
   set_clear_color_from_hex( pBDF->background );
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   glDisable( GL_CULL_FACE );
   glDisable( GL_DEPTH_TEST );
   glEnable( GL_BLEND );
   glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   glOrtho( 0, pBDF->width, pBDF->height, 0, -1, 1 );
   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity();
}

void EndDrawing( const BDF *pBDF )
{
   glfwSwapBuffers( pBDF->window );
}

void Background( BDF *pBDF, unsigned int color )
{
   pBDF->background = color;
}

int CloseAll( BDF *pBDF )
{
   if( pBDF )
   {
      glfwDestroyWindow( pBDF->window );
      free( pBDF );
      glfwTerminate();
      exit( EXIT_SUCCESS );
   }
   else
   {
      fprintf( stderr, "Error: CloseWindow called with NULL BDF pointer.\n" );
      exit( EXIT_FAILURE );
   }
}

void PollEvents()
{
   glfwPollEvents();
}

void WaitEvents()
{
   glfwWaitEvents();
}

void WaitEventsTimeout( double timeout )
{
   glfwWaitEventsTimeout( timeout );
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
// Text
int LoadBDFFont( const char *file_path )
{
   char line[ 512 ];
   unsigned int encoding = 0, bitmap_index = 0;
   unsigned int bitmap[ BITMAP_HEIGHT ];

   FILE *file = fopen( file_path, "r" );
   if( file == NULL )
   {
      fprintf( stderr, "Error opening file: %s\n", file_path );
      return -1;
   }

   fseek( file, 0, SEEK_SET );

   while( fgets( line, sizeof( line ), file ) != NULL )
   {
      if( strstr( line, "ENCODING" ) != NULL && strstr( line, "ENCODING " ) == line )
      {
         sscanf( line, "ENCODING %u", &encoding );
      }
      else if( strstr( line, "BITMAP" ) != NULL )
      {
         bitmap_index = 0;
      }
      else if( bitmap_index < BITMAP_HEIGHT )
      {
         sscanf( line, "%x", &bitmap[ bitmap_index++ ] );
         if( bitmap_index == BITMAP_HEIGHT )
         {
            for( int i = 0; i < BITMAP_HEIGHT; i++ )
            {
               fontData[ encoding ][ i ] = bitmap[ i ];
            }
         }
      }
   }

   fclose( file );
   return 1;
}

void DrawBDFText( int x, int y, const char *text, unsigned int background, unsigned int foreground )
{
   unsigned int codepoint;
   int bytes;
   unsigned char ch;
   int i;

   y += BITMAP_HEIGHT;

   while( *text != '\0' )
   {
      bytes = 0;
      ch = ( unsigned char )( *text++ );
      if( ch <= 0x7F )
      {
         codepoint = ch;
         bytes = 1;
      }
      else if( ch <= 0xDF )
      {
         codepoint = ch & 0x1F;
         bytes = 2;
      }
      else if( ch <= 0xEF )
      {
         codepoint = ch & 0x0F;
         bytes = 3;
      } else
      {
         codepoint = ch & 0x07;
         bytes = 4;
      }
      for( i = 1; i < bytes; i++ )
      {
         ch = ( unsigned char )( *text++ );
         codepoint = ( codepoint << 6 ) | ( ch & 0x3F );
      }

      draw_bdf_char( x, y, codepoint, background, foreground );
      x += BITMAP_WIDTH + 1;
   }
}
