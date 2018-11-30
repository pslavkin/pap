#include "inc_all.h"
//#include <queue>
#include <iostream>
//#include <string>
#include <fstream>

Sender_Class::Sender_Class(Sheet* Parent,Dim D):Sheet(Parent,D)
{
   Sub_Win   = derwin ( this->Win,D.H-4 ,D.W-4,2,2 );
   scrollok           ( Sub_Win, TRUE              );

   GFile.open("gcodes/route.nc");
   if(GFile.good()) {
         Read_File();
   //      File2Win();
   }
}
void Sender_Class::Key(int K)
{
   switch(K) {
      case KEY_LEFT:
         break;
      case KEY_RIGHT:
         break;
      case KEY_UP:
         break;
      case KEY_DOWN:
         break;
      case 'u':
               Full_Screen();
         break;
      case 'U':
               Restore_Screen();
         break;
   }
}

void Sender_Class::Read_File(void)
{
   uint16_t i;
   for(i=0;i<MAX_LINES && std::getline(GFile,Lines[i]);i++)
      ;
   Actual_Line=0;
   Total_Lines=i;
}
void Sender_Class::File2Win(void)
{
   uint16_t i,HH=2;//=Sub_Dim->H/2-2;
   wclear(Sub_Win);
   pthread_mutex_lock(&Main_Page->Print_Mutex);
   for(i=0;i<HH;i++)
         mvwprintw(Sub_Win,i,0,"%.*s",Dims.W-4,
               Exec_Line>=(HH-i)?Lines[Exec_Line-(HH-i)].data():"---");
   wcolor_set(Sub_Win, 4,NULL);
     mvwprintw(Sub_Win,i,0,"%.*s",Dims.W-4,Lines[Exec_Line].data());
   wcolor_set(Sub_Win, 0,NULL);
   for(i++;i<Dims.H-4;i++)
         mvwprintw(Sub_Win,i,0,"%.*s",Dims.W-4,
         (Exec_Line+(i-HH))<Total_Lines?Lines[Exec_Line+(i-HH)].data():"~~~");
   Touch_Win();
   pthread_mutex_unlock(&Main_Page->Print_Mutex);
}

void Sender_Class::Rti(void)
{
   char Len;
   while(1) {
      nanosleep     ( &Rti_Delay,&Rti_Delay );
//      if(Main_Page->Serial->Available_Space>0) {
//         File2Win();
//         Main_Page->Serial->serial_send((char*)"GL ",3);
//         Main_Page->Serial->serial_send((char*)Lines[Actual_Line].c_str(),Lines[Actual_Line].length());
//         Main_Page->Serial->serial_send((char*)"\r",1);
//         if(++Actual_Line>=Total_Lines)
//            break;
//        // Actual_Line=0;
//      }
   }
//   while(1)
//      nanosleep     ( &Rti_Delay,&Rti_Delay );
//
}
