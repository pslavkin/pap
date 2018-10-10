#include <cdk/cdk.h>
#include <panel.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "dim.h"
#include "sheet.h"
#include "gantry.h"
#include "menu.h"
#include "histograms.h"
#include "screen_update.h"

Sheet::Sheet(Sheet* Parent,Dim D)
{
   this->Dims   = D;
   Parent_Sheet = Parent;
   Normalize_Y ( );
   Normalize_H ( );
   Normalize_X ( );
   Normalize_W ( );
   Win          = newwin    ( D.H ,D.W,Parent->Beg_Y()+D.Y ,Parent->Beg_X()+D.X );
   Panel        = new_panel ( Win    );
   Set_Panel_User_Pointer   (        );
   Set_Name                 ( D.Name );
   Redraw_Box               (        );
}
Sheet::Sheet(WINDOW* W,Dim D)
{
   Win          = W;
   Panel        = new_panel ( Win );
   Parent_Sheet = this                ;
   Set_Panel_User_Pointer (               );
   Set_Name               ( D.Name        );
   this->Dims=D;
   wresize                ( Win,D.H,D.W   );
   move_panel             ( Panel,D.Y,D.X );
   Redraw_Box             (               );


}
void  Sheet::Set_Parent_Sheet(Sheet* P)
{
   Parent_Sheet=P;
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
void     Sheet::To_Up(void)
{
   if ( Dims.Y>0) {
      Dims.Y--;
      move_panel ( Panel,Parent_Sheet->Beg_Y()+Dims.Y,Parent_Sheet->Beg_X()+Dims.X);
   }
}
void  Sheet::To_Down(void)
{
   if ( (Dims.Y+Dims.H)<Parent_Sheet->Dims.H) {
      Dims.Y++;
      move_panel ( Panel,Parent_Sheet->Beg_Y()+Dims.Y,Parent_Sheet->Beg_X()+Dims.X);
   }
}
void  Sheet::To_Right(void)
{
   if ((Dims.X+Dims.W)<Parent_Sheet->Dims.W) {
      Dims.X++;
      move_panel ( Panel,Parent_Sheet->Beg_Y()+Dims.Y,Parent_Sheet->Beg_X()+Dims.X);
   }
}
void  Sheet::To_Left(void)
{
   if ( Dims.X>0) {
      Dims.X--;
      move_panel ( Panel,Parent_Sheet->Beg_Y()+Dims.Y,Parent_Sheet->Beg_X()+Dims.X);
   }
}

void Sheet::Normalize_X(void)
{
   if(Dims.X>=Parent_Sheet->Dims.W)          Dims.X=Parent_Sheet->Dims.W;
}
void Sheet::Normalize_Y(void)
{
   if(Dims.Y>=Parent_Sheet->Dims.H)          Dims.Y=Parent_Sheet->Dims.H;
}
void Sheet::Normalize_W(void)
{
   if((Dims.X+Dims.W) >= Parent_Sheet->Dims.W)  Dims.W = Parent_Sheet->Dims.W-Dims.X;
}
void Sheet::Normalize_H(void)
{
   if((Dims.Y+Dims.H) >= Parent_Sheet->Dims.H)  Dims.H=Parent_Sheet->Dims.H-Dims.Y;
}

void  Sheet::Inc_Width(void)
{
   Dims.W++;
   Normalize_W();
   wresize    ( Win,Dims.H,Dims.W );
   wclear     ( Win               );
   Redraw_Box (                   );
}
void  Sheet::Dec_Width(void)
{
   if(Dims.W>MIN_WIDTH)
      Dims.W--;
   wresize    ( Win,Dims.H,Dims.W );
   wclear     ( Win               );
   Redraw_Box (                   );
   Parent_Sheet->Touch_Win ( ); // sino quedan residuos del box
}
void  Sheet::Inc_Height(void)
{
   Dims.H++;
   Normalize_H();
   wresize    ( Win,Dims.H,Dims.W );
   wclear     ( Win               );
   Redraw_Box (                   );
}
void  Sheet::Dec_Height(void)
{
   if(Dims.H>MIN_HEIGHT)
      Dims.H--;
   wresize    ( Win,Dims.H,Dims.W );
   wclear     ( Win               );
   Redraw_Box (                   );
   Parent_Sheet->Touch_Win ( ); // sino quedan residuos del box
}
void  Sheet::Set_Pos(unsigned short int Y,unsigned short int X)
{
   Move_Panel ( Panel,Y,X );
}
void  Sheet::Hide(void)
{
   hide_panel ( Panel );
}
void  Sheet::Unhide(void)
{
   show_panel ( Panel );
}
void  Sheet::Top(void)
{
   top_panel ( Panel );
}
void  Sheet::Bottom(void)
{
   bottom_panel ( Panel );
}
void  Sheet::Select(void)
{
   mvwaddch ( Win,1,1,'*'|A_BOLD );
}
void  Sheet::Deselect(void)
{
   mvwaddch ( Win,1,1,' '|A_NORMAL );
}
void  Sheet::Full_Screen(void)
{
   wclear ( panel_window(Panel ));
   move_panel ( Panel,Parent_Sheet->Beg_Y( ),Parent_Sheet->Beg_X());
   wresize ( panel_window(Panel ),Parent_Sheet->Max_Y(),Parent_Sheet->Max_X());
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

