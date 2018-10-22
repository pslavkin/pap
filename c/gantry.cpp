#include "inc_all.h"

Gantry_Class::Gantry_Class(Sheet* Parent,Dim D)
{
   uint16_t Pos;
   S    = new Sheet(Parent,D);
   Fade = 189;
   for(Pos=0;Pos<FADE;Pos++) {
      Last_X      [Pos]    =D.W/2;
      Last_Y      [Pos]    =D.H/2;
   }
}
void Gantry_Class::Set_Coords(Coords_Class* C)
{
   this->Coords=C;
   this->Coords->Max_Y=S->Dims.H-2;
   this->Coords->Max_X=S->Dims.W-2;
   this->Coords->Min_Y=1;
   this->Coords->Min_X=1;
   this->Coords->X=S->Dims.W/2;
   this->Coords->Y=S->Dims.H/2;
}
void Gantry_Class::Rti(void)
{
   while(1) {
      nanosleep   ( &Rti_Delay ,&Rti_Delay );
      Fade_Pixels ( Coords->Y  ,Coords->X  );
   }
}
void Gantry_Class::Fade_Pixels(uint32_t Y, uint32_t X)
{
   uint16_t Pos,Color;
   mvwaddch (S->Win, Last_Y[0], Last_X[0], ('.' | COLOR_PAIR(0))); //borra la mas viejaa

   for(Pos=0;Pos<Fade;Pos++) {
      Last_X      [Pos]    =Last_X  [Pos+1];
      Last_Y      [Pos]    =Last_Y  [Pos+1];
      Color=MIN_COLOUR_PAIR+Pos*(MAX_COLOUR_PAIR-MIN_COLOUR_PAIR)/Fade;
      mvwaddch (S->Win, Last_Y[Pos], Last_X[Pos], ' ' | COLOR_PAIR(Color));
   }
   wattron(S->Win,A_BOLD);
   mvwaddch ( S->Win, Last_Y[Pos]=Y,Last_X[Pos]=X, 'O' | COLOR_PAIR(0));
   wattroff(S->Win,A_BOLD);
}
void Gantry_Class::Toogle_Pixel(uint32_t Y, uint32_t X)
{
   mvwaddch ( S->Win ,Y ,X ,'X' | COLOR_PAIR(2));
}
