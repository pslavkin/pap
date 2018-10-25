#include "inc_all.h"

//----------------------------------------------------------------------------------------------------
Main_Page_Class::Main_Page_Class (WINDOW* w)
{
   Dim Dim_Main_Page(0, 0,getmaxy(w),getmaxx(w),"PaP");
   Main=new Sheet(w,Dim_Main_Page);

   Dim Dim_Gantry(5, 66,35,70,"XY");
   Gantry_XY=new Gantry_Class(Main,Dim_Gantry);

   Dim Dim_Histo(5, 61,35, 5,"z");
   Histo_Z=new Histo_Class(Main,Dim_Histo,100,50);

   Dim Dim_Serial ( 30, 0, 10, 61,"Serial" );
   Serial=new Serial_Manager_Class(Main,Dim_Serial);

   Dim Dim_Coords ( 0,61,  5, 75,"Coords" );
   Coords=new Coords_Class(Main,Dim_Coords);

   Dim Dim_Parser ( 20, 0, 10, 61,"Parser" );
   Parser=new Parser_Class(Main,Dim_Parser);

   TresD=new TresD_Class();

   Gantry_XY->Set_Coords ( Coords );
   Histo_Z->Set_Coords   ( Coords );

   Screen_Update=new Screen_Update_Class();

   T.Set_Coords_Rti        ( Coords        );
   T.Set_Serial_Manager_Rti( Serial        );
   T.Set_Gantry_Rti        ( Gantry_XY     );
   T.Set_Histo_Rti         ( Histo_Z       );
   T.Set_Parser_Rti        ( Parser        );
   T.Set_Screen_Update_Rti ( Screen_Update );
//   T.Set_TresD_Rti         ( TresD         );
}
//----------------------------------------------------------------------------------------------------

