#include "inc_all.h"

Sender_Class::Sender_Class(Sheet* Parent,Dim D):Sheet(Parent,D)
{
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
         Next_State=ONE_LINE;
         break;
      case 'p':
         Next_State=PLAY;
         break;
      case ' ':
         Next_State=STOP;
         break;
      case 'u':
         Toogle_Full_Restore_Screen();
         break;
   }
}

void Sender_Class::Read_File(void)
{
   uint16_t i;
   for(i=0;i<MAX_LINES && std::getline(GFile,Lines[i]);i++)
//      if (Lines[i][Lines[i].size() - 1] == '\r')
//         Lines[i].resize(Lines[i].size() - 1);
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
         mvwprintw(Sub_Win,i,0,"%.*s",Dims.W-5,
               Exec_Line>=(HH-i)?Lines[Exec_Line-(HH-i)].data():"---");
   wcolor_set(Sub_Win, 4,NULL);
     mvwprintw(Sub_Win,i,0,"%.*s",Dims.W-5,Lines[Exec_Line].data());
   wcolor_set(Sub_Win, 0,NULL);
   for(i++;i<Dims.H-4;i++)
         mvwprintw(Sub_Win,i,0,"%.*s",Dims.W-5,
         (Exec_Line+(i-HH))<Total_Lines?Lines[Exec_Line+(i-HH)].data():"~~~");
   Touch_Win();
   pthread_mutex_unlock(&Main_Page->Print_Mutex);
}

void Sender_Class::Send_Next_Line(void)
{
   if(Main_Page->Serial->Space>0) {
      if(Actual_Line<=Total_Lines) {
         char Buf[200];
         char Ans_Buf[20];
         strcpy(Buf,"GL ");
         strcpy(Buf+3,Lines[Actual_Line].c_str());
         Main_Page->Serial->Send_And_Receive(Buf,Ans_Buf,3);
         Actual_Line++;
      }
   }
}
void Sender_Class::Rti(void)
{
   while(1) {
      nanosleep     ( &Rti_Delay,&Rti_Delay );
      State=Next_State;
      switch(State) {
         case STOP:
            break;
         case PLAY:
            Send_Next_Line();
            break;
         case ONE_LINE:
            Send_Next_Line();
            Next_State=STOP;
            break;
      }
      Main_Page->Sender->File2Win();
   }
}
