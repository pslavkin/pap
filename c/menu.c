#include <cdk/cdk.h>
#include <thread>
#include <panel.h>

#include "dim.h"
#include "sheet.h"
#include "menu.h"
#include "gantry.h"
#include "serialmanager.hpp"
#include "histograms.h"
#include "timer.hpp"
#include "screen_update.h"

//----------------------------------------------------------------------------------------------------
pthread_t      PT_Menu_Rti;
Sheet*         Main_Sheet; // global porque lo usan el resto de las ventanitas para saber el maximo de tamanio y demas..
//----------------------------------------------------------------------------------------------------
void Init_Menu (void)
{
   Dim PaPD(0, 0,getmaxy(stdscr),getmaxx(stdscr),"PaP");
   Main_Sheet=new Sheet(stdscr,PaPD);

   Dim XYD(5, 66,35,70,"XY");
   static Gantry_Class XY(Main_Sheet,XYD);

   Dim ZD(5, 63,35, 3,"z");
   static Histo_Class Z(Main_Sheet,ZD,100,50);

   Screen_Update_Class* SU=new Screen_Update_Class();
   SU->Start_Rti();

   static Timer_Class T;
   T.Set_Gantry_Rti ( &XY );
   T.Set_Histo_Rti  ( &Z  );

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

