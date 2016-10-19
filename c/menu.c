#include <cdk/cdk.h>
#include <menu.h>
#include <pthread.h>
#include <panel.h>
#include "ncurses_pthread.h"

#include "stretcher.h"
#include "status_bar.h"

#include "sheets.h"
#include "screen_update.h"
#include "multichannel.h"

//----------------------------------------------------------------------------------------------------
#define WIDTH  	49
#define HEIGHT 	27
#define WIN_X 	10
#define WIN_Y 	0

static WINDOW 		*Win;
static PANEL 		*Panel;
pthread_t 		PT_Menu_Rti;
static void (*Methods[10]) (void) =
{
	Top_Panel2U,
	Top_Panel2D,
	Top_Panel2R,
	Top_Panel2L,
	Select_Menu,
	Deselect_Menu,
	Redraw_Menu_Box,
	(void (*)())Parse_Menu_Menu,
	Start_Menu_Menu,
	Hide_Menu,
};
//----------------------------------------------------------------------------------------------------
void 	Redraw_Menu_Box(void)
{
	pthread_mutex_lock(&Screen_Update_Mutex);	
		box   	  	(Win,0,0);
		mvwprintw 	(Win,0,5,"Menu ");
	pthread_mutex_unlock(&Screen_Update_Mutex);	
}
void Init_Menu (void)
{
	Win = 			newwin(HEIGHT, WIDTH,WIN_Y,WIN_X);
	Redraw_Menu_Box();
	Panel= 			new_panel(Win);
	hide_panel(Panel);
	set_panel_userptr 	(Panel,Methods);
	pthread_create 		(&PT_Menu_Rti, NULL, Menu_Rti, NULL);
}
void Bottom_Menu 	(void) {Pt_Bottom_Panel(Panel);}
void Top_Menu 		(void) {Pt_Top_Panel   (Panel);}
void Select_Menu   	(void) {Select_Panel(Panel);}
void Deselect_Menu 	(void) {Deselect_Panel(Panel);}
void Hide_Menu 		(void) {Pt_Hide_Panel(Panel);}
//----------------------------------------------------------------------------------------------------
void Set_Slider (PANEL* Panel,unsigned int* Sel,unsigned int Min,unsigned int Max,unsigned int Fine_Step)
{
	unsigned short int Ans;
	CDKSCREEN *Cdk		=initCDKScreen 		(panel_window(Panel));
	CDKSLIDER *Slider 	=newCDKSlider(Cdk,CENTER,CENTER,"<C></U>Sel","",A_REVERSE|COLOR_PAIR(29)|' ',WIDTH-10,*Sel,Min,Max,Fine_Step,Fine_Step*10,TRUE,FALSE);
	pthread_mutex_lock(&Screen_Update_Mutex);	
		Ans 		=activateCDKSlider 	(Slider,0);
	pthread_mutex_unlock(&Screen_Update_Mutex);	
	if (Slider->exitType == vNORMAL) {*Sel=Ans;Print_Status_Bar_Data("Selected=%d\n",Ans);}
	destroyCDKSlider (Slider);
}
void Set_Menu (PANEL* Panel,const char* Menu_List[][MAX_SUB_ITEMS],unsigned char Items,int* Submenu_Size,int *Menu_Loc)
{
	unsigned short int	Selection;
	CDKSCREEN *Cdk		=initCDKScreen 		(panel_window(Panel));
	CDKMENU *Menu		=newCDKMenu 		(Cdk, Menu_List, Items, Submenu_Size, Menu_Loc, TOP, A_UNDERLINE, A_REVERSE); 
	pthread_mutex_lock(&Screen_Update_Mutex);	
		Selection 	=activateCDKMenu 	(Menu,0); 
	pthread_mutex_unlock(&Screen_Update_Mutex);	
	if (Menu->exitType == vNORMAL) 
		((void (**)(int))panel_userptr(panel_below(0)))[PARSE_MENU_OPTIONS_FUNC_INDEX](Selection);
	destroyCDKMenu 		(Menu);
	destroyCDKScreen 	(Cdk);
	((void (**)())panel_userptr(panel_below(0)))[REDRAW_BOX_FUNC_INDEX]();
}
char* Set_File_Select (PANEL* Panel)
{
	char 				*File_Name;
	static char 			New_File_Name[1000];
	CDKSCREEN 	*Cdk		=initCDKScreen (panel_window(Panel));
	CDKFSELECT 	*File_Select 	=newCDKFselect (Cdk,CENTER,CENTER,20,65,"Select File","",A_NORMAL,'_', A_REVERSE,"</5>","</48>","</N>","</N>",TRUE,FALSE);
	
	pthread_mutex_lock(&Screen_Update_Mutex);	
   		File_Name = copyChar(activateCDKFselect(File_Select,0));
	pthread_mutex_unlock(&Screen_Update_Mutex);	
	if (File_Select->exitType == vNORMAL) 
		strcpy(New_File_Name,File_Name);
	else strcpy(New_File_Name,"");
	destroyCDKFselect(File_Select);
	destroyCDKScreen(Cdk);
	return New_File_Name;
}

unsigned char Set_Entry (PANEL* Panel,const char* Title,char* Actual_Data,char* Data,unsigned short int Length)
{
	char 	*Info,Ans=1;
	CDKSCREEN 	*Cdk 	=initCDKScreen 		(panel_window(Panel));
   	CDKENTRY 	*Entry 	=newCDKEntry(Cdk,CENTER,CENTER,Title,Actual_Data,A_NORMAL,'.',vMIXED,20,0,Length,TRUE,TRUE);
	pthread_mutex_lock(&Screen_Update_Mutex);	
   		Info=activateCDKEntry(Entry, 0);
	pthread_mutex_unlock(&Screen_Update_Mutex);	
  	if (Entry->exitType == vNORMAL) {
		Ans=0;
		strcpy(Data,Info);
	}
   	destroyCDKEntry 	(Entry);
	destroyCDKScreen 	(Cdk);
	return Ans;
}

void* Menu_Rti(void* Arg1)
{
	struct timespec req={0,1000000000};
	int Selection,Key;
	while(1) {
	 	nanosleep(&req,&req);
		Key=getch();
//		Print_Status_Bar_Data("ingreso:%d\n",Key);
		switch(Key) {	
			case KEY_F1:
			case ' ':
				Top_Panel_Method_Exec(START_MENU_FUNC_INDEX);
				break;
			case KEY_F2:
				Top_Panel_Method_Exec(UNSELECT_FUNC_INDEX);
				break;
			case KEY_F3:
				Top_Panel_Method_Exec(UNSELECT_FUNC_INDEX);
				break;
			case KEY_F4:
				Top_Panel_Method_Exec(UNSELECT_FUNC_INDEX);
				Top_Stretcher();
				Select_Stretcher();
				break;
			case KEY_F5:
				Top_Panel_Method_Exec(UNSELECT_FUNC_INDEX);
				Top_Status_Bar();
				Select_Status_Bar();
				break;
			case KEY_F6:
				Top_Panel_Method_Exec(UNSELECT_FUNC_INDEX);
				break;
			case KEY_F7:
				Top_Panel_Method_Exec(UNSELECT_FUNC_INDEX);
				Top_Sheets();
				Select_Sheets();
				break;
			case KEY_F8:
				Top_Panel_Method_Exec(UNSELECT_FUNC_INDEX);
				break;
			case 't':
				Top_Panel_Method_Exec(UNSELECT_FUNC_INDEX);
				break;
			case KEY_F9:
				Top_Panel_Method_Exec(HIDE_FUNC_INDEX);
				break;
			case KEY_F10:
				Top_Panel_Method_Exec(UNSELECT_FUNC_INDEX);
				break;
			case KEY_F11:
				Top_Panel_Method_Exec(FULL_SCREEN_FUNC_INDEX);
				break;

			case KEY_UP:
				Top_Panel_Method_Exec(MOVE2U_FUNC_INDEX);
				break;
			case KEY_DOWN:
				Top_Panel_Method_Exec(MOVE2D_FUNC_INDEX);
				break;
			case KEY_RIGHT:
				Top_Panel_Method_Exec(MOVE2R_FUNC_INDEX);
				break;
			case KEY_LEFT:
				Top_Panel_Method_Exec(MOVE2L_FUNC_INDEX);
				break;
			case 'l':
				Top_Panel_Method_Exec(l_KEY_FUNC_INDEX);
				break;
			case 'h':
				Top_Panel_Method_Exec(h_KEY_FUNC_INDEX);
				break;
			case 'j':
				Top_Panel_Method_Exec(j_KEY_FUNC_INDEX);
				break;
			case 'k':
				Top_Panel_Method_Exec(k_KEY_FUNC_INDEX);
				break;
			case 'a':
				Top_Panel_Method_Exec(a_KEY_FUNC_INDEX);
				break;
			case 's':
				Top_Panel_Method_Exec(s_KEY_FUNC_INDEX);
				break;
			case 'd':
				Top_Panel_Method_Exec(d_KEY_FUNC_INDEX);
				break;
			case 'f':
				Top_Panel_Method_Exec(f_KEY_FUNC_INDEX);
				break;
			case 'i':
				Top_Panel_Method_Exec(i_KEY_FUNC_INDEX);
				break;
			case 'o':
				Top_Panel_Method_Exec(o_KEY_FUNC_INDEX);
				break;
			case '1':
				Top_Panel_Method_Exec(UNSELECT_FUNC_INDEX);
				break;
			case '2':
				Top_Panel_Method_Exec(UNSELECT_FUNC_INDEX);
				break;
			case '3':
				Top_Panel_Method_Exec(UNSELECT_FUNC_INDEX);
				break;
			case '4':
				Top_Panel_Method_Exec(UNSELECT_FUNC_INDEX);
				break;
			case '5':
				Top_Panel_Method_Exec(UNSELECT_FUNC_INDEX);
				break;
			case '6':
				Top_Panel_Method_Exec(UNSELECT_FUNC_INDEX);
				break;
			case KEY_BACKSPACE:
				Bottom_Panel_Method_Index(BACKSPACE_KEY_FUNC_INDEX);
				Top_Panel_Method_Exec(RE_INIT_FUNC_INDEX);
				break;
			case KEY_HOME:
				Read_Properties_From_File();
				break;
		}
	}
}
void Destruct_Menu (void)
{
	endCDK ();
}
//----------------------------------------------------------------------------------------------------
void Start_Menu_Menu 	(void)/*{{{*/
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
void Parse_Menu_Menu 	(int Selection)
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

