#include "inc_all.h"
//----------------------------------------------------------------------------------------------------
Screen_Update_Class::Screen_Update_Class(void)
{
}
void Screen_Update_Class::Rti(void)
{
   int Key;
   while(1) {
      nanosleep     ( &Rti_Delay,&Rti_Delay );
      update_panels ( );
      Key=getch     ( ); // ojo que esta humilde funcion llama a wrefresh!!
      doupdate      ( ); // por eso tengo que hacer todo junto con el doupdate
      switch(Key) {
         case 'q':
            clrtoeol (   );
            endwin   (   );
            echo     (   );
            nocbreak (   );
            exit     ( 0 );
            break;
         case 'x':
            if(Sheet::Sheet4Top_Panel()!=Main_Page->Gantry_XY)
               Sheet::Sheet4Top_Panel()->Deselect();
            Main_Page->Gantry_XY->Toogle_Select();
            Main_Page->Gantry_XY->Top();
            break;
         case 'z':
            if(Sheet::Sheet4Top_Panel()!=Main_Page->Histo_Z->S)
               Sheet::Sheet4Top_Panel()->Deselect();
            Main_Page->Histo_Z->S->Toogle_Select();
            Main_Page->Histo_Z->S->Top();
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
            if(Sheet::Sheet4Top_Panel()!=Main_Page->Coords->S)
               Sheet::Sheet4Top_Panel()->Deselect();
            Main_Page->Coords->S->Toogle_Select ( );
            Main_Page->Coords->S->Top           ( );
            break;
         case '3':
               Main_Page->T.Set_TresD_Rti ( Main_Page->TresD );
            break;
         default:
            Sheet::Sheet4Top_Panel()->Key(Key);
      }
   }
}
//----------------------------------------------------------------------------------------------------
