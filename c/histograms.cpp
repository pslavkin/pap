#include "inc_all.h"

//----------------------------------------------------------------------------------------------------
Histo_Class::Histo_Class(Sheet* Parent,Dim D ,int32_t Max_Value, int32_t Min_Value, int32_t Value) : Sheet (Parent,D)
{
//   this->S         = new Sheet(Parent,D);
   this->Max_Value = Max_Value;
   this->Min_Value = Min_Value;
   this->Value     = Value;
};
//void Histo_Class::Set_V_Inverted_Rule_Value(int32_t Value)
//{
//   uint16_t i;
//   uint16_t Height = Dims.H-2;
//   uint32_t Length = Height-(((Value-Min_Value)*Height)/(Max_Value-Min_Value));
//   uint8_t Color;
//   Color=Main_Page->Gantry_XY->Color4Hight(Value);
//   for(i=0;i<Height;i++)
//      mvwaddch(Win,i+1,2,i>Length?('.'|COLOR_PAIR(0)):('.'|COLOR_PAIR(Color)));
//}
void Histo_Class::Set_V_Inverted_Rule_Value(int32_t Value)
{

   uint16_t i;
   uint16_t Height = Dims.H-2;
   uint32_t Length = Height-(((Value-Min_Value)*Height)/(Max_Value-Min_Value));
   uint8_t Color;
   int32_t H2Value;
   Color=Main_Page->Gantry_XY->Color4Hight(Value);
   for(i=0;i<Height;i++) {
      H2Value=Min_Value+((Height-i)*(Max_Value-Min_Value)/Height);
      Color=Main_Page->Gantry_XY->Color4Hight(H2Value);
      if(i>Length)
         mvwaddch(Win,i+1,2,' '|COLOR_PAIR(Color));
      else if(i==Length) {
         wattron(Win,A_BOLD);
         mvwaddch(Win,i+1,2,'0'|COLOR_PAIR(Color));
         wattroff(Win,A_BOLD);
      }
      else
         mvwaddch(Win,i+1,2,'|'|COLOR_PAIR(Color));
   }
}
void Histo_Class::Rti(void)
{
   while(1) {
      nanosleep     ( &Rti_Delay,&Rti_Delay );
      Set_V_Inverted_Rule_Value(Coords->Z);
   }
}
void Histo_Class::Set_Coords(Coords_Class* C)
{
   this->Coords = C;
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
               To_Up();
         break;
      case KEY_DOWN:
               To_Down();
         break;
      case 'u':
         Toogle_Full_Restore_Screen();
         break;
   }
}

