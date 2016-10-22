#include <cdk/cdk.h>
#include <panel.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "screen_update.h"
#include "ncurses_pthread.h"
#include "sheets.h"
#include "menu.h"
#include "analog_clk.h"

////----------------------------------------------------------------------------------------------------
	Sheet::Sheet()
{
	Win= 			newwin(1, 1, 0,0);
	Panel= 			new_panel(Win);
}
void 	Sheet::Redraw_Box(void)
{
	box   	  	(Win,0,0);
	mvwprintw 	(Win,0,5,Name);
	update_panels();
}
void 	Sheet::Hide_Box(void)
{
	wborder	  	(Win,' ',' ',' ',' ',' ',' ',' ',' ');
	update_panels();
}
void 	Sheet::Set_Name(char* Sheet_Name)
{
	strcpy(Name,Sheet_Name);	
}
void 	Sheet::Set_Size(unsigned short int Height,unsigned short int Width)
{
	wresize(Win,Height,Width);
	update_panels();
}
void 	Sheet::To_Up(void)
{
	Sheet::Move_Panel(Panel,getbegy(Win)-1,getbegx(Win));
}
void 	Sheet::To_Down(void)
{
	Sheet::Move_Panel(Panel,getbegy(Win)+1,getbegx(Win));
}
void 	Sheet::To_Right(void)
{
	Sheet::Move_Panel(Panel,getbegy(Win),getbegx(Win)+1);
}
void 	Sheet::To_Left(void)
{
	Sheet::Move_Panel(Panel,getbegy(Win),getbegx(Win)-1);
}
void 	Sheet::Inc_Width(void)
{
	if((getmaxx(Win)+getbegx(Win))<getmaxx(stdscr)) {
			wclear(Win);
			wresize(Win,getmaxy(Win),getmaxx(Win)+1);
	}
	Redraw_Box();
	update_panels();
}
void 	Sheet::Dec_Width(void)
{
	if(getmaxx(Win)>MIN_WIDTH) {
		wclear(Win);
		wresize(Win,getmaxy(Win),getmaxx(Win)-1);
	}
	Redraw_Box();
	Touch_Scr_Window();	//sino quedan residuos del box
	update_panels();
}
void 	Sheet::Inc_Height(void)
{
	if((getmaxy(Win)+getbegy(Win))<getmaxy(stdscr)) {
			wclear(Win);
			wresize(Win,getmaxy(Win)+1,getmaxx(Win));
	}
	Redraw_Box();
	update_panels();
}
void 	Sheet::Dec_Height(void)
{
	if(getmaxy(Win)>MIN_HEIGHT) {
			wclear(Win);
			wresize(Win,getmaxy(Win)-1,getmaxx(Win));
	}
	Redraw_Box();
	Touch_Scr_Window();	//sino quedan residuos del box
	update_panels();
}
void 	Sheet::Set_Pos(unsigned short int Y,unsigned short int X)
{
	Move_Panel(Panel,Y,X);
}
void 	Sheet::Hide(void)
{
	hide_panel(Panel);
	update_panels();
}
void 	Sheet::Unhide(void)
{
	show_panel(Panel);
	update_panels();
}
void 	Sheet::Top(void)
{
	top_panel(Panel);
	update_panels();
}
void 	Sheet::Bottom(void)
{
	bottom_panel(Panel);
	update_panels();
}
void 	Sheet::Select(void)
{
	mvwaddch(Win,1,1,'*'|A_BOLD);
	update_panels();
}
void 	Sheet::Deselect(void)
{
	mvwaddch(Win,1,1,' '|A_NORMAL);
	update_panels();
}
void 	Sheet::Full_Screen(void)
{
	wclear(panel_window(Panel));
	move_panel(Panel,getbegy(Scr_Window()),getbegx(Scr_Window()));
	wresize(panel_window(Panel),getmaxy(Scr_Window()),getmaxx(Scr_Window()));
	Sheet::Redraw_Box();
	update_panels();
}
void Sheet::Set_Panel_User_Pointer(Sheet* Ptr)
{
	set_panel_userptr 	(Panel,(void*)Ptr);
}
 	Sheet::~Sheet(void)
{
	del_panel(Panel);
	delwin(Win);
};
void 	Sheet::Move_Panel(PANEL* Panel,unsigned short int Y,unsigned short int X)
{
	move_panel(Panel,Y,X);
	update_panels();
}
void 	Sheet::Touch_Win(void)
{
	touchwin(Win);
	update_panels();
}

