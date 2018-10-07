#include <cdk/cdk.h>
#include <menu.h>
#include <pthread.h>
#include <panel.h>

#include "sheet.h"
#include "ball.h"
#include "screen_update.h"
#include "serialmanager.hpp"

//----------------------------------------------------------------------------------------------------
pthread_t      PT_Menu_Rti;
Sheet*         Main_Sheet; // global porque lo usan el resto de las ventanitas para saber el maximo de tamanio y demas..
//----------------------------------------------------------------------------------------------------
void Init_Menu (void)
{
//   Main_Sheet=new Sheet(stdscr);
   Main_Sheet=new Sheet(5,5,20,20,"menu");
   pthread_create     ( &PT_Menu_Rti, NULL, Menu_Rti, NULL );
//   Main_Sheet->Set_Panel_User_Pointer ( Main_Sheet );
//   Main_Sheet->Set_Name               ( "Main"     );
 //  Main_Sheet->Full_Screen            (            );
  // Main_Sheet->Redraw_Box             (            );
}
//----------------------------------------------------------------------------------------------------
void Set_Menu (PANEL* Panel,const char* Menu_List[][MAX_SUB_ITEMS],unsigned char Items,int* Submenu_Size,int *Menu_Loc)
{
   unsigned short int   Selection;
   CDKSCREEN *Cdk = initCDKScreen   ( panel_window(Panel                                                         ));
   CDKMENU *Menu  = newCDKMenu      ( Cdk, Menu_List, Items, Submenu_Size, Menu_Loc, TOP, A_UNDERLINE, A_REVERSE ) ;
   Selection      = activateCDKMenu ( Menu,0                                                                     ) ;
   if (Menu->exitType == vNORMAL)
      Parse_Menu_Menu(Selection);
   destroyCDKMenu         ( Menu );
   destroyCDKScreen       ( Cdk  );
   Main_Sheet->Redraw_Box (      );
   Main_Sheet->Touch_Win  (      );
}
char* Set_File_Select (PANEL* Panel)
{
   char           *File_Name;
   static char     New_File_Name[1000];
   CDKSCREEN   *Cdk         = initCDKScreen ( panel_window(Panel                                                                                       ));
   CDKFSELECT  *File_Select = newCDKFselect ( Cdk,CENTER,CENTER,20,65,"Select File","",A_NORMAL,'_', A_REVERSE,"</5>","</48>","</N>","</N>",TRUE,FALSE ) ;

      File_Name = copyChar(activateCDKFselect(File_Select,0));
   if (File_Select->exitType == vNORMAL)
      strcpy(New_File_Name,File_Name);
   else strcpy       ( New_File_Name,"" );
   destroyCDKFselect ( File_Select      );
   destroyCDKScreen  ( Cdk              );
   return New_File_Name;
}

unsigned char Set_Entry (PANEL* Panel,const char* Title,const char* Actual_Data,char* Data,unsigned short int Length)
{
   char  *Info,Ans=1;
   CDKSCREEN   *Cdk   = initCDKScreen    ( panel_window(Panel                                                            ));
   CDKENTRY    *Entry = newCDKEntry      ( Cdk,CENTER,CENTER,Title,Actual_Data,A_NORMAL,'.',vMIXED,20,0,Length,TRUE,TRUE ) ;
   Info               = activateCDKEntry ( Entry, 0                                                                      ) ;
   if (Entry->exitType == vNORMAL) {
      Ans=0;
      strcpy(Data,Info);
   }
   destroyCDKEntry  ( Entry );
   destroyCDKScreen ( Cdk   );
   return Ans;
}
//-------------------------------------------------------------------
void* Menu_Rti(void* Arg1)
{
   struct timespec req={0, 50000000};
   while(1) 
      nanosleep     ( &req,&req );
}
//----------------------------------------------------------------------------------------------------
void Start_Menu_Menu    (void)
{
   int         Submenu_Size[]={3,2,3,4},Menu_Loc[]={LEFT,LEFT,LEFT,RIGHT};
   const char     *Menu_List[][MAX_SUB_ITEMS]= {
               {
                  "</B>File<!B>",
                  "</B>Save<!B>",
                  "</B>Exit<!B>",
               },
               {
                  "</B>Empty<!B>",
                  "</B>Nada<!B>",
               },
               {
                  "</B>RS232<!B>",
                  "</B>Open<!B>",
                  "</B>Close<!B>",
               },
{
                  "</B>Help<!B>",
                  "</B>On Edit <!B>",
                  "</B>On File <!B>",
                  "</B>About...<!B>",
               },
            };
   Set_Menu (Main_Sheet->Panel,Menu_List,4,Submenu_Size,Menu_Loc);
}
void Parse_Menu_Menu    (int Selection)
{
   switch(Selection) {
      case 000:
         Set_File_Select(Main_Sheet->Panel);
         break;
      case 001:
         endCDK (   );
         exit   ( 0 );
         break;
      case 100:
         break;
      case 200:
         Serial_Manager::Serial_Manager_Inst->Open(0,115200);
         break;
      }
}
//----------------------------------------------------------------------------------------------------

void* Graph_Rti(void* Arg1);

pthread_t      PT_Graph_Rti;
#define FADE 100
int Fade=5;
static unsigned short int  Last_X[FADE]={0},Last_Y[FADE]={0};
Sheet* Inst;

void Fade_Pixels(unsigned char Times)
{
   unsigned short int Pos,Color;
      for ( Pos=0;Pos<Times;Pos++ )
         if(Last_Y[Pos]) mvwaddch (Inst->Win, Last_Y[Pos], Last_X[Pos], ('.' | COLOR_PAIR(0))); //borra la mas viejaa

      for(Pos=0;Pos<(Fade-Times);Pos++) {
               Last_X      [Pos]    =Last_X  [Pos+Times];
               Last_Y      [Pos]    =Last_Y  [Pos+Times];
         Color=MIN_COLOUR_PAIR+((unsigned int)Pos*(MAX_COLOUR_PAIR-MIN_COLOUR_PAIR))/Fade;
         if(Color>MAX_COLOUR_PAIR || Color<MIN_COLOUR_PAIR) 1;
         if(Last_Y[Pos]) mvwaddch (Inst->Win, Last_Y[Pos], Last_X[Pos], ' ' | COLOR_PAIR(MIN_COLOUR_PAIR+((unsigned int)Pos*(MAX_COLOUR_PAIR-MIN_COLOUR_PAIR-1))/Fade));
         }
}
void Toogle_Pixel(unsigned char Y, unsigned char X)
{
      Fade_Pixels(1);
      mvwaddch (Inst->Win, Last_Y[Fade-1]=Y,Last_X[Fade-1]=X, 'O' | COLOR_PAIR(2));
}

void Init_Graph(void)
{
   Inst = new Sheet();
   Inst->Set_Panel_User_Pointer ( Inst );
   Inst->Set_Size   ( 20,20  )        ;
   Inst->Set_Pos    ( 5,10  )        ;
   Inst->Set_Name   ( (char* )"graph");
   Inst->Redraw_Box (        )        ;
   pthread_create(&PT_Graph_Rti, NULL, Graph_Rti, NULL);
}
void* Graph_Rti(void* Arg1)
{
   struct timespec req={0,5000000};
   while(1) {
      Toogle_Pixel(rand()%(getmaxy(Inst->Win)-2)+1,rand()%(getmaxx(Inst->Win)-2)+1);
      nanosleep(&req,&req);
   }
}

