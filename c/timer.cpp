#include "inc_all.h"


Timer_Class::Timer_Class (void)
{
}
void Timer_Class::Set_Gantry_Rti ( Gantry_Class* G )
{
   GRti = std::thread (&Gantry_Class::Rti,G);
}
void Timer_Class::Set_Histo_Rti  ( Histo_Class* H  )
{
   HRti = std::thread (&Histo_Class::Rti,H);
}
void Timer_Class::Set_Serial_Manager_Rti  ( Serial_Manager_Class* S  )
{
   SRti = std::thread (&Serial_Manager_Class::Rti,S);
}
void Timer_Class::Set_Coords_Rti  ( Coords_Class* C  )
{
   SRti = std::thread (&Coords_Class::Rti,C);
}


