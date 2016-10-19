#ifndef MENU
#define MENU

#include <panel.h>



extern void 		Init_Menu 		(void);
extern void 		Start_Menu_Menu		(void);
extern void 		Parse_Menu_Menu		(int Selection);
extern void 		Destruct_Menu 		(void);
extern void* 		Menu_Rti 		(void* Arg1);
extern unsigned char 	Set_Entry 		(PANEL* Panel,const char* Title,char* Actual_Data,char* Data,unsigned short int Length);
extern char* 		Set_File_Select 	(PANEL* Panel);
extern void 		Set_Slider 		(PANEL* Panel,unsigned int* Sel,unsigned int Min,unsigned int Max,unsigned int Fine_Step);
extern void 		Set_Menu 		(PANEL* Panel,const char* Menu_List[][MAX_SUB_ITEMS],unsigned char Items,int* Submenu_Size,int *Menu_Loc);
extern void 		Redraw_Menu_Box 	(void);
extern void 		Bottom_Menu 		(void); 
extern void 		Top_Menu 		(void); 
extern void 		Select_Menu   		(void); 
extern void 		Deselect_Menu 		(void); 
extern void 		Hide_Menu 		(void); 
#endif

