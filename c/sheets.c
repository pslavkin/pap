#include <cdk/cdk.h>
#include <panel.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "screen_update.h"
#include "status_bar.h"
#include "ncurses_pthread.h"

#include "sheets.h"
#include "menu.h"


#include "stretcher.h"
#include "multichannel.h"

#define 	WIDTH  	49
#define 	HEIGHT 	27
#define  	WIN_X 	10
#define  	WIN_Y 	0
//----------------------------------------------------------------------------------------------------
static WINDOW 			*Win,*Scr_Win;
static PANEL 			*Panel,*Scr_Panel;
static pthread_t 		PT_Sheets_Rti,PT_Scr_Rti;
static FILE 			*File 			= NULL;
static PANEL 			*Sheet_List[MAX_PANELS]={NULL};
static unsigned short int	Hide 			= 1;
pthread_mutex_t 		Sheets_Mutex = PTHREAD_MUTEX_INITIALIZER;
static void (*Methods[]) (void) =
{
	Top_Panel2U,
	Top_Panel2D,
	Top_Panel2R,
	Top_Panel2L,
	Select_Sheets,
	Deselect_Sheets,
	Redraw_Sheets_Box,
	(void (*)())Parse_Sheet_Menu,
	Start_Sheet_Menu,
	Hide_Sheet,
	Top_Inc_Width_Sheet,
	Top_Dec_Width_Sheet,
	Top_Inc_Height_Sheet,
	Top_Dec_Height_Sheet,
	a_Key_Sheets,
	s_Key_Sheets,
	d_Key_Sheets,
	f_Key_Sheets,
	Re_Init_Sheets,
	Rien,
	Rien,
	Rien,
	Top_Panel_Full_Screen,
	(void (*)())Set_Sheets_Props,
	(void (*)())Read_Sheets_Props,
};
static void (*Scr_Methods[]) (void) =
{
	Rien,
	Rien,
	Rien,
	Rien,
	Rien,
	Rien,
	Redraw_Scr_Box,
	(void (*)())Parse_Scr_Menu,
	Start_Scr_Menu,
	Rien,
	Rien,
	Rien,
	Rien,
	Rien,
	Rien,
	Rien,
	Rien,
	Rien,
	Rien,
	Redraw_Scr_Box,
	Rien,
	Rien,
	Rien,
	Top_Panel_Full_Screen,
};
//----------------------------------------------------------------------------------------------------
void 	Redraw_Scr_Box(void)
{
	pthread_mutex_lock(&Screen_Update_Mutex);	
		wclear 		(Scr_Win);
		box   	  	(Scr_Win,0,0);
		mvwprintw 	(Scr_Win,0,5,"DCI ");
	pthread_mutex_unlock(&Screen_Update_Mutex);	
}
void 	Redraw_Sheets_Box(void)
{
	pthread_mutex_lock(&Screen_Update_Mutex);	
		box   	  	(Win,0,0);
		mvwprintw 	(Win,0,5,"sheets ");
	pthread_mutex_unlock(&Screen_Update_Mutex);	
	Hide=0;
}
void Init_Sheets(void)
{
	Scr_Win=initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	initCDKColor ();
	Init_Super_Colours(1,1,0,  0,192);
	curs_set(0);
	Scr_Panel= new_panel(Scr_Win);
	set_panel_userptr(Scr_Panel,Scr_Methods);
	Redraw_Scr_Box();
	pthread_create(&PT_Sheets_Rti, NULL, Scr_Rti, NULL);

	Win	= newwin(HEIGHT, WIDTH, WIN_Y,WIN_X);
	Panel	= new_panel(Win);
	hide_panel(Panel);
	Redraw_Sheets_Box();
	set_panel_userptr(Panel,Methods);
	pthread_create(&PT_Sheets_Rti, NULL, Sheets_Rti, NULL);
	Change_Sheets_File((char*)"./.config");
	Register_Panel(Panel,SHEETS_PROP_INDEX);	
}
void Re_Init_Sheets(void)
{
	Redraw_Sheets_Box();

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
void* Sheets_Rti(void* Arg1)
{
	struct timespec req={0,SHEETS_RTI};
	while(1) {
	 	nanosleep(&req,&req);
	}
}
void* Scr_Rti(void* Arg1)
{
	struct timespec req={0,SCR_RTI};
	while(1) {
	 	nanosleep(&req,&req);
	//	Redraw_Scr_Box(); ///me mete un flikeo .mejor lo asigno a una opcion de menu...y  ya....
	}
}

void Destroy_Sheets(void)
{
//	pthread_exit(&PT_Sheets_Rti);
	delwin(Win);
	endwin();
	endCDK ();
	exit(0);
}

void Bottom_Sheets 	(void) {Pt_Bottom_Panel(Panel);}
void Top_Sheets 	(void) {Pt_Top_Panel   (Panel);}
void Select_Sheets   	(void) {Select_Panel(Panel);}
void Deselect_Sheets 	(void) {Deselect_Panel(Panel);}
void Hide_Sheet 	(void) {Pt_Hide_Panel(Panel); Hide=1;}
//----------------------------------------------------------------------------------------------------
void Select_Window		(WINDOW* Win)
{
	pthread_mutex_lock(&Screen_Update_Mutex);	
			mvwaddch(Win,1,1,'*'|A_BOLD);
	pthread_mutex_unlock(&Screen_Update_Mutex);	
}
void Select_Panel		(PANEL* Panel)
{
	pthread_mutex_lock(&Screen_Update_Mutex);	
			mvwaddch(panel_window(Panel),1,1,'*'|A_BOLD);
	pthread_mutex_unlock(&Screen_Update_Mutex);	
}
void Deselect_Panel		(PANEL* Panel)
{
	pthread_mutex_lock(&Screen_Update_Mutex);	
			mvwaddch(panel_window(Panel),1,1,' '|A_NORMAL);
	pthread_mutex_unlock(&Screen_Update_Mutex);	
}
//----------------------------------------------------------------------------------------------------
void Pt_Resize_Window		(WINDOW* Win,unsigned short int Height,unsigned short int Width)
{
	pthread_mutex_lock(&Screen_Update_Mutex);	
		wresize(Win,Height,Width);
	pthread_mutex_unlock(&Screen_Update_Mutex);	
}
void Move_Panel		(PANEL* Panel,unsigned short int Y,unsigned short int X)
{
	pthread_mutex_lock(&Screen_Update_Mutex);	
		move_panel(Panel,Y,X);
	pthread_mutex_unlock(&Screen_Update_Mutex);	
}
void Top_Panel2U	(void)
{
	Panel2U(panel_below(0));
}
void Top_Panel2D	(void)
{
	Panel2D(panel_below(0));
}
void Top_Panel2R	(void)
{
	Panel2R(panel_below(0));
}
void Top_Panel2L	(void)
{
	Panel2L(panel_below(0));
}
void Panel2U	(PANEL* Panel)
{
	Move_Panel(Panel,getbegy(panel_window(Panel))-1,getbegx(panel_window(Panel)));
}
void Panel2D	(PANEL* Panel)
{
	Move_Panel(Panel,getbegy(panel_window(Panel))+1,getbegx(panel_window(Panel)));
}
void Panel2R	(PANEL* Panel)
{
	Move_Panel(Panel,getbegy(panel_window(Panel)),getbegx(panel_window(Panel))+1);
}
void Panel2L	(PANEL* Panel)
{
	Move_Panel(Panel,getbegy(panel_window(Panel)),getbegx(panel_window(Panel))-1);
}
void Top_Panel_Full_Screen	(void)
{
	Panel_Full_Screen(panel_below(0));
	Top_Panel_Method_Exec(RE_INIT_FUNC_INDEX);
}
void Set_Panel_Prop	(PANEL* Panel, struct Struct_Sheets_Prop *S)
{
	if(S->Hide) hide_panel(Panel); 
	else top_panel(Panel);
	wresize(panel_window(Panel),S->Height,S->Width);
	Move_Panel(Panel,S->Y,S->X);
	wclear(panel_window(Panel));
	if(!S->Hide) Panel_Method_Exec(Panel,RE_INIT_FUNC_INDEX);
}
void Read_Panel_Prop	(PANEL* Panel, struct Struct_Sheets_Prop *S)
{
	S->Y 		=getbegy(panel_window(Panel));
	S->X 		=getbegx(panel_window(Panel));
	S->Height 	=getmaxy(panel_window(Panel));
	S->Width 	=getmaxx(panel_window(Panel));
}
void Panel_Full_Screen	(PANEL* Panel)
{
	pthread_mutex_lock(&Screen_Update_Mutex);	
		wclear(panel_window(Panel));
		move_panel(Panel,getbegy(Scr_Win),getbegx(Scr_Win));
		wresize(panel_window(Panel),getmaxy(Scr_Win),getmaxx(Scr_Win));
	pthread_mutex_unlock(&Screen_Update_Mutex);	
}
void Pt_Panel_Full_Screen	(PANEL* Panel)
{
	pthread_mutex_lock(&Screen_Update_Mutex);	
		wclear(panel_window(Panel));
		move_panel(Panel,getbegy(Scr_Win),getbegx(Scr_Win));
		wresize(panel_window(Panel),getmaxy(Scr_Win),getmaxx(Scr_Win));
	pthread_mutex_unlock(&Screen_Update_Mutex);	
}
void Pt_Top_Panel		(PANEL* Panel)
{
	pthread_mutex_lock(&Screen_Update_Mutex);	
		top_panel(Panel);
	pthread_mutex_unlock(&Screen_Update_Mutex);	
}
void Pt_Bottom_Panel		(PANEL* Panel)
{
	pthread_mutex_lock(&Screen_Update_Mutex);	
		bottom_panel(Panel);
	pthread_mutex_unlock(&Screen_Update_Mutex);	
}
void Pt_Hide_Panel		(PANEL* Panel)
{
	pthread_mutex_lock(&Screen_Update_Mutex);	
		hide_panel(Panel);
	pthread_mutex_unlock(&Screen_Update_Mutex);	
}
void f_Key_Sheets(void) { }
void a_Key_Sheets(void) { }
void s_Key_Sheets(void) { }
void d_Key_Sheets(void) { }

void l_Key_Sheets(void)
{
	Inc_Width_Sheet(Win); 
}
void h_Key_Sheets(void)
{
	Dec_Width_Sheet(Win);	
}
void k_Key_Sheets(void)
{
	Inc_Height_Sheet(Win);	
}
void j_Key_Sheets(void)
{
	Dec_Height_Sheet(Win);	
}
void Inc_Width_Sheet(WINDOW* Win)
{
	if((getmaxx(Win)+getbegx(Win))<getmaxx(stdscr)) {
		pthread_mutex_lock(&Screen_Update_Mutex);	
			wclear(Win);
			wresize(Win,getmaxy(Win),getmaxx(Win)+1);
		pthread_mutex_unlock(&Screen_Update_Mutex);	
		Top_Panel_Method_Exec(RE_INIT_FUNC_INDEX);
	}
}
void Dec_Width_Sheet(WINDOW* Win)
{
	if(getmaxx(Win)>MIN_WIDTH) {
		
		pthread_mutex_lock(&Screen_Update_Mutex);	
			wclear(Win);
			wresize(Win,getmaxy(Win),getmaxx(Win)-1);
		pthread_mutex_unlock(&Screen_Update_Mutex);	
		Top_Panel_Method_Exec(RE_INIT_FUNC_INDEX);
	}
}
void Inc_Height_Sheet(WINDOW* Win)
{
	if((getmaxy(Win)+getbegy(Win))<getmaxy(stdscr)) {
		pthread_mutex_lock(&Screen_Update_Mutex);	
			wclear(Win);
			wresize(Win,getmaxy(Win)+1,getmaxx(Win));
		pthread_mutex_unlock(&Screen_Update_Mutex);	
		Top_Panel_Method_Exec(RE_INIT_FUNC_INDEX);
	}
}
void Dec_Height_Sheet(WINDOW* Win)
{
	if(getmaxy(Win)>MIN_HEIGHT) {
		pthread_mutex_lock(&Screen_Update_Mutex);	
			wclear(Win);
			wresize(Win,getmaxy(Win)-1,getmaxx(Win));
		pthread_mutex_unlock(&Screen_Update_Mutex);	
		Top_Panel_Method_Exec(RE_INIT_FUNC_INDEX);
	}
}
void Top_Inc_Width_Sheet(void)
{
	Inc_Width_Sheet(panel_window(panel_below(0)));
}
void Top_Dec_Width_Sheet(void) 
{
	Dec_Width_Sheet(panel_window(panel_below(0)));
}
void Top_Inc_Height_Sheet(void)
{
	Inc_Height_Sheet(panel_window(panel_below(0)));
}
void Top_Dec_Height_Sheet(void)
{
	Dec_Height_Sheet(panel_window(panel_below(0)));
}


void Register_Panel(PANEL* Panel,unsigned short Index)
{
	Sheet_List[Index]=Panel;	
}
void Change_Sheets_File(char* File_Name)
{
	FILE *New_File,*Old_File;
	New_File = fopen(File_Name,"r+");
	if(New_File==NULL) 	New_File = fopen(File_Name,"w+");
	if(New_File !=NULL) {
		Old_File=File;
		File=New_File;
		if(Old_File!=NULL) fclose(Old_File);
		//Print_Status_Bar_Data("Sheets Config file=%s\n",File_Name);
	}
}
void Panel_Prop_Method_Exec(struct Struct_Sheets_Prop *S,unsigned char Func_Index)
{
	((void (**)(struct Struct_Sheets_Prop *))panel_userptr(Sheet_List[S->Index]))[Func_Index](S);
}
void Panel_Prop_Set_Method_Exec(struct Struct_Sheets_Prop *S)
{
	Panel_Prop_Method_Exec(S,SET_PROPERTIES_FUNC_INDEX);
}
void Panel_Prop_Read_Method_Exec(struct Struct_Sheets_Prop *S)
{
	Panel_Prop_Method_Exec(S,READ_PROPERTIES_FUNC_INDEX);
}
void Read_Properties_From_File(void)
{
	if(File!=NULL) {
		struct Struct_Sheets_Prop S;
		unsigned short int i;
		for(rewind(File),i=0;i<MAX_PROP_PANELS && fread(&S,sizeof(Struct_Sheets_Prop),1,File)!=EOF;i++) {
		        Panel_Prop_Set_Method_Exec(&S);
			//Print_Status_Bar_Data("prop=%d %d %d %d %d %d\n ",S.Index,S.X,S.Y,S.Height,S.Width, S.Hide); 
			Panel_Prop_Method_Exec(&S,UNSELECT_FUNC_INDEX);
			
		}
	}
	else Print_Status_Bar_Data("can't open config file \n");
}
void Save_Properties_To_File(void)
{
	if(File!=NULL) {
		struct Struct_Sheets_Prop S;
		unsigned short int i;
		for(rewind(File),i=0;i<MAX_PROP_PANELS;i++) {
			S.Index=i;
		        Panel_Prop_Read_Method_Exec(&S);
			fwrite(&S,sizeof(Struct_Sheets_Prop),1,File);	
			//Print_Status_Bar_Data("prop=%d %d %d %d %d %d\n ",S.Index,S.X,S.Y,S.Height,S.Width, S.Hide); 
		}
	}
	else Print_Status_Bar_Data("can't open config file \n");
}
void Set_Sheets_Props(struct Struct_Sheets_Prop *S)
{
	Set_Panel_Prop(Panel,S);
}
void Read_Sheets_Props(struct Struct_Sheets_Prop *S)
{
	S->Hide=Hide;
	Read_Panel_Prop(Panel,S);
}
//----------------------------------------------------------------------------------------------------
void Start_Sheet_Menu 	(void)/*{{{*/
{
	int 			Submenu_Size[]={5,2,4},Menu_Loc[]={LEFT,LEFT,RIGHT};
	const char 		*Menu_List[][MAX_SUB_ITEMS]= { 
					{
						"</B>File<!B>",
						"</B>Select Config File<!B>",
						"</B>Load Config<!B>",
						"</B>Save Config<!B>",
						"</B>Exit<!B>",
					},
					{
						"</B>Refresher<!B>",
						"</B>Tic<!B>",
					},
					{
						"</B>Help<!B>",
						"</B>On Edit <!B>",
						"</B>On File <!B>",
						"</B>About...<!B>",
					},
				};
	Set_Menu (Panel,Menu_List,3,Submenu_Size,Menu_Loc);
	Re_Init_Sheets();	
}
void Parse_Sheet_Menu 	(int Selection)
{
	switch(Selection) {	
		case 000:
			Change_Sheets_File(Set_File_Select(Panel));
			break;
		case 001:
			Read_Properties_From_File();
			break;
		case 002:
			Save_Properties_To_File();
			break;
		case 003:
			Destroy_Sheets();
			break;
		case 100: {
			unsigned int Ans=Read_Screen_Update_Rti_Delay()/1000000;
			Set_Slider(Panel,(unsigned int*)&Ans,10,999,1);
			Set_Screen_Update_Rti_Delay(Ans*1000000);
			break;
			}
		}
}
//----------------------------------------------------------------------------------------------------
void Start_Scr_Menu 	(void)
{
	int 			Submenu_Size[]={3,10,2,4},Menu_Loc[]={LEFT,LEFT,LEFT,RIGHT};
	const char 		*Menu_List[][MAX_SUB_ITEMS]= { 
					{
						"</B>File<!B>",
						"</B>Save<!B>",
						"</B>Exit<!B>",
					},
					{
						"</B>Sheets<!B>",
						"</B>F2 Head<!B>",
						"</B>F4 Stretcher<!B>",
						"</B>F5 Log<!B>",
						"</B>F7 Sheets<!B>",
						"</B>F8 Multichannel<!B>",
						"</B>F9 Hide<!B>",
						"</B>F10 Unselect<!B>",
						"</B>F11 Full Screen<!B>",
					},
					{
						"</B>Screen<!B>",
						"</B>Refresh<!B>",
					},
					{
						"</B>Help<!B>",
						"</B>On Edit <!B>",
						"</B>On File <!B>",
						"</B>About Cuipet...<!B>",
					},
				};
	Set_Menu (Scr_Panel,Menu_List,3,Submenu_Size,Menu_Loc);
}
void Parse_Scr_Menu 	(int Selection)
{
	switch(Selection) {	
		case 000:
			break;
		case 001:
			Destroy_Sheets();
			break;
		case 100:
			Top_Panel_Method_Exec(UNSELECT_FUNC_INDEX);
			break;
		case 101:
			Top_Panel_Method_Exec(UNSELECT_FUNC_INDEX);
			break;
		case 102:
			Top_Panel_Method_Exec(UNSELECT_FUNC_INDEX);
			Top_Stretcher();
			Select_Stretcher();
			break;
		case 103:
			Top_Panel_Method_Exec(UNSELECT_FUNC_INDEX);
			Top_Status_Bar();
			Select_Status_Bar();
			break;
		case 104:
			Top_Panel_Method_Exec(UNSELECT_FUNC_INDEX);
			break;
		case 105:
			Top_Panel_Method_Exec(UNSELECT_FUNC_INDEX);
			Top_Sheets();
			Select_Sheets();
			break;
		case 106:
			Top_Panel_Method_Exec(UNSELECT_FUNC_INDEX);
			Select_Menu();
			break;
		case 107:
			Top_Panel_Method_Exec(HIDE_FUNC_INDEX);
			break;
		case 200:
			Redraw_Scr_Box();
			break;
		}
}/*}}}*/








	Sheet::Sheet()
{
	Win= 			newwin(1, 1, 0,0);
	Panel= 			new_panel(Win);
}
void 	Sheet::Redraw_Box(void)
{
	box   	  	(Win,0,0);
	Pt_mvwprintw 	(Win,0,5,Name);
}
void 	Sheet::Set_Name(char* Sheet_Name)
{
	strcpy(Name,Sheet_Name);	
}
void 	Sheet::Set_Size(unsigned short int Height,unsigned short int Width)
{
	Pt_Resize_Window(Win,Height,Width);
}
void 	Sheet::To_Up(void)
{
	Move_Panel(Panel,getbegy(Win)-1,getbegx(Win));
}
void 	Sheet::To_Down(void)
{
	Move_Panel(Panel,getbegy(Win)+1,getbegx(Win));
}
void 	Sheet::To_Right(void)
{
	Move_Panel(Panel,getbegy(Win),getbegx(Win)+1);
}
void 	Sheet::To_Left(void)
{
	Move_Panel(Panel,getbegy(Win),getbegx(Win)-1);
}
void 	Sheet::Inc_Width(void)
{
	pthread_mutex_lock(&Screen_Update_Mutex);	
		if((getmaxx(Win)+getbegx(Win))<getmaxx(stdscr)) {
				wclear(Win);
				wresize(Win,getmaxy(Win),getmaxx(Win)+1);
		}
	pthread_mutex_unlock(&Screen_Update_Mutex);	
	Redraw_Box();
}
void 	Sheet::Dec_Width(void)
{
	pthread_mutex_lock(&Screen_Update_Mutex);	
		if(getmaxx(Win)>MIN_WIDTH) {
			wclear(Win);
			wresize(Win,getmaxy(Win),getmaxx(Win)-1);
		}
	pthread_mutex_unlock(&Screen_Update_Mutex);	
	Redraw_Box();
}
void 	Sheet::Inc_Height(void)
{
	pthread_mutex_lock(&Screen_Update_Mutex);	
		if((getmaxy(Win)+getbegy(Win))<getmaxy(stdscr)) {
				wclear(Win);
				wresize(Win,getmaxy(Win)+1,getmaxx(Win));
		}
	pthread_mutex_unlock(&Screen_Update_Mutex);	
	Redraw_Box();
}
void 	Sheet::Dec_Height(void)
{
	pthread_mutex_lock(&Screen_Update_Mutex);	
		if(getmaxy(Win)>MIN_HEIGHT) {
				wclear(Win);
				wresize(Win,getmaxy(Win)-1,getmaxx(Win));
		}
	pthread_mutex_unlock(&Screen_Update_Mutex);	
	Redraw_Box();
}
void 	Sheet::Set_Pos(unsigned short int Y,unsigned short int X)
{
	Move_Panel(Panel,Y,X);
}
void 	Sheet::Hide(void)
{
	hide_panel(Panel);
}
void 	Sheet::Unhide(void)
{
	show_panel(Panel);
}
void 	Sheet::Top(void)
{
	top_panel(Panel);
	Select_Window(Win);
}
void 	Sheet::Select(void)
{
	Select_Window(Win);
}
void 	Sheet::Full_Screen(void)
{
	Pt_Panel_Full_Screen(Panel);
	Sheet::Redraw_Box();
}
void Sheet::Set_Panel_User_Pointer(Sheet* Ptr)
{
	set_panel_userptr 	(Panel,(void*)Ptr);
}


