#include <cdk/cdk.h>
#include <panel.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "status_bar.h"
#include "ncurses_pthread.h"

#include "sheets.h"
#include "menu.h"
#include "screen_update.h"
#include "sheets.h"

#define WIDTH  	49
#define HEIGHT 	27
#define WIN_X 	10
#define WIN_Y 	0

static WINDOW 			*Win,*Sub_Win;
static PANEL 			*Panel,*Sub_Panel;
static pthread_t 		PT_Status_Bar_Rti;
pthread_mutex_t 		Status_Bar_Mutex = PTHREAD_MUTEX_INITIALIZER;
static unsigned short int	Hide 			= 1;
static char 			Buf[WIDTH*HEIGHT];
static void (*Methods[]) (void) =
{
	Status_Bar_Panel2U,
	Status_Bar_Panel2D,
	Status_Bar_Panel2R,
	Status_Bar_Panel2L,
	Select_Status_Bar,
	Deselect_Status_Bar,
	Redraw_Status_Bar_Box,
	(void (*)())Parse_Status_Bar_Menu,
	Start_Status_Bar_Menu,
	Hide_Status_Bar,
	l_Key_Status_Bar,
	h_Key_Status_Bar,
	j_Key_Status_Bar,
	k_Key_Status_Bar,
	a_Key_Status_Bar,
	s_Key_Status_Bar,
	d_Key_Status_Bar,
	f_Key_Status_Bar,
	Re_Init_Status_Bar,
	Rien,
	Rien,
	Rien,
	Full_Screen_Status_Bar,
	(void (*)())Set_Status_Bar_Props,
	(void (*)())Read_Status_Bar_Props,
};
//----------------------------------------------------------------------------------------------------
void 	Redraw_Status_Bar_Box(void)
{
	pthread_mutex_lock(&Screen_Update_Mutex);	
		box   	  	(Win,0,0);
		mvwprintw 	(Win,0,5,"Status_Bar ");
	pthread_mutex_unlock(&Screen_Update_Mutex);	
}
void Init_Status_Bar(void)
{
	Win			= newwin(HEIGHT, WIDTH, WIN_Y,WIN_X);
	Sub_Win 		= newwin(getmaxy(Win)-2, getmaxx(Win)-2, getbegy(Win)+1,getbegx(Win)+1);
	scrollok(Sub_Win,true);
	Panel			= new_panel(Win);
	Sub_Panel		= new_panel(Sub_Win);
	set_panel_userptr 	(Sub_Panel,Methods);
	set_panel_userptr 	(Panel,Methods);
	Redraw_Status_Bar_Box();
	pthread_create(&PT_Status_Bar_Rti, NULL, Status_Bar_Rti, NULL);
	hide_panel(Panel);
	hide_panel(Sub_Panel);
	Register_Panel(Panel,STATUS_BAR_PROP_INDEX);	
}
void 	Re_Init_Status_Bar(void)
{
	Redraw_Status_Bar_Box();
	Reposition_Status_Bar_Log_Panel();
	Hide=0;
}
void Reposition_Status_Bar_Log_Panel(void)
{
	wresize 	(Sub_Win, 	getmaxy(Win)-2,getmaxx(Win)-2);
	Move_Panel 	(Sub_Panel, 	getbegy(Win)+1,getbegx(Win)+1);
	top_panel(Sub_Panel);
}
void* Status_Bar_Rti(void* Arg1)
{
	struct timespec req={0,STATUS_BAR_RTI};
	while(1) {
	 	nanosleep(&req,&req);
	}
}
void Destroy_Status_Bar(void)
{
	pthread_exit(&PT_Status_Bar_Rti);
	delwin(Win);
}
void Print_Status_Bar_Data(const char *D,...)
{
	va_list a_list;
    	va_start(a_list, D );
	Pt_wprintw (Sub_Win,D,a_list);
	
}
void Print_Status_Bar_Hex_Data(const char *D,unsigned short int Length)
{
	unsigned short int i;
	for(i=0;i<Length;i++)
		Pt_waddch_hex(Sub_Win,D[i]);
}
void Add_Status_Bar_Data(char *Data,unsigned int Length)
{
	Pt_waddnstr(Sub_Win,Data,Length);
}
void Status_Bar_Panel2U 	(void) {Panel2U 	(Panel); 	Reposition_Status_Bar_Log_Panel();}
void Status_Bar_Panel2D 	(void) {Panel2D 	(Panel); 	Reposition_Status_Bar_Log_Panel();}
void Status_Bar_Panel2R 	(void) {Panel2R 	(Panel); 	Reposition_Status_Bar_Log_Panel();}
void Status_Bar_Panel2L 	(void) {Panel2L 	(Panel); 	Reposition_Status_Bar_Log_Panel();}
void Bottom_Status_Bar 		(void) {Pt_Bottom_Panel (Panel); 	Pt_Bottom_Panel(Sub_Panel);}
void Top_Status_Bar 		(void) {Pt_Top_Panel 	(Panel); 	Pt_Top_Panel(Sub_Panel);}
void Select_Status_Bar   	(void) {Select_Panel 	(Panel); 	Re_Init_Status_Bar();}
void Deselect_Status_Bar 	(void) {Deselect_Panel 	(Panel); 	;}
void Hide_Status_Bar 		(void) {Pt_Hide_Panel 	(Panel); 	Pt_Hide_Panel(Sub_Panel); 	Hide=1;}

void f_Key_Status_Bar(void) { }
void a_Key_Status_Bar(void) { }
void s_Key_Status_Bar(void) { }
void d_Key_Status_Bar(void) { }

void Full_Screen_Status_Bar(void)
{
	Panel_Full_Screen(Panel); 
	Re_Init_Status_Bar();
}

void l_Key_Status_Bar(void)
{
	Inc_Width_Sheet(Win); 
}
void h_Key_Status_Bar(void)
{
	Dec_Width_Sheet(Win);	
}
void k_Key_Status_Bar(void)
{
	Inc_Height_Sheet(Win);	
}
void j_Key_Status_Bar(void)
{
	Dec_Height_Sheet(Win);	
}
void Set_Status_Bar_Props(struct Struct_Sheets_Prop *S)
{
	Set_Panel_Prop(Panel,S);
}
void Read_Status_Bar_Props(struct Struct_Sheets_Prop *S)
{
	S->Hide=Hide;
	Read_Panel_Prop(Panel,S);
}
//----------------------------------------------------------------------------------------------------
void Start_Status_Bar_Menu 	(void)/*{{{*/
{
	int 			Submenu_Size[]={3,4},Menu_Loc[2]={LEFT,RIGHT};
	const char 		*Menu_List[][MAX_SUB_ITEMS]= { 
					{
						"</B>File<!B>",
						"</B>Save<!B>",
						"</B>Exit<!B>",
					},
					{
						"</B>Help<!B>",
						"</B>On Edit <!B>",
						"</B>On File <!B>",
						"</B>About...<!B>",
					},
				};
	Set_Menu (Panel,Menu_List,2,Submenu_Size,Menu_Loc);
}
void Parse_Status_Bar_Menu 	(int Selection)
{
	switch(Selection) {	
		case 000:
			break;
		case 001:
			Destroy_Sheets();
			break;
		}
}/*}}}*/
//----------------------------------------------------------------------------------------------------

