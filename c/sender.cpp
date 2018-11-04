#include "inc_all.h"
//#include <queue>
#include <iostream>
//#include <string>
#include <fstream>

Sender_Class::Sender_Class(Sheet* Parent,Dim D)
{
   S = new Sheet(Parent,D);
   Dim Sub_Dim(2,2,D.H-4,D.W-4,"");
   Sub = new Sheet ( S,Sub_Dim,false);
   scrollok        ( Sub->Win, TRUE );

   GFile.open("gcodes/route.nc");
   if(GFile.good()) {
         Read_File();
//         File2Win();
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
   uint16_t i,HH=2;//Sub->Dims.H/2-2;
   wclear(Sub->Win);
   pthread_mutex_lock(&Main_Page->Print_Mutex);
   for(i=0;i<HH;i++)
         mvwprintw(Sub->Win,i,0,"%s",
               Actual_Line>=(HH-i)?Lines[Actual_Line-(HH-i)].data():"---");
   wcolor_set(Sub->Win, 4,NULL);
     mvwprintw(Sub->Win,i,0,"%s",Lines[Actual_Line].data());
   wcolor_set(Sub->Win, 0,NULL);
   for(i++;i<Sub->Dims.H;i++)
         mvwprintw(Sub->Win,i,0,"%s",
         (Actual_Line+(i-HH))<Total_Lines?Lines[Actual_Line+(i-HH)].data():"~~~");
   pthread_mutex_unlock(&Main_Page->Print_Mutex);
}
void Sender_Class::Rti(void)
{
   char Buf[100],Len;
   while(1) {
      nanosleep     ( &Rti_Delay,&Rti_Delay );
      if(Main_Page->Serial->Available_Space>0) {
         File2Win();
         Main_Page->Serial->serial_send((char*)Lines[Actual_Line].c_str(),Lines[Actual_Line].length());
         Main_Page->Serial->serial_send((char*)"\r",1);
         if(++Actual_Line>=Total_Lines)
            Actual_Line=0;
      }
   }
}
