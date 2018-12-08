#include "inc_all.h"

//----------------------------------------------------------------------------------------------------
Curses_Color_Class::Curses_Color_Class (void)
{
   Init_Curses();
}
void Curses_Color_Class::Init_Curses (void)
{
   initscr            (              );
   cbreak             (              );
   noecho             (              );
   keypad             ( stdscr, TRUE );
   nodelay            ( stdscr,true  );
   start_color        (              );
   use_default_colors (              ); // mantiene los colores de la consola que lo llama genial!! agianta la tranparencia
   Init_Full_Colors   (              );
   curs_set           ( 0            );
}

void Curses_Color_Class::init_Basic_Colors (void)
{
  if (has_colors ()) {
      int color[] = { COLOR_WHITE, COLOR_RED, COLOR_GREEN, COLOR_YELLOW, COLOR_BLUE, COLOR_MAGENTA, COLOR_CYAN, COLOR_BLACK };
      int pair = 1;
      int fg, bg;
      int limit;

      limit = (COLORS < MAX_BASIC_COLORS) ? COLORS : MAX_BASIC_COLORS;

      /* Create the color pairs. */
      for (fg = 0; fg < limit; fg++) {
         for (bg = 0; bg < limit; bg++) {
            init_pair ((short)pair++, (short)color[fg], (short)color[bg]);
         }
      }
   }
}
void Curses_Color_Class::Init_Full_Colors (void)
{
   int color[] = { COLOR_WHITE, COLOR_RED, COLOR_GREEN, COLOR_YELLOW, COLOR_BLUE, COLOR_MAGENTA, COLOR_CYAN, COLOR_BLACK };
   int Count=80;
   int Pair=1;
   int i;
   for(Pair=1;Pair<8;Pair++) {
      init_pair (Pair, COLOR_WHITE,color[Pair]);
   }
   for(Pair=8;Pair<16;Pair++) {
      init_pair (Pair, COLOR_WHITE,Pair);
      init_color(Pair,Pair*1000/8,Pair*1000/8,Pair*1000/8);
   }
   Pair=16;
   for(i=0;i<Count;i++) {
      init_pair (Pair, COLOR_WHITE, Pair);
      init_color(Pair,100,100,i*1000/Count);
      Pair++;
   }
   for(i=0;i<Count;i++) {
      init_pair (Pair, COLOR_WHITE, Pair);
      init_color(Pair,i*1000/Count,0,1000-i*1000/Count);
      Pair++;
   }
   for(i=0;i<Count;i++) {
      init_pair (Pair, COLOR_WHITE, Pair);
      init_color(Pair,1000-i*1000/Count,i*1000/Count,0);
      Pair++;
   }
}
void Curses_Color_Class::Init_Gradient_Colors(unsigned char R,unsigned char G,unsigned char B,unsigned char From, unsigned char Count)
{
   if (has_colors ()) {
      uint16_t i,Bg,Pair;
      Pair=MIN_COLOUR_PAIR+From; // los primeros 64 se los regalo a CDK en su llamada a initCDKColor
      Bg=16+From;                // cdk usa solo 8 colores... me agarro el resto (parece que tambien usa el 15...raaaro)
      for(i=1;i<Count;i++)    {  // no me puedo pasar de 255 pares... no da mas la funcion PAIR_NUMBER.. si no fuera por eso podria seguir...
         init_pair (Pair,(i<Count/2)?15:255,Bg);
         init_color(Bg,(i*1000/Count)*R,(i*1000/Count)*G,(i*1000/Count)*B);
         Bg++;
         Pair++;
      }
   }
}
