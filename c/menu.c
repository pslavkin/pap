#include <cdk/cdk.h>
#include <menu.h>
#include <pthread.h>
#include <panel.h>
#include "ncurses_pthread.h"

#include "sheets.h"
#include "screen_update.h"
#include "analog_clk.h"

//----------------------------------------------------------------------------------------------------
pthread_t 		PT_Menu_Rti;
static WINDOW 		*Scr_Win;
static PANEL 		*Scr_Panel;
//----------------------------------------------------------------------------------------------------
void Init_Menu (void)
{
	Scr_Win=initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	//initCDKColor ();
	Init_Super_Colours(1,1,0,  0,192);
	curs_set(0);
	pthread_create 		(&PT_Menu_Rti, NULL, Menu_Rti, NULL);
}
void Init_Super_Colours(unsigned char R,unsigned char G,unsigned char B,unsigned char From, unsigned char Count)
{
	unsigned short int i,Bg,Pair;
	Pair=MIN_COLOUR_PAIR+From; 		//los primeros 64 se los regalo a CDK en su llamada a initCDKColor
	Bg=16+From;				//cdk usa solo 8 colores... me agarro el resto (parece que tambien usa el 15...raaaro)
	for(i=1;i<Count;i++) 	{ 	 	//no me puedo pasar de 255 pares... no da mas la funcion PAIR_NUMBER.. si no fuera por eso podria seguir...
		init_pair (Pair,255,Bg); 	
		init_color(Bg,(i*1000/Count)*R,(i*1000/Count)*G,(i*1000/Count)*B);
		Bg++;
		Pair++;
	}
}
//----------------------------------------------------------------------------------------------------
void Set_Menu (PANEL* Panel,const char* Menu_List[][MAX_SUB_ITEMS],unsigned char Items,int* Submenu_Size,int *Menu_Loc)
{
	unsigned short int	Selection;
	CDKSCREEN *Cdk		=initCDKScreen 		(panel_window(Panel));
	CDKMENU *Menu		=newCDKMenu 		(Cdk, Menu_List, Items, Submenu_Size, Menu_Loc, TOP, A_UNDERLINE, A_REVERSE); 
 	Selection 	=activateCDKMenu 	(Menu,0); 
	if (Menu->exitType == vNORMAL) 
		Rien();//		((void (**)(int))panel_userptr(panel_below(0)))[PARSE_MENU_OPTIONS_FUNC_INDEX](Selection);
	destroyCDKMenu 		(Menu);
	destroyCDKScreen 	(Cdk);
	//((void (**)())panel_userptr(panel_below(0)))[REDRAW_BOX_FUNC_INDEX]();
}
char* Set_File_Select (PANEL* Panel)
{
	char 				*File_Name;
	static char 			New_File_Name[1000];
	CDKSCREEN 	*Cdk		=initCDKScreen (panel_window(Panel));
	CDKFSELECT 	*File_Select 	=newCDKFselect (Cdk,CENTER,CENTER,20,65,"Select File","",A_NORMAL,'_', A_REVERSE,"</5>","</48>","</N>","</N>",TRUE,FALSE);
	
   	File_Name = copyChar(activateCDKFselect(File_Select,0));
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
   	Info=activateCDKEntry(Entry, 0);
  	if (Entry->exitType == vNORMAL) {
		Ans=0;
		strcpy(Data,Info);
	}
   	destroyCDKEntry 	(Entry);
	destroyCDKScreen 	(Cdk);
	return Ans;
}

//-------------------------------------------------------------------
Sheet* Sheet4Top_Panel(void)
{
	return Sheet4Panel(panel_below(0));	
}
Sheet* Sheet4Panel(PANEL* Panel)
{
	return (Sheet*)(panel_userptr(Panel));
}
WINDOW* Scr_Window(void)	{return Scr_Win;}
void Touch_Scr_Window(void)	{touchwin(Scr_Win);}
//-------------------------------------------------------------------
void* Menu_Rti(void* Arg1)
{
	struct timespec req={0,1000000};
	int Selection,Key;
	while(1) {
	 	nanosleep(&req,&req);
		Key=getch();
		switch(Key) {	
			case KEY_F1:
			case ' ':
				break;
			case KEY_F2:
				break;
			case KEY_F3:
				Sheet4Top_Panel()->Deselect();
				Top_Analog_Clk();
				Sheet4Top_Panel()->Select();
				break;
			case KEY_F4:
				Sheet4Top_Panel()->Deselect();
				Top_Analog_Clk1();
				Sheet4Top_Panel()->Select();
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
				Sheet4Top_Panel()->Hide();
				break;
			case KEY_F10:
				break;
			case KEY_F11:
				Sheet4Top_Panel()->Full_Screen();
				break;
			case KEY_UP:
				Sheet4Top_Panel()->To_Up();
				break;
			case KEY_DOWN:
				Sheet4Top_Panel()->To_Down();
				break;
			case KEY_RIGHT:
				Sheet4Top_Panel()->To_Right();
				break;
			case KEY_LEFT:
				Sheet4Top_Panel()->To_Left();
				break;
			case 'l':
				Sheet4Top_Panel()->Inc_Width();
				break;
			case 'h':
				Sheet4Top_Panel()->Dec_Width();
				break;
			case 'j':
				Sheet4Top_Panel()->Inc_Height();
				break;
			case 'k':
				Sheet4Top_Panel()->Dec_Height();
				break;
			case KEY_BACKSPACE:
				break;
			case KEY_HOME:
				break;
			case KEY_ESC:
				exit(0);
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
//	Set_Menu (Panel,Menu_List,2,Submenu_Size,Menu_Loc);
}
void Parse_Menu_Menu 	(int Selection)
{
	switch(Selection) {	
		case 000:
			break;
		case 001:
			break;
		}
}/*}}}*/
//----------------------------------------------------------------------------------------------------

