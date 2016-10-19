#ifndef STATUS_BAR
#define STATUS_BAR

extern void 	Init_Status_Bar 			(void);
extern void 	Start_Status_Bar_Menu 			(void);
extern void 	Parse_Status_Bar_Menu			(int Selection);
extern void 	Redraw_Status_Bar_Box 			(void);
extern void 	Start_Status_Bar_Menu 			(void);
extern void* 	Status_Bar_Rti 				(void* Arg1);
extern void 	Destroy_Status_Bar 			(void);
extern void 	Print_Status_Bar_Data 			(const char *D,...);
extern void 	Print_Status_Bar_Hex_Data 		(const char *D,unsigned short int Length);
extern void 	Add_Status_Bar_Data 			(char *Data,unsigned int Length);
extern void 	Bottom_Status_Bar 			(void);
extern void 	Top_Status_Bar 				(void);
extern void 	Set_Status_Bar_Props 			(struct Struct_Sheets_Prop *S);
extern void 	Read_Status_Bar_Props 			(struct Struct_Sheets_Prop *S);
extern void 	Status_Bar_Panel2U 			(void);
extern void 	Status_Bar_Panel2D 			(void);
extern void 	Status_Bar_Panel2R 			(void);
extern void 	Status_Bar_Panel2L 			(void);
extern void 	Reposition_Status_Bar_Log_Panel 	(void);
extern void 	Select_Status_Bar 			(void);
extern void 	Deselect_Status_Bar 			(void);
extern void 	Full_Screen_Status_Bar 			(void);
extern void 	Hide_Status_Bar 			(void); 
extern void 	l_Key_Status_Bar 			(void);
extern void 	h_Key_Status_Bar 			(void);
extern void 	j_Key_Status_Bar 			(void);
extern void 	k_Key_Status_Bar 			(void);
extern void 	a_Key_Status_Bar 			(void);
extern void 	s_Key_Status_Bar 			(void);
extern void 	d_Key_Status_Bar 			(void);
extern void 	f_Key_Status_Bar 			(void);
extern void 	Re_Init_Status_Bar 			(void);
extern void 	Reposition_Status_Bar_Log_Panel 	(void);
//----------------------------------------------------------------------------------------------------

#endif
