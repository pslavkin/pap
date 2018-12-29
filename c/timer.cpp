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
   Serial_Rti = std::thread (&Serial_Manager_Class::Rti,S);
}
void Timer_Class::Set_Coords_Rti  ( Coords_Class* C  )
{
   SRti = std::thread (&Coords_Class::Rti,C);
}
void Timer_Class::Set_Sender_Rti  ( Sender_Class* S  )
{
   Sender_Rti = std::thread (&Sender_Class::Rti,S);
}
void Timer_Class::Set_TresD_Rti  ( TresD_Class* TresD  )
{
   TresD_Rti = std::thread (&TresD_Class::Rti,TresD);
}
void Timer_Class::Set_Screen_Update_Rti( Screen_Update_Class* SUpdate  )
{
   SUpdate_Rti = std::thread (&Screen_Update_Class::Rti,SUpdate);
}
void Timer_Class::Set_Openmv_Rti  ( Openmv_Class* Openmv  )
{
   Openmv_Rti = std::thread (&Openmv_Class::Rti,Openmv);
}
void Timer_Class::Set_Fiducial_Rti  ( Fiducial_Class* Fiducial  )
{
   Fiducial_Rti = std::thread (&Fiducial_Class::Rti,Fiducial);
}

