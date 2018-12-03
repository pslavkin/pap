#include "inc_all.h"

Coords_Class::Coords_Class(Sheet* Parent,Dim D) : Sheet(Parent,D)
{
//   S = new Sheet(Parent,D);
   mvwprintw(Win ,1 ,16 ,"X           Y           Z        Speed    |   Accel      Decel");
   mvwprintw(Win ,2 ,2 ,"Actual |");
   mvwprintw(Win ,3 ,2 ,"Jog    |");
   X              = 0       ;
   Y              = 0       ;
   Z              = 0       ;
   Actual_X       = 0       ;
   Actual_Y       = 0       ;
   Actual_Z       = 0       ;
   Speed_X        = 0       ;
   Speed_Y        = 0       ;
   Speed_Z        = 0       ;
   Actual_Speed_X = 0       ;
   Actual_Speed_Y = 0       ;
   Actual_Speed_Z = 0       ;
   Speed          = 0       ;
   Jog_Speed      = 10      ;
   Jog_X          = 0       ;
   Jog_Y          = 0       ;
   Jog_Z          = 0       ;
   Actual_Jog_X   = 0       ;
   Actual_Jog_Y   = 0       ;
   Actual_Jog_Z   = 0       ;
   Max_X          = 2097152 ;
   Max_Y          = 2097152 ;
   Max_Z          = 2097152 ;
   Min_X          = -2097152;
   Min_Y          = -2097152;
   Min_Z          = -2097152;
   Max_Acc      = 1000      ;
   Max_Dec      = 1000      ;
   Speed_Scale  = 50        ;
}
void Coords_Class::Rti(void)
{
   while(1) {
      nanosleep     ( &Rti_Delay,&Rti_Delay );
      Write();
   }
}
void Coords_Class::Write(void)
{
   pthread_mutex_lock(&Main_Page->Print_Mutex);
      wattron(Win,A_BOLD);
      mvwprintw(Win,2,11,"%+011.3f %+011.3f %+011.3f %010.3f | %010.3f %010.3f",
                Actual_X,Actual_Y,Actual_Z,Actual_Speed,Max_Acc,Max_Dec);
      wattroff(Win,A_BOLD);
      mvwprintw(Win,3,11,"%+011.3f %+011.3f %+011.3f %010.3f | Speed % = %0.3d",
            Actual_Jog_X,Actual_Jog_Y,Actual_Jog_Z,Jog_Speed,Speed_Scale);
   pthread_mutex_unlock(&Main_Page->Print_Mutex);
}

void Coords_Class::Jog2Machine(void)
{
   Jog_Y=Y;
   Jog_X=X;
   Jog_Z=Z;
   Actual_Jog_Y=Actual_Y;
   Actual_Jog_X=Actual_X;
   Actual_Jog_Z=Actual_Z;
}
void Coords_Class::Machine2Coords(int32_t X, int32_t Y,int32_t Z,
                                  float Speed_X, float Speed_Y, float Speed_Z)
{
   Actual_Y       = (float)Y/Y_SCALE;
   Actual_X       = (float)X/X_SCALE;
   Actual_Z       = (float)Z/Z_SCALE;
   Actual_Speed_Y = (float)((float)Speed_Y*MICROSTEP)/Y_SCALE;
   Actual_Speed_X = (float)((float)Speed_X*MICROSTEP)/X_SCALE;
   Actual_Speed_Z = (float)((float)Speed_Z*MICROSTEP)/Z_SCALE;
   Actual_Speed   = sqrt( Actual_Speed_Y*Actual_Speed_Y +\
                          Actual_Speed_X*Actual_Speed_X+\
                          Actual_Speed_Z*Actual_Speed_Z);
   this->X       = X;
   this->Y       = Y;
   this->Z       = Z;
   this->Speed_Y = Speed_Y;
   this->Speed_X = Speed_X;
   this->Speed_Z = Speed_Z;
   this->Speed   = sqrt(Speed_X*Speed_X+Speed_Y*Speed_Y+Speed_Z*Speed_Z);
}

void Coords_Class::Inc_Speed_Scale(void)
{
   if(Speed_Scale<=90)
      Speed_Scale+=10;
}
void Coords_Class::Dec_Speed_Scale(void)
{
   if(Speed_Scale>=10)
      Speed_Scale-=10;
}
void Coords_Class::Inc_Jog_Speed(void)
{
   if(Jog_Speed<10)
      Jog_Speed++;
   else {
      if((Jog_Speed+10)<=MAX_JOG_SPEED)
         Jog_Speed+=10;
   }
}
void Coords_Class::Dec_Jog_Speed(void)
{
   if(Jog_Speed<=10) {
      if(Jog_Speed>0)
         Jog_Speed--;
   }
   else
      Jog_Speed-=10;
}

void Coords_Class::Key(int K)
{
   switch(K) {
      case '+':
         Inc_Jog_Speed();
         break;
      case '-':
         Dec_Jog_Speed();
         break;
      case KEY_LEFT:
         break;
      case KEY_RIGHT:
         break;
      case KEY_UP:
         Inc_Speed_Scale();
         break;
      case KEY_DOWN:
         Dec_Speed_Scale();
         break;
      case 'u':
         Toogle_Full_Restore_Screen();
         break;
   }
}
