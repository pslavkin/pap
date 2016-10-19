#ifndef MULTICHANNEL
#define MULTICHANNEL

#define 	MAX_VISIBLE_CH_NUM 	400
#define 	CH_NUM 			(8192)


extern void 	Init_Multichannel     		(void);
extern void 	Re_Init_Multichannel 		(void);
extern void 	Start_Multichannel_Menu		(void);
extern void 	Parse_Multichannel_Menu		(int Selection);
extern void 	Start_Multichannel_Menu		(void);
extern void 	Redraw_Multichannel_Box		(void);
extern void 	Redraw_Multichannel_Limits 	(void);
extern void 	Destroy_Multichannel  		(void);
extern void* 	Multichannel_Rti 		(void* Arg1);
extern void 	Bottom_Multichannel 		(void); 
extern void 	Top_Multichannel 		(void);
extern void 	Select_Multichannel 		(void);
extern void 	Deselect_Multichannel 		(void);
extern void 	Hide_Multichannel 		(void); 
extern void 	Inc_Energy_Channel 		(unsigned short int Channel);
extern void 	Clear_Energy_Ch 		(void);

extern void 	Clear_Multichannel 		(void);
extern void 	Update_Multichannel 		(void);
extern void 	Calculate_Multichannel 		(void);
extern void 	i_Key_Multichannel 		(void);
extern void 	o_Key_Multichannel 		(void);
extern void 	Inc_Ch_Min 			(void);
extern void 	Dec_Ch_Min 			(void);
extern void 	a_Key_Multichannel 		(void);
extern void 	s_Key_Multichannel 		(void);
extern void 	d_Key_Multichannel 		(void);
extern void 	f_Key_Multichannel 		(void);
extern void 	Inc_Width_Multichannel 		(void);
extern void 	Dec_Width_Multichannel 		(void);
extern void 	Autoscale_Multichannel 		(void);
extern void 	Set_Multichannel_Props 		(struct Struct_Sheets_Prop *S);
extern void 	Read_Multichannel_Props 	(struct Struct_Sheets_Prop *S);
#endif
//----------------------------------------------------------------------------------------------------
