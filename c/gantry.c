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
   Fade = 189;
}
void Gantry_Class::Rti(void)
{
   while(1) {
      nanosleep     ( &Rti_Delay,&Rti_Delay );
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
   Fade_Pixels(Y,X);
   }
}
void Gantry_Class::Fade_Pixels(uint16_t Y, uint16_t X)
{
   uint16_t Pos,Color;
   mvwaddch (S->Win, Last_Y[0], Last_X[0], ('.' | COLOR_PAIR(0))); //borra la mas viejaa

   for(Pos=0;Pos<Fade;Pos++) {
      Last_X      [Pos]    =Last_X  [Pos+1];
      Last_Y      [Pos]    =Last_Y  [Pos+1];
      Color=MIN_COLOUR_PAIR+Pos*(MAX_COLOUR_PAIR-MIN_COLOUR_PAIR)/Fade;
      mvwaddch (S->Win, Last_Y[Pos], Last_X[Pos], ' ' | COLOR_PAIR(Color));
   }
   mvwaddch ( S->Win, Last_Y[Pos]=Y,Last_X[Pos]=X, 'X' | COLOR_PAIR(2));
}
void Gantry_Class::Toogle_Pixel(uint16_t Y, uint16_t X)
{
   mvwaddch ( S->Win ,Y ,X ,'X' | COLOR_PAIR(2));
}
