#include "inc_all.h"

Fiducial_Class::Fiducial_Class (Sheet* Parent,Dim D):Sheet(Parent,D)
{
};

//-----------------------------------------------------------------------
void Fiducial_Class::Rti(void)
{
   while(1){
         nanosleep ( &Rti_Delay,&Rti_Delay );
         switch(Fiducial_State) {
            case 1:
               Main_Page->Coords->Actual_Jog_X=Main_Page->Coords->Actual_X+OPENMV_CAMERA_OFFSET_X;
               Main_Page->Coords->Actual_Jog_Y=Main_Page->Coords->Actual_Y+OPENMV_CAMERA_OFFSET_Y;
               Main_Page->Gantry_XY->Goto_Jog_XY();
               nanosleep ( &Rti_Delay,&Rti_Delay );
                  while(Main_Page->Coords->Speed!=0)
                     ;
               while(Main_Page->Openmv->Is_Centered()==0) {
                  Main_Page->Openmv->Move2Center();
                  nanosleep ( &Rti_Delay,&Rti_Delay );
                  while(Main_Page->Coords->Speed!=0)
                     ;
               }
               Main_Page->Coords->Actual_Jog_X=Main_Page->Coords->Actual_X-OPENMV_CAMERA_OFFSET_X;
               Main_Page->Coords->Actual_Jog_Y=Main_Page->Coords->Actual_Y-OPENMV_CAMERA_OFFSET_Y;
               Main_Page->Gantry_XY->Goto_Jog_XY();
               nanosleep ( &Rti_Delay,&Rti_Delay );
               while(Main_Page->Coords->Speed!=0)
                  ;
               Main_Page->Gantry_XY->Jog2New_XY_Zero();
               nanosleep ( &Rti_Delay,&Rti_Delay );
               Main_Page->TresD->Set_Fiducial(1);
               Main_Page->TresD->Gcode2Matrix();
               Main_Page->TresD->Rotate(Main_Page->Openmv->Rotation_Snapshot);
               Main_Page->TresD->Matrix2GCode();
               Fiducial_State=2;
               break;
            case 2:
               Main_Page->Sender->Send_Next_Line();
               nanosleep ( &Rti_Delay,&Rti_Delay );
               while(Main_Page->Coords->Speed!=0)
                  ;
               Main_Page->Coords->Actual_Jog_X=Main_Page->Coords->Actual_X+OPENMV_CAMERA_OFFSET_X;
               Main_Page->Coords->Actual_Jog_Y=Main_Page->Coords->Actual_Y+OPENMV_CAMERA_OFFSET_Y;
               Main_Page->Gantry_XY->Goto_Jog_XY();
               nanosleep ( &Rti_Delay,&Rti_Delay );
                  while(Main_Page->Coords->Speed!=0)
                     ;
               while(Main_Page->Openmv->Is_Centered()==0) {
                  Main_Page->Openmv->Move2Center();
                  nanosleep ( &Rti_Delay,&Rti_Delay );
                  while(Main_Page->Coords->Speed!=0)
                     ;
               }
               nanosleep ( &Rti_Delay,&Rti_Delay );
               while(Main_Page->Coords->Speed!=0)
                  ;
               Main_Page->Coords->Actual_Jog_X=Main_Page->Coords->Actual_X-OPENMV_CAMERA_OFFSET_X;
               Main_Page->Coords->Actual_Jog_Y=Main_Page->Coords->Actual_Y-OPENMV_CAMERA_OFFSET_Y;
               Main_Page->Gantry_XY->Goto_Jog_XY();
               nanosleep ( &Rti_Delay,&Rti_Delay );
               while(Main_Page->Coords->Speed!=0)
                  ;
               Main_Page->TresD->Set_Fiducial(2);
               Main_Page->TresD->Matrix2GCode();
               Fiducial_State=0;
               Main_Page->Sender->Play();
               break;
            case 3:
               Main_Page->Openmv->Move2Center();
               nanosleep ( &Rti_Delay,&Rti_Delay );
               while(Main_Page->Coords->Speed!=0)
                  ;
               if(Main_Page->Openmv->Is_Centered())
                  Fiducial_State=0;
               break;
         }
   }
}

void Fiducial_Class::Key(int K)
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
   }
}
