#include "inc_all.h"

//----------------------------------------------------------------------------------------------------
Main_Page_Class::Main_Page_Class (void)
{
   pthread_mutex_init(&Print_Mutex,NULL);
   pthread_mutex_init(&Serial_Mutex,NULL); //ara repartir el acceso al puerto serie..
}

void Main_Page_Class::Init (WINDOW* w)
{
   Dim Dim_Main_Page(0, 0,getmaxy(w),getmaxx(w),"PaP");
   Main=new Sheet(w,Dim_Main_Page);

   Dim Dim_Gantry(5, 47,22,50,"XY");
   Gantry_XY=new Gantry_Class(Main,Dim_Gantry);

   Dim Dim_Histo(5, 40,22, 7,"Z");
   Histo_Z=new Histo_Class(Main,Dim_Histo,MAX_Z_TABLE,MIN_Z_TABLE,0);

   Dim Dim_Sender ( 5, 0, 15, 40,"Sender" );
   Sender=new Sender_Class(Main,Dim_Sender);

   Dim Dim_Serial ( 20, 0,  7, 40,"Serial" );
   Serial=new Serial_Manager_Class(Main,Dim_Serial);

   Dim Dim_Coords ( 0,24,  5, 73,"Coords" );
   Coords=new Coords_Class(Main,Dim_Coords);

   TresD=new TresD_Class();

   Gantry_XY->Set_Coords ( Coords );
   Histo_Z->Set_Coords   ( Coords );

   Screen_Update=new Screen_Update_Class();

   T.Set_Coords_Rti        ( Coords        );
   T.Set_Gantry_Rti        ( Gantry_XY     );
   T.Set_Histo_Rti         ( Histo_Z       );
   T.Set_Sender_Rti        ( Sender        );
   T.Set_Screen_Update_Rti ( Screen_Update );
   T.Set_Serial_Manager_Rti( Serial        );
   T.Set_TresD_Rti         ( TresD         );
}
//----------------------------------------------------------------------------------------------------

