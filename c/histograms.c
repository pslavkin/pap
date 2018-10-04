#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <cdk/cdk.h>
#include <panel.h>
#include <pthread.h>

#include "sheet.h"
#include "screen_update.h"
#include "serialmanager.hpp"
#include "menu.h"
#include "histograms.h"

pthread_t      PT_Histograms_Rti;
static struct Struct_Histo    Histo;
//----------------------------------------------------------------------------------------------------
void Init_Histogram(struct Struct_Histo *Histo,WINDOW *Win,unsigned short int
      Y,unsigned short int X,const char* Tittle, unsigned int Max_Value,
      unsigned int Value,unsigned short int Width)
{
   Histo->X         = X;
   Histo->Y         = Y;
   Histo->Width     = Width;
   Histo->Value     = Value;
   Histo->Max_Value = Max_Value;
   Histo->Win       = Win;
   strcpy         (Histo->Tittle,Tittle);
}
void Set_Histogram_Value(struct Struct_Histo *Histo, unsigned int Value)   //histograma
{
   unsigned short int i;
      if(Value>Histo->Max_Value) Value=Histo->Max_Value;
      mvwprintw(Histo->Win,Histo->Y,Histo->X,"%s %d   ",Histo->Tittle,Value);
      Histo->Value=Value;
      Value=((Value/(float)Histo->Max_Value))*Histo->Width; 
      for(i=0;i<Histo->Width;i++) 
         mvwaddch(Histo->Win,Histo->Y+1,Histo->X+i,i<Value?('.'| COLOR_PAIR(3)):(' '| COLOR_PAIR(2)));
   
}
void Set_Rule_Value(struct Struct_Histo *Histo, unsigned int Value)     //detector de picos
{
   unsigned short int i;
      if(Value>Histo->Max_Value) Value=Histo->Max_Value;
      mvwprintw(Histo->Win,Histo->Y,Histo->X,"%s %d   ",Histo->Tittle,Value);
      Histo->Value=Value;
      Value=((Value/(float)Histo->Max_Value))*Histo->Width; 
      for(i=0;i<Histo->Width;i++) 
         mvwaddch(Histo->Win,Histo->Y+1,Histo->X+i,i!=Value?('.'| COLOR_PAIR(3)):(' '| COLOR_PAIR(2)));
}
void Set_V_Histogram_Value(struct Struct_Histo *Histo, unsigned int Value)    //histograma
{
   unsigned short int i;
      Value=((Value/(float)Histo->Max_Value))*(Histo->Width-1);
      for(i=0;i<Histo->Width;i++) 
         mvwaddch(Histo->Win,Histo->Y-i,Histo->X,i<Value?((i<4?Histo->Tittle[3-i]:'.')| COLOR_PAIR(2)):((i<4?Histo->Tittle[3-i]:' ')| COLOR_PAIR(3)));
}
void Set_V_Rule_Value(struct Struct_Histo *Histo, unsigned int Value)   //detecta picos
{
   unsigned short int i;
      Value=((Value/(float)Histo->Max_Value))*(Histo->Width-1);   
      for(i=0;i<Histo->Width;i++) 
         mvwaddch(Histo->Win,Histo->Y-i,Histo->X,i!=Value?((i<4?Histo->Tittle[3-i]:' ')| COLOR_PAIR(0)):((i<4?Histo->Tittle[3-i]:' ')| COLOR_PAIR(3)));
}
void Set_V_Double_Rule_Value(struct Struct_Histo *Histo, unsigned int ValueA,unsigned int ValueB)
{
   unsigned short int i;
   unsigned short int Data;

      ValueA=((ValueA/(float)Histo->Max_Value))*(Histo->Width-1); 
      ValueB=((ValueB/(float)Histo->Max_Value))*(Histo->Width-1); 
      for(i=0;i<Histo->Width;i++) {
         Data=COLOR_PAIR(0);
         if(i==ValueA) Data=COLOR_PAIR(3);
         if(i==ValueB) Data=COLOR_PAIR(4);
         if(i<4) Data|=Histo->Tittle[3-i];   
         else  Data|='.'; 
         mvwaddch(Histo->Win,Histo->Y-i,Histo->X,Data);
      }
}
void Set_V_Y_Scale(struct Struct_Histo *Histo)
{
   unsigned short int i;
      for(i=0;i<Histo->Width;i++) 
         mvwprintw(Histo->Win,Histo->Y-i,Histo->X-7,"%5.1d",(unsigned int) (((Histo->Max_Value)/(float)(Histo->Width-1))*i));
}
void Set_V_Inverted_Rule_Value(struct Struct_Histo *Histo, unsigned int Value)
{
   unsigned short int i;
      Value=((Value/(float)Histo->Max_Value))*(Histo->Width-1);
      for(i=0;i<Histo->Width;i++)
         mvwaddch(Histo->Win,Histo->Y-i,Histo->X,Value<=(Histo->Width-i)?('.'|COLOR_PAIR(0)):(' '|COLOR_PAIR(3)));
}
void Init_Histograms(void)
{
   WINDOW* Win=Main_Sheet->Win;
   Init_Histogram(&Histo,Win,getmaxy(Win)-4,20,"",getmaxy(Win)-4,20,getmaxy(Win)-5);
   pthread_create(&PT_Histograms_Rti, NULL, Histogram_Rti, NULL);
}
void* Histogram_Rti(void* Arg1)
{
   int i=0;
   struct timespec req={0,50000000};
   while(1) {
      nanosleep(&req,&req);
      Set_V_Inverted_Rule_Value(&Histo, i++);
      if(i>50) i=0;
   }
}
void Destroy_Histograms(void)
{
   pthread_exit(&PT_Histograms_Rti);
}
