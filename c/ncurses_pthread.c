#include <ncurses.h>
#include <pthread.h>
#include <panel.h>
#include <ncurses_pthread.h>
#include <screen_update.h>
#include <sheets.h>
#include <time.h>

pthread_mutex_t Print_Mutex = PTHREAD_MUTEX_INITIALIZER;


void Init_Ncurses_Pthread(void)
{
}
void Rien(void)
{
}

void Bottom_Panel_Method_Index(unsigned char Index)
{
	((void (**)())panel_userptr(panel_above(0)))[Index]();
}
void Hide_All_Panels(void)
{
 unsigned char i;
 for(i=0;i<20;i++) Pt_Hide_Panel(panel_below(0));
}

void Panel_Method_Exec(PANEL* Panel,unsigned char Index)
{
	((void (**)())panel_userptr(Panel))[Index]();
}
void Top_Panel_Method_Exec(unsigned char Index)
{
	Panel_Method_Exec(panel_below(0),Index);
}

void Pt_wprintw (WINDOW *A,const char *D,va_list Varg)
{
	pthread_mutex_lock(&Screen_Update_Mutex); 
		 vw_printw(A,D,Varg); 		
	pthread_mutex_unlock(&Screen_Update_Mutex); 

}
void Pt_waddch_hex (WINDOW *A,unsigned char D)
{
	char Aux[7];
	static unsigned char Last_Data;
	sprintf(Aux,"%.2X ",D);
	pthread_mutex_lock(&Screen_Update_Mutex); 
		if(D==0x0E) {
			Last_Data=0x0E;
		} 
		else	if(D==0x0F)
				if(Last_Data==0x0E) {
					waddch(A,'\n');
					wattrset(A,A_BOLD);
					waddnstr(A,"0E 0F ",6);
					wattrset(A,A_NORMAL);
					Last_Data=0;
				}
				else {
					waddnstr(A,"0E ",3);
					waddnstr(A,Aux,3);
				}
			else	waddnstr(A,Aux,5);
	pthread_mutex_unlock(&Screen_Update_Mutex); 
}

void Pt_mvwprintw (WINDOW *A,int B,int C, const char *D,...)
{
	va_list a_list;
    	va_start(a_list, D );
	pthread_mutex_lock(&Screen_Update_Mutex); 
		 wmove(A,B,C);
		 vw_printw(A,D,a_list); 		//no existe la move print w con valist.... asi que tengo que mover y luego imprimir...
	pthread_mutex_unlock(&Screen_Update_Mutex); 

}
void Pt_waddnstr (WINDOW *A,char* B,int C)
{
	pthread_mutex_lock(&Screen_Update_Mutex); 
		waddnstr(A,B,C);
	pthread_mutex_unlock(&Screen_Update_Mutex); 
}
void Pt_mvwaddch (WINDOW *A,int B,int C,const chtype D)
{
	pthread_mutex_lock(&Screen_Update_Mutex); 
		mvwaddch (A,B,C,D);
	pthread_mutex_unlock(&Screen_Update_Mutex); 
}

unsigned short int Get_Actual_Time(void)
{
	timespec Time;
 	clock_gettime(CLOCK_MONOTONIC_RAW,&Time);
	return (Time.tv_sec*10)+(Time.tv_nsec/100000000);
//	return (Time.tv_sec&0x0FFF)<<4 | (Time.tv_nsec/100000000)&0x000F;
}


