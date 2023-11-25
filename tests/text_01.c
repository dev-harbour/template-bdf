/*
 *
 */

#include "bdf.h"

int main()
{
   const char *text[] = {
      "",
      "Mathematics and sciences:",
      "",
      "  ∮ E⋅da = Q,  n → ∞, ∑ f(i) = ∏ g(i),      ⎧⎡⎛┌─────┐⎞⎤⎫",
      "                                            ⎪⎢⎜│a²+b³ ⎟⎥⎪",
      "  ∀x∈ℝ: ⌈x⌉ = −⌊−x⌋, α ∧ ¬β = ¬(¬α ∨ β),    ⎪⎢⎜│───── ⎟⎥⎪",
      "                                            ⎪⎢⎜⎷ c₈   ⎟⎥⎪",
      "  ℕ ⊆ ℕ₀ ⊂ ℤ ⊂ ℚ ⊂ ℝ ⊂ ℂ,                   ⎨⎢⎜       ⎟⎥⎬",
      "                                            ⎪⎢⎜ ∞     ⎟⎥⎪",
      "  ⊥ < a ≠ b ≡ c ≤ d ≪ ⊤ ⇒ (⟦A⟧ ⇔ ⟪B⟫),      ⎪⎢⎜ ⎲     ⎟⎥⎪",
      "                                            ⎪⎢⎜ ⎳aⁱ-bⁱ⎟⎥⎪",
      "  2H₂ + O₂ ⇌ 2H₂O, R = 4.7 kΩ, ⌀ 200 mm     ⎩⎣⎝i=1    ⎠⎦⎭",
      "",
      "Linguistics and dictionaries:",
      "",
      "  ði ıntəˈnæʃənəl fəˈnɛtık əsoʊsiˈeıʃn",
      "  Y [ˈʏpsilɔn], Yen [jɛn], Yoga [ˈjoːgɑ]",
      "",
      "APL:",
      "",
      "  ((V⍳V)=⍳⍴V)/V←,V    ⌷←⍳→⍴∆∇⊃‾⍎⍕⌈"
   };

   int numLines = LEN( text );

   BDF *app = CreateWindow(830, 450, "Test text");

   LoadBDFFont("../font/9x18.bdf");

   Background( app, 0x2F3853 );

   while( ! MainLoop( app ) )
   {
      BEGINDRAWING( app );

         for ( int i = 0; i < numLines; i++ )
         {
            DrawBDFText( 36, i * 18 , text[ i ], 0x2F3853, 0xF1F1F1 );
         }

      ENDDRAWING( app );
      WaitEvents();
   }

   CloseAll( app );
}
