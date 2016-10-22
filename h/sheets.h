#ifndef SHEETS
#define SHEETS

#include <panel.h>

#define MIN_COLOUR_PAIR         65
#define MAX_COLOUR_PAIR         255

#define MIN_WIDTH         	10
#define MIN_HEIGHT		10

extern void 		Init_Sheets 			(void);
extern void 		Init_Super_Colours 		(unsigned char R,unsigned char G,unsigned char B,unsigned char From, unsigned char Count);
//---------------------------------------------------------------------------------------------------
extern void 		Start_Scr_Menu 			(void);
extern void 		Parse_Scr_Menu 			(int Selection);
extern void 		Redraw_Scr_Box 			(void);
//---------------------------------------------------------------------------------------------------
class Sheet{
public:
	WINDOW 			*Win;
	PANEL 			*Panel; 
	char Name[100];

			Sheet				();
	void 		Redraw_Box			(void);
	void 		Hide_Box			(void);
	void 		Set_Name			(char* Sheet_Name);
	void 		Set_Size			(unsigned short int Height,unsigned short int Width);
	void 		Set_Pos				(unsigned short int Y,unsigned short int X);
	void 		To_Up				(void);
	void 		To_Down				(void);
	void 		To_Right			(void);
	void 		To_Left				(void);
	void 		Inc_Width			(void);
	void 		Dec_Width			(void);
	void 		Inc_Height			(void);
	void 		Dec_Height			(void);
	void 		Full_Screen			(void);
	void 		Hide				(void);
	void 		Unhide				(void);
	void 		Top				(void);
	void 		Bottom				(void);
	void 		Select				(void);
	void 		Deselect			(void);
	void 		Set_Panel_User_Pointer		(Sheet* Ptr);
	void 		Touch_Win			(void);
	 		~Sheet				(void);
private:
	void 		Move_Panel			(PANEL* Panel,unsigned short int Y,unsigned short int X);
};

#endif
