#include <cdk/cdk.h>
#include <thread>
#include <panel.h>
#include "dim.h"
#include "sheet.h"
#include "menu.h"
#include "histograms.h"
#include "gantry.h"


void Gantry_Class::Fade_Pixels(unsigned char Times)
{
   unsigned short int Pos,Color;
   for ( Pos=0;Pos<Times;Pos++ )
      if(Last_Y[Pos]) mvwaddch (Win, Last_Y[Pos], Last_X[Pos], ('.' | COLOR_PAIR(0))); //borra la mas viejaa

   for(Pos=0;Pos<(Fade-Times);Pos++) {
      Last_X      [Pos]    =Last_X  [Pos+Times];
      Last_Y      [Pos]    =Last_Y  [Pos+Times];
      Color=MIN_COLOUR_PAIR+((unsigned int)Pos*(MAX_COLOUR_PAIR-MIN_COLOUR_PAIR))/Fade;
      if(Color>MAX_COLOUR_PAIR || Color<MIN_COLOUR_PAIR) 1;
      if(Last_Y[Pos]) mvwaddch (Win, Last_Y[Pos], Last_X[Pos], ' ' | COLOR_PAIR(MIN_COLOUR_PAIR+((unsigned int)Pos*(MAX_COLOUR_PAIR-MIN_COLOUR_PAIR-1))/Fade));
   }
}
void Gantry_Class::Toogle_Pixel(unsigned char Y, unsigned char X)
{
   Fade_Pixels(1);
   mvwaddch ( Win, Last_Y[Fade-1]=Y,Last_X[Fade-1]=X, 'O' | COLOR_PAIR(2 ));
}

Gantry_Class::Gantry_Class(Sheet* Parent,Dim D) :Sheet(Parent,D)
{
   Fade=5;
   Histo_Class* H=new Histo_Class(this,0,0,10-2,3,(char*)"Z",10,5);
   TRti = std::thread();
}
void Gantry_Class::Start_Rti(void)
{
   TRti = std::thread(&Gantry_Class::Rti,this);
}
void Gantry_Class::Rti(void)
{
   struct timespec req={0, 50000000};
   while(1)  {
      nanosleep ( &req,&req );
      Toogle_Pixel(rand()%(getmaxy(Win)-2)+1,rand()%(getmaxx(Win)-2)+1);
  }
}

