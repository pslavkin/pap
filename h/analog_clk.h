#ifndef ANALOG_CLK
#define ANALOG_CLK

extern	void Init_Analog_Clk	(void);
extern	void Top_Analog_Clk	(void);
extern	void Select_Analog_Clk	(void);
extern	void Debug_Analog_Clk	(void);

class Sheet{
public:
	static const int HEIGHT=20;
	static const int WIDTH =20;

	WINDOW 			*Win;
	PANEL 			*Panel; 
	unsigned short int	Hide;

			Sheet				();
	void 		Redraw_Box			(void);
	static void 	Parser				(void);
	void 		Top				(void);
	void 		Select				(void);
	void 		Set_Panel_User_Pointer		(Sheet* Ptr);
};

//extern void 	Init_Stretcher     	(void);
//extern void 	Re_Init_Stretcher     	(void);
//extern void 	Start_Stretcher_Menu 	(void);
//extern void 	Parse_Stretcher_Menu	(int Selection);
//extern void 	Start_Stretcher_Menu 	(void);
//extern void 	Redraw_Stretcher_Box 	(void);
//extern void 	Destroy_Stretcher  	(void);
//extern void* 	Stretcher_Rti 		(void* Arg1);
//extern void 	Bottom_Stretcher 	(void); 
//extern void 	Top_Stretcher 		(void);
//extern void 	Select_Stretcher 	(void);
//extern void 	Deselect_Stretcher 	(void);
//extern void 	Set_Stretcher_Props 	(struct Struct_Sheets_Prop *S);
//extern void 	Read_Stretcher_Props 	(struct Struct_Sheets_Prop *S);
//extern void 	Hide_Stretcher 		(void); 
//extern void 	l_Key_Stretcher 	(void);
//extern void 	h_Key_Stretcher 	(void);
//extern void 	j_Key_Stretcher 	(void);
//extern void 	k_Key_Stretcher 	(void);
//extern void 	a_Key_Stretcher 	(void);
//extern void 	s_Key_Stretcher 	(void);
//extern void 	d_Key_Stretcher 	(void);
//extern void 	f_Key_Stretcher 	(void);
#endif
//----------------------------------------------------------------------------------------------------
