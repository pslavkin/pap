#include <cdk/cdk.h>
#include <panel.h>
#include <pthread.h>
#include "ncurses_pthread.h"

#include "stretcher.h"
#include "sheets.h"
#include "menu.h"
#include "histograms.h"
#include "status_bar.h"


	Sheet::Sheet()
{
	Win= 			newwin(HEIGHT, WIDTH, 0,0);
	Panel= 			new_panel(Win);
	char Buf[100];
	Redraw_Box();
	Hide=0;
	//top_panel(Panel);
	//hide_panel(Panel);
	Register_Panel(Panel,ANALOG_CLK_PROP_INDEX);	
}
void 	Sheet::Redraw_Box(void)
{
	box   	  	(Win,0,0);
	Pt_mvwprintw 	(Win,0,5,"Sheet ");
	Pt_mvwprintw 	(Win,3,getmaxx(Win)/2,"|");
}
void 	Sheet::Parser(void)
{
	unsigned char i;
	i++;
	Pt_mvwprintw 	(panel_window(panel_below(0)),3,i%WIDTH,"A");
}

void 	Sheet::Top(void)
{
	top_panel(Panel);
}
void 	Sheet::Select(void)
{
	Select_Window(Win);
}
void Sheet::Set_Panel_User_Pointer(Sheet* Ptr)
{
	set_panel_userptr 	(Panel,(void*)Ptr);
}


Sheet *Analog_Clk;
void Init_Analog_Clk(void)
{
 Analog_Clk=new Sheet();	
 Analog_Clk->Set_Panel_User_Pointer(Analog_Clk);
}
void Top_Analog_Clk(void) {Analog_Clk->Top();}
void Select_Analog_Clk(void) {Analog_Clk->Select();}
 


//----------------------------------------------------------------------------------------------------
//#define WIN_WIDTH  		49
//#define WIN_HEIGHT 		27
//
//#define STRETCHER_WIDTH  	(getmaxx(Win)-8)
//#define STRETCHER_POS_MAX 	1600
//
//#define WIN_X 			5
//#define WIN_Y 			0
////----------------------------------------------------------------------------------------------------
//static void (*Methods[]) (void) =
//{
//	Top_Panel2U,
//	Top_Panel2D,
//	Top_Panel2R,
//	Top_Panel2L,
//	Select_Stretcher,
//	Deselect_Stretcher,
//	Redraw_Stretcher_Box,
//	(void (*)())Parse_Stretcher_Menu,
//	Start_Stretcher_Menu,
//	Hide_Stretcher,
//	l_Key_Stretcher,
//	h_Key_Stretcher,
//	j_Key_Stretcher,
//	k_Key_Stretcher,
//	a_Key_Stretcher,
//	s_Key_Stretcher,
//	d_Key_Stretcher,
//	f_Key_Stretcher,
//	Re_Init_Stretcher,
//	Rien,
//	Rien,
//	Rien,
//	Top_Panel_Full_Screen,
//	(void (*)())Set_Stretcher_Props,
//	(void (*)())Read_Stretcher_Props,
//};
//static WINDOW 			*Win;
//static PANEL 			*Panel; 
//static unsigned short int	Hide 			= 1;
//static float 			Pos;
//static struct Struct_Histo 	Histo;
//static pthread_t 		PT_Stretcher_Rti;
//pthread_mutex_t Stretcher_Mutex = PTHREAD_MUTEX_INITIALIZER;
////----------------------------------------------------------------------------------------------------
//void 	Redraw_Stretcher_Box(void)
//{
//	box   	  	(Win,0,0);
//	Pt_mvwprintw 	(Win,0,5,"Stretcher ");
//	Pt_mvwprintw 	(Win,3,getmaxx(Win)/2,"|");
//}
//void Init_Stretcher(void)
//{
//	Pos=0;
//	Win= 			newwin(WIN_HEIGHT, WIN_WIDTH, 0,0);
//	Panel= 			new_panel(Win);
//	set_panel_userptr 	(Panel,Methods);
//	pthread_create 		(&PT_Stretcher_Rti, NULL, Stretcher_Rti, NULL);
//	Re_Init_Stretcher();
//	hide_panel(Panel);
//	Register_Panel(Panel,STRETCHER_PROP_INDEX);	
//}
//void Re_Init_Stretcher(void)
//{
//	Init_Histogram 		(&Histo,	Win, 1,3,"Avance",STRETCHER_POS_MAX, 0, STRETCHER_WIDTH);	
//	Redraw_Stretcher_Box();
//	Hide=0;
//}
//void* Stretcher_Rti(void* Arg1)
//{
//	static char Left_Or_Rigth=1;
//	struct timespec req={0,STRETCHER_RTI};
//	while(1) {
//	 	nanosleep(&req,&req);
//		Pos=Pos+Left_Or_Rigth;
//			if(Pos>STRETCHER_POS_MAX) 	{Pos=STRETCHER_POS_MAX;Left_Or_Rigth=-1;}
//		else 	if(Pos<0) 			{Pos=0;Left_Or_Rigth=1;}
//   		Set_Stretcher_Pos(Pos);
//	}
//}
//void Destroy_Stretcher(void)
//{
//	pthread_exit(&PT_Stretcher_Rti);
//	del_panel(Panel); 	
//}
//void Bottom_Stretcher 		(void) {bottom_panel(Panel);}
//void Top_Stretcher 		(void) {top_panel   (Panel);}
//void Select_Stretcher   	(void) {Select_Panel(Panel);Re_Init_Stretcher();}
//void Deselect_Stretcher 	(void) {Deselect_Panel(Panel);}
//void Hide_Stretcher 		(void) {hide_panel(Panel); 	Hide=1;}
//
//void f_Key_Stretcher(void) { }
//void a_Key_Stretcher(void) { }
//void s_Key_Stretcher(void) { }
//void d_Key_Stretcher(void) { }
//
//void l_Key_Stretcher(void)
//{
//	Inc_Width_Sheet(Win); 
//}
//void h_Key_Stretcher(void)
//{
//	Dec_Width_Sheet(Win);	
//}
//void k_Key_Stretcher(void)
//{
//	Inc_Height_Sheet(Win);	
//}
//void j_Key_Stretcher(void)
//{
//	Dec_Height_Sheet(Win);	
//}
//void Set_Stretcher_Props(struct Struct_Sheets_Prop *S)
//{
//	Set_Panel_Prop(Panel,S);
//}
//void Read_Stretcher_Props(struct Struct_Sheets_Prop *S)
//{
//	S->Hide=Hide;
//	Read_Panel_Prop(Panel,S);
//}
////----------------------------------------------------------------------------------------------------
//void Start_Stretcher_Menu 	(void)/*{{{*/
//{
//	int 			Submenu_Size[]={3,4},Menu_Loc[2]={LEFT,RIGHT};
//	const char	 	*Menu_List[][MAX_SUB_ITEMS]= { 
//					{
//						"</B>File<!B>",
//						"</B>Save<!B>",
//						"</B>Exit<!B>",
//					},
//					{
//						"</B>Help<!B>",
//						"</B>On Edit <!B>",
//						"</B>On File <!B>",
//						"</B>About...<!B>",
//					},
//				};
//	Set_Menu (Panel,Menu_List,2,Submenu_Size,Menu_Loc);
//}
//void Parse_Stretcher_Menu 	(int Selection)
//{
//	switch(Selection) {	
//		case 000:
//			break;
//		case 001:
//			Destroy_Sheets();
//			break;
//		}
//}/*}}}*/
////----------------------------------------------------------------------------------------------------
