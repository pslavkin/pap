#include <cdk/cdk.h>
#include <thread>
#include <panel.h>
#include "dim.h"
#include "sheet.h"
#include "menu.h"
#include "histograms.h"
#include "gantry.h"
#include "screen_update.h"

Gantry_Class::Gantry_Class(Sheet* Parent,Dim D)
{
   S    = new Sheet(Parent,D);
   Fade = 100;
}
void Gantry_Class::Rti(void)
{
   static uint16_t X=1,Y=1;
   switch(rand()%4) {
      case 0:
         if(X<(S->Dims.W-2)) {
            X++;
         }
         else
            X=1;
         break;
      case 1:
         if(X>1)
            X--;
         else
            X=(S->Dims.W-2);
         break;
      case 2:
         if(Y<(S->Dims.H-2)) {
            Y++;
         }
         else
            Y=1;
         break;
      case 3:
         if(Y>1)
            Y--;
         else
            Y=(S->Dims.H-2);
         break;
   }

   //Toogle_Pixel(rand()%(S->Dims.H-2)+1,rand()%(S->Dims.W-2)+1);
   Toogle_Pixel(Y,X);
}
void Gantry_Class::Fade_Pixels(unsigned char Times)
{
   unsigned short int Pos,Color;
   for ( Pos=0;Pos<Times;Pos++ )
      if(Last_Y[Pos]) mvwaddch (S->Win, Last_Y[Pos], Last_X[Pos], ('.' | COLOR_PAIR(0))); //borra la mas viejaa

   for(Pos=0;Pos<(Fade-Times);Pos++) {
      Last_X      [Pos]    =Last_X  [Pos+Times];
      Last_Y      [Pos]    =Last_Y  [Pos+Times];
      Color=MIN_COLOUR_PAIR+((unsigned int)Pos*(MAX_COLOUR_PAIR-MIN_COLOUR_PAIR))/Fade;
      if(Color>MAX_COLOUR_PAIR || Color<MIN_COLOUR_PAIR) 1;
      if(Last_Y[Pos]) mvwaddch (S->Win, Last_Y[Pos], Last_X[Pos], ' ' | COLOR_PAIR(MIN_COLOUR_PAIR+((unsigned int)Pos*(MAX_COLOUR_PAIR-MIN_COLOUR_PAIR-1))/Fade));
   }
}
void Gantry_Class::Toogle_Pixel(unsigned char Y, unsigned char X)
{
   Fade_Pixels(1);
   mvwaddch ( S->Win, Last_Y[Fade-1]=Y,Last_X[Fade-1]=X, 'O' | COLOR_PAIR(2 ));
}
