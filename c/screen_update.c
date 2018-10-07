#include <cdk/cdk.h>
#include <ncurses.h>
#include <panel.h>
#include <pthread.h>
#include "screen_update.h"
#include "sheet.h"
//----------------------------------------------------------------------------------------------------
pthread_t                  PT_Screen_Update_Rti    ;
static struct timespec     Rti_Delay= { 0, 5000000}; // 100 milis
//----------------------------------------------------------------------------------------------------
void Init_Screen_Update(void)
{
   pthread_create ( &PT_Screen_Update_Rti, NULL, Screen_Update_Rti, NULL );
}
void* Screen_Update_Rti(void* Arg1)
{
   int Key;
   while(1) {
      nanosleep     ( &Rti_Delay,&Rti_Delay );
      update_panels (           );
      Key=getch    (); // ojo que esta humilde funcion llama a wrefresh!!
      doupdate      (           ); // por eso tengo que hacer todo junto con el doupdate 
      switch(Key) {
         case KEY_F1:
         case ' ':
//            Start_Menu_Menu();
            break;
         case KEY_F2:
            break;
         case KEY_F3:
            break;
         case KEY_F4:
            break;
         case KEY_F5:
            break;
         case KEY_F6:
            break;
         case KEY_F7:
            break;
         case KEY_F8:
            break;
         case KEY_F9:
            Sheet::Sheet4Top_Panel()->Hide();
            break;
         case KEY_F10:
            break;
         case KEY_F11:
            Sheet::Sheet4Top_Panel()->Full_Screen();
            break;
         case KEY_UP:
            Sheet::Sheet4Top_Panel()->To_Up();
            break;
         case KEY_DOWN:
            Sheet::Sheet4Top_Panel()->To_Down();
            break;
         case KEY_RIGHT:
            ((Sheet*)panel_userptr(panel_below(0)))->To_Right();
            Sheet::Sheet4Top_Panel()->To_Right();
            break;
         case KEY_LEFT:
            Sheet::Sheet4Top_Panel()->To_Left();
            break;
         case 'l':
            Sheet::Sheet4Top_Panel()->Inc_Width();
            break;
         case 'h':
            Sheet::Sheet4Top_Panel()->Dec_Width();
            break;
         case 'j':
            Sheet::Sheet4Top_Panel()->Inc_Height();
            break;
         case 'k':
            Sheet::Sheet4Top_Panel()->Dec_Height();
            break;
         case KEY_BACKSPACE:
            break;
         case KEY_HOME:
            break;
         case KEY_ESC:
            endCDK (   );
            exit   ( 0 );
            break;
      }
   }
}
void Destroy_Screen_Update(void)
{
   pthread_exit ( &PT_Screen_Update_Rti );
}
//----------------------------------------------------------------------------------------------------
