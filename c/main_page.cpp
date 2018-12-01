#include "inc_all.h"

//----------------------------------------------------------------------------------------------------
Main_Page_Class::Main_Page_Class (WINDOW* w)
{
   pthread_mutex_init(&Print_Mutex,NULL);
   pthread_mutex_init(&Serial_Mutex,NULL); //ara repartir el acceso al puerto serie..

   Dim Dim_Main_Page(0, 0,getmaxy(w),getmaxx(w),"PaP");
   Main=new Sheet(w,Dim_Main_Page);

   Dim Dim_Gantry(5, 47,35,50,"XY");
   Gantry_XY=new Gantry_Class(Main,Dim_Gantry);

   Dim Dim_Histo(5, 42,35, 5,"Z");
   Histo_Z=new Histo_Class(Main,Dim_Histo,25*Z_SCALE,-25*Z_SCALE,0);

   Dim Dim_Sender ( 5, 0, 15, 42,"Sender" );
   Sender=new Sender_Class(Main,Dim_Sender);

   Dim Dim_Serial ( 20, 0,  8, 42,"Serial" );
   Serial=new Serial_Manager_Class(Main,Dim_Serial);

   Dim Dim_Coords ( 0,42,  5, 55,"Coords" );
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
//   T.Set_TresD_Rti         ( TresD         );
}
//----------------------------------------------------------------------------------------------------

