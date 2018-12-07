#include "inc_all.h"

Gantry_Class::Gantry_Class(Sheet* Parent,Dim D):Sheet(Parent,D)
{
   Path_X[0]=Path_Y[0]=Path_Z[0]=0;
}
void Gantry_Class::Grid(int16_t G)
{
   int32_t x,y;
   int32_t Win_Max_Y,Win_Max_X,Win_Min_Y,Win_Min_X;
   Absolute_Y2Gantry(Coords->Max_Y,&Win_Max_Y);
   Absolute_Y2Gantry(Coords->Min_Y,&Win_Min_Y);
   Absolute_X2Gantry(Coords->Max_X,&Win_Max_X);
   Absolute_X2Gantry(Coords->Min_X,&Win_Min_X);
   for(x=1;x<Dims.W-1;x++) {
      if(View_Max_Y>=Coords->Max_Y)
         mvwaddch (Win, Win_Max_Y, x, ('-' | COLOR_PAIR(0)));
      if(View_Min_Y<=Coords->Min_Y)
         mvwaddch (Win, Win_Min_Y, x, ('-' | COLOR_PAIR(0)));
      }
   for(y=1;y<Dims.H-1;y++) {
      if(View_Max_X>=Coords->Max_X)
         mvwaddch (Win, y, Win_Max_X, ('|' | COLOR_PAIR(0)));
      if(View_Min_X<=Coords->Min_X)
         mvwaddch (Win, y, Win_Min_X, ('|' | COLOR_PAIR(0)));
   }
}

void Gantry_Class::Key(int K)
{
   switch(K) {
      case 'i':
         Inc_Scale();
         break;
      case 'o':
         Dec_Scale();
         break;
      case 'l':
               Change_Center(View_Center_Y,View_Center_X+View_W/4);
         break;
      case 'h':
               Change_Center(View_Center_Y,View_Center_X-View_W/4);
         break;
      case 'j':
               Change_Center(View_Center_Y+View_H/4,View_Center_X);
         break;
      case 'k':
               Change_Center(View_Center_Y-View_H/4,View_Center_X);
         break;
      case 'p':
               Change_Center(Coords->Y,Coords->X);
         break;
      case 'P':
               Toogle_Auto_Center();
         break;
      case 'L':
               Clear_Path();
         break;
      case KEY_LEFT:
               Jog2Left();
         break;
      case KEY_RIGHT:
               Jog2Right();
         break;

      case KEY_UP:
               Jog2Up();
         break;
      case KEY_DOWN:
               Jog2Down();
         break;
      case 'u':
         Toogle_Full_Restore_Screen();
         Redraw_Path ( );
         break;
      case ' ':
              Goto_Jog();
         break;
   }
}
void Gantry_Class::Print_Scale(void)
{
   float StepsX=(float)Pixel_X_Distance()/X_SCALE;
   float StepsY=(float)Pixel_Y_Distance()/Y_SCALE;
   pthread_mutex_lock(&Main_Page->Print_Mutex);
      mvwprintw ( Win ,1 ,2 ,"X%07.3f [mm/pixel]" ,StepsX );
      mvwprintw ( Win ,2 ,2 ,"Y%07.3f [mm/pixel]" ,StepsY );
   pthread_mutex_unlock(&Main_Page->Print_Mutex);
}
int32_t Gantry_Class::Pixel_X_Distance(void)
{
  return (View_Max_X-View_Min_X)/(Dims.W-2);
}
int32_t Gantry_Class::Pixel_Y_Distance(void)
{
  return (View_Max_Y-View_Min_Y)/(Dims.H-2);
}
void Gantry_Class::Jog2Left(void)
{
   int32_t D=Pixel_X_Distance();
   if( (Coords->Jog_X-D) >= Coords->Min_X)   //View_Min_X)
      Coords->Jog_X -= D;
   Coords->Actual_Jog_X=(float)Coords->Jog_X/X_SCALE;
}
void Gantry_Class::Jog2Right(void)
{
   int32_t D=Pixel_X_Distance();
   if( (Coords->Jog_X+D) <= Coords->Max_X) //View_Max_X)
      Coords->Jog_X += D;
   Coords->Actual_Jog_X=(float)Coords->Jog_X/X_SCALE;
}
void Gantry_Class::Jog2Up(void)
{
   int32_t D=Pixel_Y_Distance();
   if( (Coords->Jog_Y+D)<= Coords->Max_Y) //View_Max_Y)
      Coords->Jog_Y+=D;
   Coords->Actual_Jog_Y=(float)Coords->Jog_Y/Y_SCALE;
}
void Gantry_Class::Jog2Down(void)
{
   int32_t D=Pixel_Y_Distance();
   if( (Coords->Jog_Y-D)>= Coords->Min_Y)//View_Min_Y)
      Coords->Jog_Y-=D;
   Coords->Actual_Jog_Y=(float)Coords->Jog_Y/Y_SCALE;
}

void Gantry_Class::Inc_Scale(void)
{
   if(Scale_Index>1)
      Scale_Index/=2;
   Change_Scale();
}
void Gantry_Class::Dec_Scale(void)
{
   if(Scale_Index<MAX_SCALE_INDEX)
      Scale_Index*=2;
   Change_Scale();
}
void Gantry_Class::Set_Coords(Coords_Class* C)
{
   this->Coords = C;
   Scale_Index  = MAX_SCALE_INDEX/1000;
   Change_Scale();
}
void Gantry_Class::Rti(void)
{
   while(1) {
      nanosleep       ( &Rti_Delay ,&Rti_Delay        );
      Draw_Path       ( Coords->Y,Coords->X,Coords->Z );
      Grid            ( 0                             );
      Print_Jog_Pixel (                               );
      Auto_Center     ( Coords->Y,Coords->X           );
   }
}
void Gantry_Class::Goto_Jog(void)
{
   if(Main_Page->Sender->Is_Running()==false) {
      char Buf[100];
      sprintf(Buf,"maxv %f %f %f\n",
            (float)(Coords->Speed_Limit*X_SCALE)/MICROSTEP,
            (float)(Coords->Speed_Limit*Y_SCALE)/MICROSTEP,
            (float)(Coords->Speed_Limit*Z_SCALE)/MICROSTEP
            );
      Main_Page->Serial->Send_And_Forget(Buf);

      sprintf(Buf,"acc %f %f %f\n",
            (float)(Coords->Acc*X_SCALE)/MICROSTEP,
            (float)(Coords->Acc*Y_SCALE)/MICROSTEP,
            (float)(Coords->Acc*Z_SCALE)/MICROSTEP
            );
      Main_Page->Serial->Send_And_Forget(Buf);

      sprintf(Buf,"dec %f %f %f\n",
            (float)(Coords->Dec*X_SCALE)/MICROSTEP,
            (float)(Coords->Dec*Y_SCALE)/MICROSTEP,
            (float)(Coords->Dec*Z_SCALE)/MICROSTEP
            );
      Main_Page->Serial->Send_And_Forget(Buf);

      sprintf(Buf,"goto %d %d %d\n",Coords->Jog_X,Coords->Jog_Y,Coords->Jog_Z);
      Main_Page->Serial->Send_And_Forget(Buf);
  }

}
void Gantry_Class::Jog2New_Zero(void)
{

}


void Gantry_Class::Change_Scale(void)
{
   uint32_t Max_H=(Coords->Max_Y-Coords->Min_Y);
   uint32_t Max_W=(Coords->Max_X-Coords->Min_X);

   View_H=(((Dims.H-2)*Scale_Index)>Max_H)?Max_H:(Dims.H-2)*Scale_Index;
   View_W=(((Dims.W-2)*Scale_Index)>Max_W)?Max_W:(Dims.W-2)*Scale_Index;
   View_Max_X = View_Center_X+View_W/2;
   View_Min_X = View_Center_X-View_W/2;
   View_Max_Y = View_Center_Y+View_H/2;
   View_Min_Y = View_Center_Y-View_H/2;
   Change_Center ( View_Center_Y,View_Center_X );
   wclear        ( Win                         );
   Redraw_Box    ( Selected                    );
   Redraw_Path   (                             );
   Print_Scale (          );
}
void Gantry_Class::Auto_Center(int32_t New_Center_Y, int32_t New_Center_X)
{
   static uint8_t Period=0;
   if(Auto_Center_Enabled==true)
      if(++Period>10) {
         Period=0;
         Change_Center(New_Center_Y,New_Center_X);
         Main_Page->Histo_Z->Change_Center(Coords->Z);
      }
}

void Gantry_Class::Toogle_Auto_Center(void)
{
   if(Auto_Center_Enabled==true)
      Auto_Center_Enabled=false;
   else
      Auto_Center_Enabled=true;
}


void Gantry_Class::Change_Center(int32_t New_Center_Y, int32_t New_Center_X)
{
   if((New_Center_Y+View_H/2)>=Coords->Max_Y)
      View_Center_Y = Coords->Max_Y-View_H/2;
   else
      if((New_Center_Y-View_H/2)<=Coords->Min_Y)
         View_Center_Y = Coords->Min_Y+View_H/2;
      else
         View_Center_Y = New_Center_Y;
   View_Max_Y    = View_Center_Y+View_H/2;
   View_Min_Y    = View_Center_Y-View_H/2;

   if((New_Center_X+View_W/2)>=Coords->Max_X)
      View_Center_X = Coords->Max_X-View_W/2;
   else
      if((New_Center_X-View_W/2)<=Coords->Min_X)
         View_Center_X = Coords->Min_X+View_W/2;
      else
         View_Center_X = New_Center_X;
   View_Max_X    = View_Center_X+View_W/2;
   View_Min_X    = View_Center_X-View_W/2;
   wclear      ( Win      );
   Redraw_Box  ( Selected );
   Redraw_Path (          );
}

bool Gantry_Class::Absolute_X2Gantry(int32_t In_X,int32_t* Out_X)
{
   bool Ans;
   if(In_X>=View_Min_X && In_X<=View_Max_X) {
      *Out_X=1+((Dims.W-3)*(In_X-View_Min_X))/View_W;
      Ans=true;
   }
   else {
      *Out_X = 100000;
      Ans    = false;
   }
   return Ans;
}
bool Gantry_Class::Absolute_Y2Gantry(int32_t In_Y,int32_t* Out_Y)
{
   bool Ans;
   if(In_Y>=View_Min_Y && In_Y<=View_Max_Y) {
      *Out_Y=Dims.H-(2+((Dims.H-3)*(In_Y-View_Min_Y))/View_H);
      Ans=true;
   }
   else {
      *Out_Y=100000;
      Ans=false;
   }
   return Ans;
}

uint8_t Gantry_Class::Color4Hight(int32_t Z)
{
   uint8_t Color;
   if(Z<=MIN_Z_TABLE) Color=MIN_COLOUR_PAIR;
   else
      if(Z>=MAX_Z_TABLE) Color=MAX_COLOUR_PAIR;
      else
         Color=MIN_COLOUR_PAIR+((Z-MIN_Z_TABLE)*(MAX_COLOUR_PAIR-MIN_COLOUR_PAIR))/(MAX_Z_TABLE-MIN_Z_TABLE);
   return Color;
}

void Gantry_Class::Clear_Path(void)
{
   wclear(Win);
   Redraw_Box(Selected);
   Path_X[0]=Path_X[Path_Index];
   Path_Y[0]=Path_Y[Path_Index];
   Path_Z[0]=Path_Z[Path_Index];
   Path_Index=0;
}
void Gantry_Class::Redraw_Path(void)
{
   uint32_t i;
   uint32_t End=Path_Index;
   uint32_t Begin=End>Main_Page->Coords->Plot_Limit?End-Main_Page->Coords->Plot_Limit:0;
   int32_t Gantry_X,Gantry_Y;
   wclear(Win);
   Redraw_Box(Selected);
   pthread_mutex_lock(&Main_Page->Print_Mutex);
      for(i=Begin;i<End;i++)
         if(Absolute_Y2Gantry(Path_Y[i],&Gantry_Y) &&
            Absolute_X2Gantry(Path_X[i],&Gantry_X))
            mvwaddch (Win, Gantry_Y, Gantry_X, '.' | COLOR_PAIR(Color4Hight(Path_Z[i])));
   pthread_mutex_unlock(&Main_Page->Print_Mutex);
}
void Gantry_Class::Draw_Path ( int32_t Y, int32_t X, int32_t Z )
{
   uint16_t Color;
   int32_t Gantry_X,Gantry_Y;
   pthread_mutex_lock(&Main_Page->Print_Mutex);
      if(Path_Y[Path_Index]!=Y || Path_Y[Path_Index]!=X || Path_Y[Path_Index]!=Z) {
         if(Absolute_Y2Gantry(Path_Y[Path_Index],&Gantry_Y) &&
            Absolute_X2Gantry(Path_X[Path_Index],&Gantry_X))
            mvwaddch (Win, Gantry_Y, Gantry_X, '.' | COLOR_PAIR(Color4Hight(Z)));
         Path_Index++;
         Path_Y[Path_Index] = Y;
         Path_X[Path_Index] = X;
         Path_Z[Path_Index] = Z;
         wattron(Win,A_BOLD);
         if(Absolute_Y2Gantry(Path_Y[Path_Index],&Gantry_Y) &&
            Absolute_X2Gantry(Path_X[Path_Index],&Gantry_X))
            mvwaddch (Win, Gantry_Y,Gantry_X, 'O' | COLOR_PAIR(0));
         wattroff(Win,A_BOLD);
   }
   pthread_mutex_unlock(&Main_Page->Print_Mutex);
}
void Gantry_Class::Toogle_Pixel(int32_t Y, int32_t X)
{
   pthread_mutex_lock(&Main_Page->Print_Mutex);
      mvwaddch (Win ,Y ,X ,'X' | COLOR_PAIR(2));
   pthread_mutex_unlock(&Main_Page->Print_Mutex);
}

void Gantry_Class::Print_Jog_Pixel(void)
{
   static int32_t Gantry_X,Gantry_Y;
   pthread_mutex_lock(&Main_Page->Print_Mutex);
      mvwaddch (Win ,Gantry_Y ,Gantry_X ,' ' | COLOR_PAIR(0));
      Absolute_Y2Gantry(Coords->Jog_Y,&Gantry_Y);
      Absolute_X2Gantry(Coords->Jog_X,&Gantry_X);
      mvwaddch (Win ,Gantry_Y ,Gantry_X ,'X' | COLOR_PAIR(2));
   //   mvwaddch (Win ,Zero_Gantry_Y ,Zero_Gantry_X ,' ' | COLOR_PAIR(0));
      int32_t Zero_Gantry_X,Zero_Gantry_Y;
      Absolute_Y2Gantry(0,&Zero_Gantry_Y);
      Absolute_X2Gantry(0,&Zero_Gantry_X);
      mvwaddch (Win ,Zero_Gantry_Y ,Zero_Gantry_X ,'+' | COLOR_PAIR(5));
   pthread_mutex_unlock(&Main_Page->Print_Mutex);
}
