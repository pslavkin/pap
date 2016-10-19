#ifndef SHEETS
#define SHEETS

#include <panel.h>

#define MIN_COLOUR_PAIR         65
#define MAX_COLOUR_PAIR         255
  
#define MAX_PANELS 	20
#define MIN_WIDTH 	2
#define MIN_HEIGHT	2	

#define MOVE2U_FUNC_INDEX 		0
#define MOVE2D_FUNC_INDEX 		1
#define MOVE2R_FUNC_INDEX 		2
#define MOVE2L_FUNC_INDEX 		3
#define SELECT_FUNC_INDEX 		4
#define UNSELECT_FUNC_INDEX 		5
#define REDRAW_BOX_FUNC_INDEX 		6
#define PARSE_MENU_OPTIONS_FUNC_INDEX 	7
#define START_MENU_FUNC_INDEX		8
#define HIDE_FUNC_INDEX			9
#define l_KEY_FUNC_INDEX		10
#define h_KEY_FUNC_INDEX		11
#define j_KEY_FUNC_INDEX		12
#define k_KEY_FUNC_INDEX		13
#define a_KEY_FUNC_INDEX		14
#define s_KEY_FUNC_INDEX		15
#define d_KEY_FUNC_INDEX		16
#define f_KEY_FUNC_INDEX		17
#define RE_INIT_FUNC_INDEX		18
#define BACKSPACE_KEY_FUNC_INDEX	19
#define i_KEY_FUNC_INDEX		20
#define o_KEY_FUNC_INDEX		21
#define FULL_SCREEN_FUNC_INDEX		22
#define SET_PROPERTIES_FUNC_INDEX	23
#define READ_PROPERTIES_FUNC_INDEX	24
#define _1_KEY_FUNC_INDEX		25

struct Struct_Sheets_Prop 
{
	unsigned char 	 	Index;
	unsigned short int 	X;
	unsigned short int 	Y;
	unsigned short int 	Height;
	unsigned short int 	Width;
	unsigned char 		Hide;
};

#define MAX_PROP_PANELS			3 
#define STRETCHER_PROP_INDEX		0
#define STATUS_BAR_PROP_INDEX		1
#define SHEETS_PROP_INDEX		2

extern void 		Init_Sheets 			(void);
extern void 		Init_Super_Colours 		(unsigned char R,unsigned char G,unsigned char B,unsigned char From, unsigned char Count);
extern void 		Register_Panel 			(PANEL* Panel,unsigned short Index);
extern void 		Re_Init_Sheets 			(void);
extern void 		Start_Sheet_Menu 		(void);
extern void 		Parse_Sheet_Menu		(int Selection);
extern void* 		Sheets_Rti 			(void* Arg1);
extern void* 		Scr_Rti 			(void* Arg1);
extern void 		Destroy_Sheets 			(void);
extern void 		Read_Properties_From_File 	(void);
extern void 		Change_Sheets_File 		(char* File_Name);
extern void 		Bottom_Sheets 			(void);
extern void 		Top_Sheets 			(void);
extern void 		Select_Sheets 			(void);
extern void 		Deselect_Sheets 		(void);
extern void 		Hide_Sheet 			(void); 
extern void 		Redraw_Sheets_Box 		(void);
extern void 		Move_Panel			(PANEL* Panel,unsigned short int Y,unsigned short int X);
extern void 		Deselect_Panel			(PANEL* Panel);
extern void 		Select_Panel			(PANEL* Panel);
extern void 		Pt_Top_Panel			(PANEL* Panel);
extern void 		Pt_Bottom_Panel			(PANEL* Panel);
extern void 		Pt_Hide_Panel			(PANEL* Panel);
extern void 		Set_Panel_Prop			(PANEL* Panel, struct Struct_Sheets_Prop *S);
extern void 		Read_Panel_Prop			(PANEL* Panel, struct Struct_Sheets_Prop *S);
extern void 		Panel_Full_Screen		(PANEL* Panel);
extern void 		Panel_Prop_Method_Exec 		(struct Struct_Sheets_Prop *S,unsigned char Func_Index);
extern void 		Panel_Prop_Set_Method_Exec 	(struct Struct_Sheets_Prop *S);
extern void 		Panel_Prop_Read_Method_Exec 	(struct Struct_Sheets_Prop *S);
extern void 		Set_Sheets_Props 		(struct Struct_Sheets_Prop *S);
extern void 		Read_Sheets_Props 		(struct Struct_Sheets_Prop *S);
extern void 		Top_Panel_Full_Screen		(void);
extern void 		Top_Panel2R			(void);
extern void 		Top_Panel2L			(void);
extern void 		Top_Panel2U			(void);
extern void 		Top_Panel2D			(void);
extern void 		Panel2U				(PANEL* Panel);
extern void 		Panel2D				(PANEL* Panel);
extern void 		Panel2R				(PANEL* Panel);
extern void 		Panel2L				(PANEL* Panel);
extern void 		Inc_Width_Sheet  		(WINDOW* Win);
extern void 		Dec_Width_Sheet  		(WINDOW* Win);
extern void 		Inc_Height_Sheet 		(WINDOW* Win);
extern void 		Dec_Height_Sheet 		(WINDOW* Win);
extern void 		Top_Inc_Width_Sheet 		(void);
extern void 		Top_Dec_Width_Sheet 		(void);
extern void 		Top_Inc_Height_Sheet 		(void);
extern void 		Top_Dec_Height_Sheet 		(void);
extern void 		l_Key_Sheets 			(void);
extern void 		h_Key_Sheets 			(void);
extern void 		j_Key_Sheets 			(void);
extern void 		k_Key_Sheets 			(void);
extern void 		a_Key_Sheets 			(void);
extern void 		s_Key_Sheets 			(void);
extern void 		d_Key_Sheets 			(void);
extern void 		f_Key_Sheets 			(void);
//---------------------------------------------------------------------------------------------------
extern void 		Start_Scr_Menu 			(void);
extern void 		Parse_Scr_Menu 			(int Selection);
extern void 		Redraw_Scr_Box 			(void);

#endif
