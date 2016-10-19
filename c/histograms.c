#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include "histograms.h"
#include "ncurses_pthread.h"
#include "screen_update.h"
#include "status_bar.h"

pthread_mutex_t Histo_Mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t 		PT_Histograms_Rti;
//----------------------------------------------------------------------------------------------------
void Init_Histogram(struct Struct_Histo *Histo,WINDOW *Win,unsigned short int Y,unsigned short int X,const char* Tittle, \
		    unsigned int Max_Value, unsigned int Value,unsigned short int Width)
{
	Histo->X 		=X;
	Histo->Y		=Y;
	Histo->Width 		=Width;
	Histo->Value 		=Value;
	Histo->Max_Value 	=Max_Value;
	Histo->Win 		=Win;
	strcpy 			(Histo->Tittle,Tittle);
}
void Set_Histogram_Value(struct Struct_Histo *Histo, unsigned int Value) 	//histograma
{
	unsigned short int i;
	pthread_mutex_lock(&Screen_Update_Mutex);	
		if(Value>Histo->Max_Value) Value=Histo->Max_Value;
		mvwprintw(Histo->Win,Histo->Y,Histo->X,"%s %d   ",Histo->Tittle,Value);
		Histo->Value=Value;
		Value=((Value/(float)Histo->Max_Value))*Histo->Width;	
		for(i=0;i<Histo->Width;i++) 
			mvwaddch(Histo->Win,Histo->Y+1,Histo->X+i,i<Value?('.'| COLOR_PAIR(3)):(' '| COLOR_PAIR(2)));
	pthread_mutex_unlock(&Screen_Update_Mutex);	
	
}
void Set_Rule_Value(struct Struct_Histo *Histo, unsigned int Value) 		//detector de picos
{
	unsigned short int i;
	pthread_mutex_lock(&Screen_Update_Mutex);	
		if(Value>Histo->Max_Value) Value=Histo->Max_Value;
		mvwprintw(Histo->Win,Histo->Y,Histo->X,"%s %d   ",Histo->Tittle,Value);
		Histo->Value=Value;
		Value=((Value/(float)Histo->Max_Value))*Histo->Width;	
		for(i=0;i<Histo->Width;i++) 
			mvwaddch(Histo->Win,Histo->Y+1,Histo->X+i,i!=Value?('.'| COLOR_PAIR(3)):(' '| COLOR_PAIR(2)));
	pthread_mutex_unlock(&Screen_Update_Mutex);	
}
void Set_V_Histogram_Value(struct Struct_Histo *Histo, unsigned int Value) 	//histograma
{
	unsigned short int i;
	pthread_mutex_lock(&Screen_Update_Mutex);	
		Value=((Value/(float)Histo->Max_Value))*(Histo->Width-1);
		for(i=0;i<Histo->Width;i++) 
			mvwaddch(Histo->Win,Histo->Y-i,Histo->X,i<Value?((i<4?Histo->Tittle[3-i]:'.')| COLOR_PAIR(2)):((i<4?Histo->Tittle[3-i]:' ')| COLOR_PAIR(3)));
	pthread_mutex_unlock(&Screen_Update_Mutex);	
}
void Set_V_Rule_Value(struct Struct_Histo *Histo, unsigned int Value) 	//detecta picos
{
	unsigned short int i;
	pthread_mutex_lock(&Screen_Update_Mutex);	
		Value=((Value/(float)Histo->Max_Value))*(Histo->Width-1);	
		for(i=0;i<Histo->Width;i++) 
			mvwaddch(Histo->Win,Histo->Y-i,Histo->X,i!=Value?((i<4?Histo->Tittle[3-i]:' ')| COLOR_PAIR(0)):((i<4?Histo->Tittle[3-i]:' ')| COLOR_PAIR(3)));
	pthread_mutex_unlock(&Screen_Update_Mutex);	
}
void Set_V_Double_Rule_Value(struct Struct_Histo *Histo, unsigned int ValueA,unsigned int ValueB)
{
	unsigned short int i;
	unsigned short int Data;
	pthread_mutex_lock(&Screen_Update_Mutex);	

		ValueA=((ValueA/(float)Histo->Max_Value))*(Histo->Width-1);	
		ValueB=((ValueB/(float)Histo->Max_Value))*(Histo->Width-1);	
		for(i=0;i<Histo->Width;i++) {
			Data=COLOR_PAIR(0);
			if(i==ValueA) Data=COLOR_PAIR(3);
			if(i==ValueB) Data=COLOR_PAIR(4);
			if(i<4) Data|=Histo->Tittle[3-i];	
			else 	Data|='.'; 
			mvwaddch(Histo->Win,Histo->Y-i,Histo->X,Data);
		}
	pthread_mutex_unlock(&Screen_Update_Mutex);	
}
void Set_V_Y_Scale(struct Struct_Histo *Histo)
{
	unsigned short int i;
	pthread_mutex_lock(&Screen_Update_Mutex);	
		for(i=0;i<Histo->Width;i++) 
			mvwprintw(Histo->Win,Histo->Y-i,Histo->X-7,"%5.1d",(unsigned int) (((Histo->Max_Value)/(float)(Histo->Width-1))*i));
	pthread_mutex_unlock(&Screen_Update_Mutex);	
}
void Init_Histograms(void)
{
	pthread_create(&PT_Histograms_Rti, NULL, Histogram_Rti, NULL);
}
void* Histogram_Rti(void* Arg1)
{
	struct timespec req={0,100000000};
	while(1) {
	 	nanosleep(&req,&req);
	}
}
void Destroy_Histograms(void)
{
	pthread_exit(&PT_Histograms_Rti);
}
//---------------BRESENHAM-------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
void BDraw_Line1 	(WINDOW* Win, unsigned short int Y0,unsigned short int X0,unsigned short int Y1,unsigned short int X1, unsigned char Color)/*{{{*/
{
	short int dX=abs(X1-X0), dY=abs(Y1-Y0), Y=Y0, X=X0, eps=0; 
	for (; X<=X1; X++)  {
		Pt_mvwaddch(Win,Y,X,' '|COLOR_PAIR(Color));
		eps += dY;
		if ( (eps << 1) >= dX )  {
			Y++;
			eps -= dX;
 		}
	}
}/*}}}*/
void BDraw_Line2 	(WINDOW* Win, unsigned short int Y0,unsigned short int X0,unsigned short int Y1,unsigned short int X1, unsigned char Color)/*{{{*/
{
	short int dX=abs(X1-X0), dY=abs(Y1-Y0), Y=Y0, X=X0, eps=0; 
	for (; Y<=Y1; Y++)  {
		Pt_mvwaddch(Win,Y,X,' '|COLOR_PAIR(Color));
		eps += dX;
		if ( (eps << 1) >= dY )  {
			X++;
			eps -= dY;
		}
	}
}/*}}}*/
void BDraw_Line3 	(WINDOW* Win, unsigned short int Y0,unsigned short int X0,unsigned short int Y1,unsigned short int X1, unsigned char Color)/*{{{*/
{
	short int dX=abs(X1-X0), dY=abs(Y1-Y0), Y=Y0, X=X0, eps=0; 
	for (; Y<=Y1; Y++)  {
		Pt_mvwaddch(Win,Y,X,' '|COLOR_PAIR(Color));
		eps += dX;
		if ( (eps << 1) >= dY )  {
			X--;
			eps -= dY;
		}
	}
}/*}}}*/
void BDraw_Line4 	(WINDOW* Win, unsigned short int Y0,unsigned short int X0,unsigned short int Y1,unsigned short int X1, unsigned char Color)/*{{{*/
{
	short int dX=abs(X1-X0), dY=abs(Y1-Y0), Y=Y0, X=X0, eps=0; 
	for (; X>=X1; X--)  {
		Pt_mvwaddch(Win,Y,X,' '|COLOR_PAIR(Color));
		eps += dY;
		if ( (eps << 1) >= dX )  {
			Y++;
			eps -= dX;
 		}
	}
}/*}}}*/
void BDraw_Line5 	(WINDOW* Win, unsigned short int Y0,unsigned short int X0,unsigned short int Y1,unsigned short int X1, unsigned char Color)/*{{{*/
{
	short int dX=abs(X1-X0), dY=abs(Y1-Y0), Y=Y0, X=X0, eps=0; 
	for (; X>=X1; X--)  {
		Pt_mvwaddch(Win,Y,X,' '|COLOR_PAIR(Color));
		eps += dY;
		if ( (eps << 1) >= dX )  {
			Y--;
			eps -= dX;
 		}
	}
}/*}}}*/
void BDraw_Line6 	(WINDOW* Win, unsigned short int Y0,unsigned short int X0,unsigned short int Y1,unsigned short int X1, unsigned char Color)/*{{{*/
{
	short int dX=abs(X1-X0), dY=abs(Y1-Y0), Y=Y0, X=X0, eps=0; 
	for (; Y>=Y1; Y--)  {
		Pt_mvwaddch(Win,Y,X,' '|COLOR_PAIR(Color));
		eps += dX;
		if ( (eps << 1) >= dY )  {
			X--;
			eps -= dY;
		}
	}
}/*}}}*/
void BDraw_Line7 	(WINDOW* Win, unsigned short int Y0,unsigned short int X0,unsigned short int Y1,unsigned short int X1, unsigned char Color)/*{{{*/
{
	short int dX=abs(X1-X0), dY=abs(Y1-Y0), Y=Y0, X=X0, eps=0; 
	for (; Y>=Y1; Y--)  {
		Pt_mvwaddch(Win,Y,X,' '|COLOR_PAIR(Color));
		eps += dX;
		if ( (eps << 1) >= dY )  {
			X++;
			eps -= dY;
		}
	}
}/*}}}*/
void BDraw_Line8 	(WINDOW* Win, unsigned short int Y0,unsigned short int X0,unsigned short int Y1,unsigned short int X1, unsigned char Color)/*{{{*/
{
	short int dX=abs(X1-X0), dY=abs(Y1-Y0), Y=Y0, X=X0, eps=0; 
	for (; X<=X1; X++)  {
		Pt_mvwaddch(Win,Y,X,' '|COLOR_PAIR(Color));
		eps += dY;
		if ( (eps << 1) >= dX )  {
			Y--;
			eps -= dX;
 		}
	}
}/*}}}*/

void BDraw_Line 	(WINDOW* Win, unsigned short int Y0,unsigned short int X0,unsigned short int Y1,unsigned short int X1,unsigned char Color)
{
	short int dX=abs(X1-X0), dY=abs(Y1-Y0);
	
	if(X1>X0)
		if(Y1>=Y0)
 			if(dX>dY) {
				BDraw_Line1(Win,Y0,X0,Y1,X1,Color);
				Print_Status_Bar_Data("cuadrante 1\n");
			}
			else {
				BDraw_Line2(Win,Y0,X0,Y1,X1,Color);
				Print_Status_Bar_Data("cuadrante 2\n");
			}
		else 
			if(dX>dY) {
				BDraw_Line8(Win,Y0,X0,Y1,X1,Color);
				Print_Status_Bar_Data("cuadrante 8\n");
			}
			else {
				BDraw_Line7(Win,Y0,X0,Y1,X1,Color);
				Print_Status_Bar_Data("cuadrante 7\n");
			}
	else
		if(Y1>=Y0)
 			if(dX>dY) {
			 	BDraw_Line4(Win,Y0,X0,Y1,X1,Color);
				Print_Status_Bar_Data("cuadrante 4\n");
			}
			else {
				BDraw_Line3(Win,Y0,X0,Y1,X1,Color);
				Print_Status_Bar_Data("cuadrante 3\n");
			}
		else 
 			if(dX>dY) {
				BDraw_Line5(Win,Y0,X0,Y1,X1,Color);
				Print_Status_Bar_Data("cuadrante 5\n");
			}
			else {
				BDraw_Line6(Win,Y0,X0,Y1,X1,Color);
				Print_Status_Bar_Data("cuadrante 6\n");
			}
}


