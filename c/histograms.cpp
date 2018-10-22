#include "inc_all.h"

//----------------------------------------------------------------------------------------------------
Histo_Class::Histo_Class(Sheet* Parent,Dim D ,uint32_t Max_Value, uint32_t Value)
{
   this->S         = new Sheet(Parent,D);
   this->Max_Value = Max_Value;
   this->Value     = Value;
   Set_V_Inverted_Rule_Value(Value);
};
void Histo_Class::Set_V_Inverted_Rule_Value(uint32_t Value)
{
   uint16_t i;
   uint16_t Height=S->Dims.H-2;
   Value= ( Value*Height )/Max_Value;
   for(i=0;i<Height;i++)
      mvwaddch(S->Win,Height-i,2,Value<(Height-i)?('.'|COLOR_PAIR(0)):('.'|COLOR_PAIR(MAX_COLOUR_PAIR)));
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
   this->Coords=C;
   this->Coords->Max_Z=Max_Value;
   this->Coords->Min_Z=0;
}

