#include <cdk/cdk.h>
#include <panel.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "screen_update.h"
#include "sheet.h"
#include "menu.h"

////----------------------------------------------------------------------------------------------------
Sheet::Sheet(WINDOW *Ext_Win)
{
   Win   = Ext_Win;
   Panel = new_panel ( Win );
}
Sheet::Sheet(uint16_t Y, uint16_t X, uint16_t Height, uint16_t Width,const char* Tittle)
{
   Win   = newwin         ( Height ,Width ,Y ,X );
   Panel = new_panel      ( Win        );
   Set_Panel_User_Pointer (            );
   Set_Name               ( Tittle     );
   Redraw_Box             (            );
}
Sheet::Sheet()
{
   Win   = newwin    ( 1 ,1 ,0 ,0 );
   Panel = new_panel ( Win       );
}
void  Sheet::Redraw_Box(void)
{
   wattron       ( Win ,COLOR_PAIR(100 ));
   box           ( Win ,0 ,0           ) ;
   wattroff      ( Win ,COLOR_PAIR(100 ));
   wattron       ( Win ,COLOR_PAIR(180 ));
   if(strlen(Name)+2 <= getmaxx(Win))
      mvwprintw ( Win ,0 ,1 ,Name );
   wattroff      ( Win ,COLOR_PAIR(180 ));
}
void  Sheet::Hide_Box(void)
{
   wborder       ( Win ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' );
}
void  Sheet::Set_Name(const char* Sheet_Name)
{
   strcpy ( Name,Sheet_Name );
}
void  Sheet::Set_Size(unsigned short int Height,unsigned short int Width)
{
   wresize       ( Win,Height,Width );
}
unsigned short int Sheet::Get_Height(void)
{
   return getbegy ( Win );
}
unsigned short int Sheet::Get_Width(void)
{
   return getbegx ( Win );
}
char     Sheet::To_Up(void)
{
   if ( (getbegy(Win )-1)>Main_Sheet->Beg_Y()) {
      Sheet::Move_Panel ( Panel,getbegy(Win )-1,getbegx(Win));
      return 0;
   }
   else
      return -1;
}
char  Sheet::To_Down(void)
{
   if ( (getbegy(Win )+getmaxy(Win)+1)<(Main_Sheet->Beg_Y()+Main_Sheet->Max_Y())) {
      Sheet::Move_Panel ( Panel,getbegy(Win )+1,getbegx(Win));
      return 0;
   }
   else
      return -1;
}
char  Sheet::To_Right(void)
{
   if ( (getbegx(Win )+getmaxx(Win)+1)<(Main_Sheet->Beg_X()+Main_Sheet->Max_X())) {
      Sheet::Move_Panel ( Panel,getbegy(Win ),getbegx(Win)+1);
      return 0;
   }
   else
      return -1;
}
char  Sheet::To_Left(void)
{
   if ( (getbegx(Win )-1)>Main_Sheet->Beg_X()) {
      Sheet::Move_Panel ( Panel,getbegy(Win ),getbegx(Win)-1);
      return 0;
   }
   else
      return -1;
}
void  Sheet::Inc_Width(void)
{
   if ( (getmaxx(Win )+getbegx(Win)+1)<Main_Sheet->Max_X()) {
         wclear  ( Win             )                ;
         wresize ( Win,getmaxy(Win ),getmaxx(Win)+1);
   }
   Redraw_Box    ( );
}
void  Sheet::Dec_Width(void)
{
   if ( getmaxx(Win )>MIN_WIDTH) {
      wclear  ( Win             )                ;
      wresize ( Win,getmaxy(Win ),getmaxx(Win)-1);
   }
   Redraw_Box            ( );
   Main_Sheet->Touch_Win ( ); // sino quedan residuos del box
}
void  Sheet::Inc_Height(void)
{
   if ( (getmaxy(Win )+getbegy(Win)+1)<Main_Sheet->Max_Y()) {
         wclear  ( Win             )                ;
         wresize ( Win,getmaxy(Win )+1,getmaxx(Win));
   }
   Redraw_Box    ( );
}
void  Sheet::Dec_Height(void)
{
   if ( getmaxy(Win )>MIN_HEIGHT) {
         wclear  ( Win             )                ;
         wresize ( Win,getmaxy(Win )-1,getmaxx(Win));
   }
   Redraw_Box            ( );
   Main_Sheet->Touch_Win ( ); // sino quedan residuos del box
}
void  Sheet::Set_Pos(unsigned short int Y,unsigned short int X)
{
   Move_Panel ( Panel,Y,X );
}
void  Sheet::Hide(void)
{
   hide_panel    ( Panel );
}
void  Sheet::Unhide(void)
{
   show_panel    ( Panel );
}
void  Sheet::Top(void)
{
   top_panel     ( Panel );
}
void  Sheet::Bottom(void)
{
   bottom_panel  ( Panel );
}
void  Sheet::Select(void)
{
   mvwaddch      ( Win,1,1,'*'|A_BOLD );
}
void  Sheet::Deselect(void)
{
   mvwaddch      ( Win,1,1,' '|A_NORMAL );
}
void  Sheet::Full_Screen(void)
{
   wclear ( panel_window(Panel ));
   move_panel(Panel,Main_Sheet->Beg_Y(),Main_Sheet->Beg_X());
   wresize(panel_window(Panel),Main_Sheet->Max_Y(),Main_Sheet->Max_X());
   Sheet::Redraw_Box ( );
}
void Sheet::Set_Panel_User_Pointer()
{
   set_panel_userptr ( Panel,this);
}
void Sheet::Set_Panel_User_Pointer(Sheet* Ptr)
{
   set_panel_userptr ( Panel,(void* )Ptr);
}
Sheet::~Sheet(void)
{
   del_panel ( Panel );
   delwin    ( Win   );
};
void  Sheet::Move_Panel(PANEL* Panel,unsigned short int Y,unsigned short int X)
{
   move_panel    ( Panel,Y,X );
}
void  Sheet::Touch_Win(void)
{
   touchwin      ( Win );
}
unsigned short int   Sheet::Max_Y(void)
{
   return getmaxy ( Win );
}
unsigned short int   Sheet::Max_X(void)
{
   return getmaxx ( Win );
}
unsigned short int   Sheet::Beg_Y(void)
{
   return getbegy ( Win );
}
unsigned short int   Sheet::Beg_X(void)
{
   return getbegx ( Win );
}

Sheet* Sheet::Sheet4Top_Panel(void)
{
   return Sheet::Sheet4Panel ( panel_below(0 ));
}
Sheet* Sheet::Sheet4Panel(PANEL* Panel)
{
   return ( Sheet* )(panel_userptr(Panel));
}

