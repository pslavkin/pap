#ifndef NCURSES_PTHREAD
#define NCURSES_PTHREAD

#define SCREEN_UPDATE_RTI 	100000000
#define USB_RTI 		500000000
#define USB_READER_RTI 		100000
#define USB_WRITER_RTI 		100000
#define STATUS_BAR_RTI 		500000000
#define SHEETS_RTI 		500000000
#define SCR_RTI 		999999999 //cachichien
#define IO_FILES_RTI 		500000
#define STRETCHER_RTI 		50000000
#define LORS_RTI 		900000000



#include <ncurses.h>
#include <panel.h>
#include <analog_clk.h>

extern pthread_mutex_t 		Print_Mutex;
extern void 			Rien 				(void);
extern void 			Init_Ncurses_Pthread 		(void);
extern void 			Pt_mvwprintw 			(WINDOW *A,int B,int C, const char *D,...);
extern void 			Pt_wprintw 			(WINDOW *A,const char *D,va_list Varg);
extern void 			Pt_waddnstr 			(WINDOW *A,char* B,int C);
extern void 			Pt_mvwaddch 			(WINDOW *A,int B,int C,const chtype D);
extern void 			Pt_waddch_hex 			(WINDOW *A,unsigned char D);
extern void 			Top_Panel_Method_Exec 		(unsigned char Index);
extern void 			Panel_Method_Exec 		(PANEL* Panel,unsigned char Index);
extern Sheet* 			Sheet4Panel			(PANEL* Panel);
extern Sheet* 			Sheet4Top_Panel			(void);
extern void 			Bottom_Panel_Method_Index 	(unsigned char Index);
extern void 			Hide_All_Panels 		(void);
extern unsigned short int 	Get_Actual_Time 		(void);



#endif
