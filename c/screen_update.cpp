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
         case '3':
               Main_Page->T.Set_TresD_Rti ( Main_Page->TresD );
            break;
         case 'o':
         case 'i':
         case 'l':
         case 'h':
         case 'j':
         case 'k':
            Sheet::Sheet4Top_Panel()->Key(Key);
         case KEY_F(3):
            break;
         case KEY_F(4):
            break;
         case KEY_F(5):
            break;
         case KEY_F(6):
            break;
         case KEY_F(7):
            break;
         case KEY_F(8):
            break;
         case KEY_F(9):
            Sheet::Sheet4Top_Panel()->Hide();
            break;
         case KEY_F(10):
            break;
         case KEY_F(11):
            Sheet::Sheet4Top_Panel()->Full_Screen();
            break;
         case KEY_UP:
            Sheet::Sheet4Top_Panel()->To_Up();
            break;
         case KEY_DOWN:
            Sheet::Sheet4Top_Panel()->To_Down();
            break;
         case KEY_RIGHT:
            Sheet::Sheet4Top_Panel()->To_Right();
            break;
         case KEY_LEFT:
            Sheet::Sheet4Top_Panel()->To_Left();
            break;
//         case 'l':
//            Sheet::Sheet4Top_Panel()->Inc_Width();
//            break;
//         case 'h':
//            Sheet::Sheet4Top_Panel()->Dec_Width();
//            break;
//         case 'j':
//            Sheet::Sheet4Top_Panel()->Inc_Height();
//            break;
//         case 'k':
//            Sheet::Sheet4Top_Panel()->Dec_Height();
//            break;
         case KEY_BACKSPACE:
            break;
         case KEY_HOME:
            break;
         case 'q':
            clrtoeol (   );
            endwin   (   );
            echo     (   );
            nocbreak (   );
            exit     ( 0 );
            break;
      }
   }
}
//----------------------------------------------------------------------------------------------------
