#include "inc_all.h"
//----------------------------------------------------------------------------------------------------
Screen_Update_Class::Screen_Update_Class(void)
{
}
void Screen_Update_Class::Rti(void)
{
   int Key;
   while(Main_Page==NULL)
      ;
   while(1) {
   pthread_mutex_lock(&Main_Page->Print_Mutex);
      update_panels ( );
      Key=getch     ( ); // ojo que esta humilde funcion llama a wrefresh!!
      doupdate      ( ); // por eso tengo que hacer todo junto con el doupdate
   pthread_mutex_unlock(&Main_Page->Print_Mutex);
      switch(Key) {
         case ERR:   //cuando no hay tecna espero.. si hay, no espero asi es mas rapida la atencion al publico
            nanosleep     ( &Rti_Delay,&Rti_Delay );
            break;
         case 'q':
            clrtoeol (   );
            echo     (   );
            nocbreak (   );
            curs_set ( 1 );
            endwin   (   );
            exit     ( 0 );
            break;
         case 'x':
            if(Sheet::Sheet4Top_Panel()!=Main_Page->Gantry_XY)
               Sheet::Sheet4Top_Panel()->Deselect();
            Main_Page->Gantry_XY->Toogle_Select();
            Main_Page->Gantry_XY->Top();
            break;
         case 'z':
            if(Sheet::Sheet4Top_Panel()!=Main_Page->Histo_Z)
               Sheet::Sheet4Top_Panel()->Deselect();
            Main_Page->Histo_Z->Toogle_Select();
            Main_Page->Histo_Z->Top();
            break;
         case 's':
            if(Sheet::Sheet4Top_Panel()!=Main_Page->Sender)
               Sheet::Sheet4Top_Panel()->Deselect();
            Main_Page->Sender->Toogle_Select ( );
            Main_Page->Sender->Top           ( );
            break;
         case 'c':
            if(Sheet::Sheet4Top_Panel()!=Main_Page->Serial)
               Sheet::Sheet4Top_Panel()->Deselect();
            Main_Page->Serial->Toogle_Select ( );
            Main_Page->Serial->Top           ( );
            break;
         case 'd':
            if(Sheet::Sheet4Top_Panel()!=Main_Page->Coords)
               Sheet::Sheet4Top_Panel()->Deselect();
            Main_Page->Coords->Toogle_Select ( );
            Main_Page->Coords->Top           ( );
            break;
         case '2':
               Main_Page->TresD->Toogle_Plot_Speed();
            break;
         case '3':
               Main_Page->TresD->Toogle_Plot3();
            break;
         case '4':
               Main_Page->TresD->Toogle_Plot_Pos();
            break;
         case '5':
               Main_Page->TresD->Toogle_Plot_Gcode();
            break;
         case '6':
               Main_Page->TresD->Gcode2Matrix();
            break;
         case '7':
               Main_Page->TresD->Translate();
            break;
         case '8':
               Main_Page->TresD->Rotate();
            break;
         case '9':
               Main_Page->TresD->Matrix2GCode();
            break;
         case 'C':
               Curses->Init_Full_Colors();
               Main_Page->Gantry_XY->Redraw_Path ( );
               Main_Page->Histo_Z->Touch_Win     ( );
            break;
         default:
            Sheet::Sheet4Top_Panel()->Key(Key);
      }
   }
}
//----------------------------------------------------------------------------------------------------
