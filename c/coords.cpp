#include "inc_all.h"

Coords_Class::Coords_Class(Sheet* Parent,Dim D)
{
   S = new Sheet(Parent,D);
   mvwprintw(S->Win ,1 ,7 ,"X           Y           Z        Speed");
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
   Jog_Speed      = 600     ;
   Jog_X          = 0       ;
   Jog_Y          = 0       ;
   Jog_Z          = 0       ;
   Actual_Jog_X   = 0       ;
   Actual_Jog_Y   = 0       ;
   Actual_Jog_Z   = 0       ;
   Max_X          = 2097152 ;
   Max_Y          = 2097152 ;
// Max_Z     = 2097152 ;
   Max_Z          = 100000  ;
   Min_X          = -2097152;
   Min_Y          = -2097152;
// Min_Z     = -2097152;
   Min_Z          = -100000 ;
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
      wattron(S->Win,A_BOLD);
      mvwprintw(S->Win,2,2,"%+011.3f %+011.3f %+011.3f %010.3f",Actual_X,Actual_Y,Actual_Z,Actual_Speed);
      wattroff(S->Win,A_BOLD);
      wcolor_set(S->Win, 2,NULL);
      mvwprintw(S->Win,3,2,"%+011.3f %+011.3f %+011.3f %010.3f",Actual_Jog_X,Actual_Jog_Y,Actual_Jog_Z,Jog_Speed);
      wcolor_set(S->Win, 0,NULL);
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

void Coords_Class::Inc_Jog_Speed(void)
{
   char Buf[100],Len;
   if((Jog_Speed+100)<MAX_JOG_SPEED)
      Jog_Speed+=100;
   Len=sprintf(Buf,"F %f\r",Jog_Speed);
   Main_Page->Serial->serial_send(Buf,Len);
}
void Coords_Class::Dec_Jog_Speed(void)
{
   char Buf[100],Len;
   if(Jog_Speed>100)
      Jog_Speed-=100;
   Len=sprintf(Buf,"F %f\r",Jog_Speed);
   Main_Page->Serial->serial_send(Buf,Len);
}
