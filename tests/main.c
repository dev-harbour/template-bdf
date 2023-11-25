/*
 *
 */

#include "bdf.h"

int main()
{
   BDF *app = CreateWindow( 830, 450, "Test window" );

   LoadBDFFont( "../font/9x18.bdf" );

   Background( app, 0xEAEAEA );

   while( ! MainLoop( app ) )
   {
      BEGINDRAWING( app );

         // code ...
         int startX = ( app->width - 126 ) / 2;
         int startY = ( app->height - 18 ) / 2;

         DrawBDFText( startX, startY, "Hello, world!", 0xE1E1E1, 0x000000 );

      ENDDRAWING( app );
      WaitEvents();
   }

   CloseAll( app );
}
