#include "inc_all.h"

Coords_Class::Coords_Class(Sheet* Parent,Dim D) : Sheet(Parent,D)
{
//   S = new Sheet(Parent,D);
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
   Jog_X          = 0       ;
   Jog_Y          = 0       ;
   Jog_Z          = 0       ;
   Actual_Jog_X   = 0       ;
   Actual_Jog_Y   = 0       ;
   Actual_Jog_Z   = 0       ;
   Max_X          = 2097152 ;
   Max_Y          = 2097152 ;
   Max_Z          = MAX_Z_TABLE; //2097152 ;
   Min_X          = -2097152;
   Min_Y          = -2097152;
   Min_Z          = MIN_Z_TABLE;//-2097152;
   Acc      = 1000   ;
   Dec      = 1000   ;
   Speed_Limit  = 10 ;
   Speed_Scale  = 1.0 ;
   Plot_Limit  = 500;
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
      mvwprintw(Win ,1 , 2 ,"Plot  |   Acc/Dec  |        X           Y           Z    |   Speed");
      mvwprintw(Win,2, 1,"%6d | %010.3f |",Plot_Limit,Acc);
      wattron(Win,A_BOLD);
      mvwprintw(Win,2,23,"%+011.3f %+011.3f %+011.3f",Actual_X,Actual_Y,Actual_Z);
      wattroff(Win,A_BOLD);
      mvwprintw(Win,2,59,"| %08.3f", Actual_Speed*60);
      mvwprintw(Win,3, 2,"%5d | %010.3f | %+011.3f %+011.3f %+011.3f | %4d/%3.1f",
            Plot_Lines,Dec,Actual_Jog_X,Actual_Jog_Y,Actual_Jog_Z,Speed_Limit*60,(float)Speed_Scale/10);
   pthread_mutex_unlock(&Main_Page->Print_Mutex);
}

void Coords_Class::Reset_Jog_XY(void)
{
   Jog_Y=0;
   Jog_X=0;
   Actual_Jog_Y=0;
   Actual_Jog_X=0;
}
void Coords_Class::Reset_Jog_Z(void)
{
   Jog_Z=0;
   Actual_Jog_Z=0;
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

void Coords_Class::Send_Acc_Dec2Controller(float Acc, float Dec)
{
   char Buf[100];
   sprintf(Buf,"ramps %d %d\n",(int)Acc,(int)Dec);
   Main_Page->Serial->Send_And_Forget(Buf);
}
void Coords_Class::Inc_Acc(void) 
{
   Send_Acc_Dec2Controller((Acc+ACC_STEP)<MAX_ACC?(Acc+ACC_STEP):MAX_ACC,Dec);
}
void Coords_Class::Dec_Acc(void)
{
   Send_Acc_Dec2Controller((Acc-ACC_STEP)>MIN_ACC?(Acc-ACC_STEP):MIN_ACC,Dec);
}
void Coords_Class::Inc_Dec(void)
{
   Send_Acc_Dec2Controller(Acc,(Dec+ACC_STEP)<MAX_DEC?(Dec+ACC_STEP):MAX_DEC);
}
void Coords_Class::Dec_Dec(void)
{
   Send_Acc_Dec2Controller(Acc,(Dec-ACC_STEP)>MIN_DEC?(Dec-ACC_STEP):MIN_DEC);
}
void Coords_Class::Dec_Plot_Limit(void)
{
   uint32_t Last_Plot_Limit=Plot_Limit;
   if(Plot_Limit>PLOT_STEP)
      Plot_Limit-=PLOT_STEP;
   else Plot_Limit=1;
   if(Plot_Limit!=Last_Plot_Limit)
      Main_Page->Gantry_XY->Redraw_Path();
}
void Coords_Class::Inc_Plot_Limit(void)
{
   uint32_t Last_Plot_Limit=Plot_Limit;
   if(Plot_Limit==1) 
      Plot_Limit=PLOT_STEP;
   else
      if((Plot_Limit+PLOT_STEP)<=PLOT_MAX) 
         Plot_Limit+=PLOT_STEP;
   if(Plot_Limit!=Last_Plot_Limit)
      Main_Page->Gantry_XY->Redraw_Path();
}
void Coords_Class::Send_Speed_Limit2Controller(uint16_t Limit)
{
   char Buf[100];
   sprintf(Buf,"ls %d\n",Limit);
   Main_Page->Serial->Send_And_Forget(Buf);
}
void Coords_Class::Inc_Speed_Limit(void)
{
   if(Speed_Limit<MAX_SPEED_LIMIT) {
      Send_Speed_Limit2Controller(Speed_Limit+1);
   }
}
void Coords_Class::Dec_Speed_Limit(void)
{
   if(Speed_Limit>1) {
      Send_Speed_Limit2Controller(Speed_Limit-1);
   }
}
void Coords_Class::Send_Speed_Scale2Controller(uint8_t Scale)
{
   char Buf[100];
   sprintf(Buf,"ss %d\n",Scale);
   Main_Page->Serial->Send_And_Forget(Buf);
}
void Coords_Class::Inc_Speed_Scale(void)
{
   if(Speed_Scale<MAX_SPEED_SCALE) {
      Send_Speed_Scale2Controller(Speed_Scale+1);
   }
}
void Coords_Class::Dec_Speed_Scale(void)
{
   if(Speed_Scale>1) {
      Send_Speed_Scale2Controller(Speed_Scale-1);
   }
}

void Coords_Class::Key(int K)
{
   switch(K) {
      case '+':
         Inc_Acc();
         break;
      case '=':
         Dec_Acc();
         break;
      case '_':
         Inc_Dec();
         break;
      case '-':
         Dec_Dec();
         break;
      case ')':
         Inc_Plot_Limit();
         break;
      case '0':
         Dec_Plot_Limit();
         break;
      case KEY_LEFT:
         Dec_Speed_Scale();
         break;
      case KEY_RIGHT:
         Inc_Speed_Scale();
         break;
      case KEY_UP:
         Inc_Speed_Limit();
         break;
      case KEY_DOWN:
         Dec_Speed_Limit();
         break;
      case 'u':
         Toogle_Full_Restore_Screen();
         break;
   }
}
