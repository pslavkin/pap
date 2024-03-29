#include "inc_all.h"

//----------------------------------------------------------------------------------------------------
Histo_Class::Histo_Class(Sheet* Parent,Dim D ,int32_t Max_Value, int32_t Min_Value, int32_t Value) : Sheet (Parent,D)
{
   this->Max_Value = Max_Value;
   this->Min_Value = Min_Value;
   this->Value     = Value;
};
void Histo_Class::Inc_Scale(void)
{
   if(Scale_Index>1)
      Scale_Index/=2;
   Change_Scale();
}
void Histo_Class::Dec_Scale(void)
{
   if(Scale_Index<MAX_Z_SCALE_INDEX)
      Scale_Index*=2;
   Change_Scale();
}
void Histo_Class::Change_Scale(void)
{
   uint32_t Max_H=(Coords->Max_Z-Coords->Min_Z);

   View_H=(((Dims.H-2)*Scale_Index)>Max_H)?Max_H:(Dims.H-2)*Scale_Index;
   View_Max_Z = View_Center_Z+View_H/2;
   View_Min_Z = View_Center_Z-View_H/2;
   Change_Center ( View_Center_Z );
   wclear        ( Win           );
   Redraw_Box    ( Selected      );
   Print_Scale();
}
void Histo_Class::Change_Center(int32_t New_Center_Z)
{
   int32_t Last_Center=View_Center_Z;
      if((New_Center_Z+View_H/2)>=Coords->Max_Z)
         View_Center_Z = Coords->Max_Z-View_H/2;
      else
         if((New_Center_Z-View_H/2)<=Coords->Min_Z)
            View_Center_Z = Coords->Min_Z+View_H/2;
         else
            View_Center_Z = New_Center_Z;
      if(Last_Center!=View_Center_Z) {
         View_Max_Z    = View_Center_Z+View_H/2;
         View_Min_Z    = View_Center_Z-View_H/2;
         wclear      ( Win      );
         Redraw_Box  ( Selected );
      }
}
int32_t Histo_Class::Histo_2ZAbsolute(uint8_t Histo_Z)
{
   return  ((Dims.H-Histo_Z-2)*View_H)/(Dims.H-3)+View_Min_Z;
}
int32_t Histo_Class::Absolute_Z2Histo(int32_t In_Z)
{
   if(In_Z>=View_Min_Z && In_Z<=View_Max_Z)
      return Dims.H-(2+((Dims.H-3)*(In_Z-View_Min_Z))/View_H);
   else 
      if(In_Z<View_Min_Z) return Dims.H+1;
      else
         return -1;
}
void Histo_Class::Set_V_Inverted_Rule_Value(int32_t Value)
{
   uint16_t i,w                                ;
   uint16_t Height = Dims.H-1                  ;
   int32_t  Length = Absolute_Z2Histo ( Value );
   uint8_t  Color                              ;
   Color=Main_Page->Gantry_XY->Color4Hight(Value);
   pthread_mutex_lock(&Main_Page->Print_Mutex);
      for(i=1;i<Height;i++) {
         Color=Main_Page->Gantry_XY->Color4Hight(Histo_2ZAbsolute(i));
         if(i>Length)
            for(w=1;w<Dims.W-1;w++)
               mvwaddch(Win,i,w,' '|COLOR_PAIR(Color));
         else if(i==Length) {
            wattron(Win,A_BOLD);
            for(w=1;w<Dims.W-1;w++)
               mvwaddch(Win,i,w,'0'|COLOR_PAIR(Color));
            wattroff(Win,A_BOLD);
         }
         else
            for(w=1;w<Dims.W-1;w++)
               mvwaddch(Win,i,w,'.'|COLOR_PAIR(Color));
      }
   pthread_mutex_unlock(&Main_Page->Print_Mutex);
}
void Histo_Class::Rti(void)
{
   while(1) {
      nanosleep     ( &Rti_Delay,&Rti_Delay );
      Set_V_Inverted_Rule_Value(Coords->Z);
      Print_Jog_Pixel();
      Auto_Center     ( Coords->Z);
   }
}
void Histo_Class::Set_Coords(Coords_Class* C)
{
   this->Coords = C;
   Scale_Index  = MAX_Z_SCALE_INDEX;
   Change_Scale();
}
float Histo_Class::Pixel_Z_Distance(void)
{
 return (View_Max_Z-View_Min_Z)/(Dims.H-2);
}
void Histo_Class::Jog2Up(void)
{
   int32_t D=Pixel_Z_Distance();
   if( (Coords->Jog_Z-D) >= Coords->Min_Z)
      Coords->Jog_Z -= D;
   Coords->Actual_Jog_Z=(float)Coords->Jog_Z/Z_SCALE;
}
void Histo_Class::Jog2Down(void)
{
   int32_t D=Pixel_Z_Distance();
   if( (Coords->Jog_Z+D) <= Coords->Max_Z)
      Coords->Jog_Z += D;
   Coords->Actual_Jog_Z=(float)Coords->Jog_Z/Z_SCALE;
}
void Histo_Class::Key(int K)
{
   switch(K) {
      case KEY_LEFT:
               To_Left();
         break;
      case KEY_RIGHT:
               To_Right();
         break;
      case KEY_UP:
               Jog2Down();
               Goto_Jog_Z();
         break;
      case KEY_DOWN:
               Jog2Up();
               Goto_Jog_Z();
         break;
      case 'j':
               Change_Center(View_Center_Z+View_H/4);
         break;
      case 'k':
               Change_Center(View_Center_Z-View_H/4);
         break;
      case 'i':
         Inc_Scale();
         break;
      case 'o':
         Dec_Scale();
         break;
      case ' ':
               Goto_Jog_Z();
         break;
      case 'p':
         Change_Center(Coords->Z);
         break;
      case 'P':
         Toogle_Auto_Center();
         break;
      case 'Z':
         Jog2New_Z_Zero();
         break;
      case 'm':
         Coords->Jog_Z2Machine();
         break;
      case 'u':
         Toogle_Full_Restore_Screen();
         break;
   }
}
void Histo_Class::Print_Jog_Pixel(void)
{
   static int32_t Gantry_Z;
   uint8_t w;
   pthread_mutex_lock(&Main_Page->Print_Mutex);
      mvwaddch (Win ,Gantry_Z ,1 ,' ' | COLOR_PAIR(0));
      Gantry_Z=Absolute_Z2Histo(Coords->Jog_Z);
         for(w=1;w<Dims.W-1;w++)
            mvwaddch (Win ,Gantry_Z ,w ,'X' | COLOR_PAIR(2));
      int32_t Zero_Histo_Z;
      Zero_Histo_Z=Absolute_Z2Histo(0);
         for(w=1;w<Dims.W-1;w++)
            mvwaddch (Win ,Zero_Histo_Z ,w ,'+' | COLOR_PAIR(5));
   pthread_mutex_unlock(&Main_Page->Print_Mutex);
}
void Histo_Class::Goto_Jog_Z(void)
{
   if(Main_Page->Sender->Is_Running()==false) {
      char Buf[100];
      sprintf(Buf,"GL A G1 Z%f F%d\n",Coords->Actual_Jog_Z,Coords->Speed_Limit*60);
      Main_Page->Serial->Send_And_Forget(Buf);
  }

}
void Histo_Class::Auto_Center(int32_t New_Center_Z)
{
   static uint8_t Period=0;
   if(Auto_Center_Enabled==true)
      if(++Period>10) {
         Period=0;
         Change_Center(Coords->Z);
      }
}
void Histo_Class::Toogle_Auto_Center(void)
{
   if(Auto_Center_Enabled==true)
      Auto_Center_Enabled=false;
   else
      Auto_Center_Enabled=true;
}
void Histo_Class::Print_Scale(void)
{
   float StepsZ=Main_Page->Histo_Z->Pixel_Z_Distance()/Z_SCALE;
   pthread_mutex_lock(&Main_Page->Print_Mutex);
      mvwprintw ( Main_Page->Gantry_XY->Win ,3 ,2 ,"Z%07.3f [mm/pixel]" ,StepsZ );
   pthread_mutex_unlock(&Main_Page->Print_Mutex);
}
void Histo_Class::Jog2New_Z_Zero(void)
{
   char Buf[100];
   sprintf(Buf,"pos %d %d 0\n",Main_Page->Coords->X,Main_Page->Coords->Y); 
   Main_Page->Serial->Send_And_Forget(Buf);
   Coords->Reset_Jog_Z();
   sprintf(Buf,"rstz\n");
   Main_Page->Serial->Send_And_Forget(Buf);
}

