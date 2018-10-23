#include "inc_all.h"

Gantry_Class::Gantry_Class(Sheet* Parent,Dim D):Sheet(Parent,D)
{
   uint16_t Pos;
//   S    = new Sheet(Parent,D);
   Fade = 50;//FADE-1;
   for(Pos=0;Pos<FADE;Pos++) {
      Last_X      [Pos]    =D.W/2;
      Last_Y      [Pos]    =D.H/2;
   }
}
void Gantry_Class::Key(char K)
{
   switch(K) {
      case 'i':
         if(View_Scale<100)
            Change_Scale(View_Scale+1);
         break;
      case 'o':
            if(View_Scale>1)
               Change_Scale(View_Scale-1);
         break;
      case 'l':
               Change_Center(View_Center_Y,View_Center_X+100);
         break;
      case 'h':
               Change_Center(View_Center_Y,View_Center_X-100);
         break;
      case 'j':
               Change_Center(View_Center_Y-100,View_Center_X);
         break;
      case 'k':
               Change_Center(View_Center_Y+100,View_Center_X);
         break;
   }
}
void Gantry_Class::Set_Coords(Coords_Class* C)
{
   this->Coords        = C;
}
void Gantry_Class::Rti(void)
{
   while(1) {
      nanosleep   ( &Rti_Delay ,&Rti_Delay );
      Fade_Pixels ( Coords->Y  ,Coords->X  );
   }
}

void Gantry_Class::Change_Scale(float New_Scale)
{
   View_Scale=New_Scale;
   View_H=MAX_H/View_Scale;
   View_W=MAX_W/View_Scale;
   View_Max_X=View_Center_X+View_W/2;
   View_Min_X=View_Center_X-View_W/2;
   View_Max_Y=View_Center_Y+View_H/2;
   View_Min_Y=View_Center_Y-View_H/2;
   wclear(Win);
   Redraw_Box(Selected);
}
void Gantry_Class::Change_Center(int32_t New_Center_Y, int32_t New_Center_X)
{
   if(New_Center_Y<Coords->Max_Y && 
      New_Center_Y>Coords->Min_Y &&
      New_Center_X<Coords->Max_X &&
      New_Center_X>Coords->Min_X){
         View_Center_Y=New_Center_Y;
         View_Center_X=New_Center_X;
         View_Max_X=View_Center_X+View_W/2;
         View_Min_X=View_Center_X-View_W/2;
         View_Max_Y=View_Center_Y+View_H/2;
         View_Min_Y=View_Center_Y-View_H/2;
         wclear     ( Win      );
         Redraw_Box ( Selected );
   }
}

bool Gantry_Class::Absolute_X2Gantry(int32_t In_X,int32_t* Out_X)
{
   bool Ans;
   if(In_X>=View_Min_X && In_X<=View_Max_X) {
      *Out_X=1+((Dims.W-3)*(In_X-View_Min_X))/(View_Max_X-View_Min_X);
      Ans=true;
   }
   else
      Ans=false;
   return Ans;
}
bool Gantry_Class::Absolute_Y2Gantry(int32_t In_Y,int32_t* Out_Y)
{
   bool Ans;
   if(In_Y>=View_Min_Y && In_Y<=View_Max_Y) {
      *Out_Y=1+((Dims.H-3)*(In_Y-View_Min_Y))/(View_Max_Y-View_Min_Y);
      Ans=true;
   }
   else
      Ans=false;
   return Ans;
}


void Gantry_Class::Fade_Pixels(int32_t Y, int32_t X)
{
   uint16_t Pos,Color;
   int32_t Gantry_X,Gantry_Y;
   if(Absolute_Y2Gantry(Last_Y[0],&Gantry_Y) &&
      Absolute_X2Gantry(Last_X[0],&Gantry_X))
      mvwaddch (Win, Gantry_Y, Gantry_X, ('.' | COLOR_PAIR(0))); //borra la mas viejaa

   for(Pos=0;Pos<Fade;Pos++) {
      Last_X      [Pos]    =Last_X  [Pos+1];
      Last_Y      [Pos]    =Last_Y  [Pos+1];
      Color=MIN_COLOUR_PAIR+Pos*(MAX_COLOUR_PAIR-MIN_COLOUR_PAIR)/Fade;
      if(Absolute_Y2Gantry(Last_Y[Pos],&Gantry_Y) &&
         Absolute_X2Gantry(Last_X[Pos],&Gantry_X))
         mvwaddch (Win, Gantry_Y, Gantry_X, ' ' | COLOR_PAIR(Color));
   }
   wattron(Win,A_BOLD);
   Last_Y[Pos]=Y;
   Last_X[Pos]=X;
   if(Absolute_Y2Gantry(Last_Y[Pos],&Gantry_Y) &&
      Absolute_X2Gantry(Last_X[Pos],&Gantry_X))
      mvwaddch (Win, Gantry_Y,Gantry_X, 'O' | COLOR_PAIR(0));
//   Change_Center(Y,X);
   wattroff(Win,A_BOLD);
}
void Gantry_Class::Toogle_Pixel(int32_t Y, int32_t X)
{
   mvwaddch (Win ,Y ,X ,'X' | COLOR_PAIR(2));
}





