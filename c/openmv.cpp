#include "inc_all.h"

Openmv_Class::Openmv_Class (Sheet* Parent,Dim D):Sheet(Parent,D)
{
   scrollok ( Sub_Win, TRUE );
   Port_Number=1;
};

void Openmv_Class::Serial_Bloked_Get_Line(char* Buf,uint8_t Size)
{
   uint8_t Index = 0;
   unsigned char  Data;
   while(1) {
      while ( Get_Byte(Port_Number,&Data )!=1)
         nanosleep ( &Rti_Delay,&Rti_Delay );

      if ( (Data == '\r' )|| (Data == '\n') || (Data == 0x1b)) {
         break;
      }
      if(Index < Size) {
         Buf[Index] = Data;
         Index++;
      }
   }
   Buf[Index] = 0;
}
//-----------------------------------------------------------------------
void Openmv_Class::Rti(void)
{
   char        Buf[MAX_ANS_SIZE];
   while(OpenComport(Port_Number,115200)==1) {
      pthread_mutex_lock(&Main_Page->Print_Mutex);
         mvwprintw(Sub_Win,0,0,"camera port %d error\n",Port_Number);
         Touch_Win();
      pthread_mutex_unlock(&Main_Page->Print_Mutex);
      nanosleep ( &Open_Port_Delay,&Open_Port_Delay );
   }
   wprintw(Sub_Win,"port %d opened\n",Port_Number);
   while(1){
      Serial_Bloked_Get_Line(Buf,sizeof(Buf));
      sscanf(Buf,"%hhu %hhu %f %hhu",&Camera_X,&Camera_Y,&Rotation,&Id);
      Diff_X=Camera_X-(Camera_Max_X/2);
      Diff_Y=Camera_Y-(Camera_Max_Y/2);
      Next_Move_X=Main_Page->Coords->Actual_X+Diff_X/2;
      Next_Move_Y=Main_Page->Coords->Actual_Y-Diff_Y/2;
      Print_Camera_Pixel();
      Touch_Win();
   }
}

void Openmv_Class::Key(int K)
{
   switch(K) {
      case KEY_LEFT:
         break;
      case KEY_RIGHT:
         break;
      case KEY_UP:
         break;
      case KEY_DOWN:
         break;
      case 'a':
         Move2Center();
         break;
      case 'b':
            Main_Page->TresD->Gcode2Matrix();
            Main_Page->TresD->Rotate(Rotation);
         break;
      case 'u':
         Toogle_Full_Restore_Screen();
         break;
   }
}
void Openmv_Class::Move2Center(void)
{
   char Buf[100];
    if(Main_Page->Coords->Speed==0) {
      if(Diff_X!=0 || Diff_Y!=0) {
         sprintf(Buf,"GL A G1 X%f Y%f F%d\n",Next_Move_X,Next_Move_Y,Main_Page->Coords->Speed_Limit*60);
         Main_Page->Serial->Send_And_Forget(Buf);
      }
   }
}
uint32_t Openmv_Class::Absolute_Y2Gantry(uint8_t Y)
{
   return (Y*(Dims.H-4))/Camera_Max_Y;
}
uint32_t Openmv_Class::Absolute_X2Gantry(uint8_t X)
{
   return (X*(Dims.W-4))/Camera_Max_X;
}
void Openmv_Class::Print_Camera_Pixel(void)
{
   static int32_t Gantry_X,Gantry_Y;
   int32_t Zero_Gantry_X,Zero_Gantry_Y;
   pthread_mutex_lock(&Main_Page->Print_Mutex);
      mvwprintw(Sub_Win,0,0,"x=%hhu y=%hhu r=%4.2f id=%hhu NextX=%4.2f NextY=%4.2f\n",
            Camera_X,Camera_Y,Rotation,Id,Next_Move_X,Next_Move_Y);
      mvwaddch (Sub_Win ,Absolute_Y2Gantry(Camera_Max_Y/2) ,Absolute_X2Gantry(Camera_Max_X/2) ,'+' | COLOR_PAIR(5));

      mvwaddch (Sub_Win ,Gantry_Y ,Gantry_X ,' ' | COLOR_PAIR(0)); //borra el anterior
      Gantry_Y=Absolute_Y2Gantry(Camera_Y);
      Gantry_X=Absolute_X2Gantry(Camera_X);
      mvwaddch (Sub_Win ,Gantry_Y ,Gantry_X ,'X' | COLOR_PAIR(2));
   pthread_mutex_unlock(&Main_Page->Print_Mutex);
}

