#include "inc_all.h"

Sender_Class::Sender_Class(Sheet* Parent,Dim D):Sheet(Parent,D)
{
   scrollok(Sub_Win,TRUE);
   GFile.open("gcodes/route.nc");
   if(GFile.good()) {
         Read_File();
   //      File2Win();
   }
}
bool  Sender_Class::Is_Running(void)
{
   return State!=STOPED;
}

void Sender_Class::Key(int K)
{
   switch ( K ) {
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
      case 'r':
         Next_State=RESTART;
         break;
      case 'k':
         Next_State=STOP_NOW;
         break;
      case ' ':
         Next_State=STOP;
         break;
      case 'R':
         Reload_File();
         break;
      case 'u':
         Toogle_Full_Restore_Screen();
         break;
   }
}
void Sender_Class::Stop_Now(void)
{
   char Buf[10];
   Actual_Line=0;
   Main_Page->Serial->Send_And_Forget("halt\n");
}
void Sender_Class::Restart(void)
{
   char Buf[10];
   Actual_Line=0;
   Main_Page->Serial->Send_And_Forget ( "halt\n"     );
   Main_Page->Serial->Send_And_Forget ( "GL N0 G2\n" );
   Main_Page->Serial->Send_And_Forget ( "halt\n"     );
   Main_Page->Serial->Reopen_Log();
}
void Sender_Class::Reload_File(void)
{
   GFile.close();
   GFile.open("gcodes/route.nc");
   Read_File();
   Next_State=RESTART;
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

char* Sender_Class::Get_Line(int32_t Pos)
{
   if(Pos<=0 || Pos>Total_Lines)
      return (char*)"---";
   else
      return (char*)Lines[Pos-1].c_str();
}

void Sender_Class::File2Win(void)
{
   uint16_t i;
   wclear(Sub_Win);
   pthread_mutex_lock(&Main_Page->Print_Mutex);
   {
   for(i=0;i<Dims.H-4;i++) {
      if(i==EXEC_LINE_POS) {
         wcolor_set(Sub_Win, 4,NULL);
         wattron(Sub_Win,A_BOLD);
      }
      if(Actual_Line-Exec_Line+EXEC_LINE_POS==i) wcolor_set(Sub_Win, 3,NULL);
         mvwprintw(Sub_Win,i,0,"%.*s",Dims.W-5,Get_Line(Exec_Line+i-EXEC_LINE_POS));
      if(i==EXEC_LINE_POS) wattroff(Sub_Win,A_BOLD);
      wcolor_set(Sub_Win, 0,NULL);
   }
   Touch_Win();
   pthread_mutex_unlock(&Main_Page->Print_Mutex);
   }
}

void Sender_Class::Send_Next_Line(void)
{
   if(Main_Page->Serial->Space>0) {
      if(Actual_Line<Total_Lines) {
         char Buf[200];
         strcpy(Buf,"GL ");
         strcpy(Buf+3,Lines[Actual_Line].c_str());
         Main_Page->Serial->Send_And_Forget(Buf);
      }
      else {
         Next_State=STOP;
      }
   }
}
void Sender_Class::Rti(void)
{
   while(1) {
      nanosleep ( &Rti_Delay,&Rti_Delay );
      Main_Page->Serial->Send_And_Forget ( "K\n" );
      State=Next_State;
      switch(State) {
         case STOPED:
            break;
         case STOP:
            if(Actual_Line==Exec_Line)
               Next_State=STOPED;
            break;
         case PLAY:
            Send_Next_Line();
            break;
         case ONE_LINE:
            Send_Next_Line();
            Next_State=STOP;
            break;
         case RESTART:
            Restart();
            Next_State=STOP;
            break;
         case STOP_NOW:
            Stop_Now();
            Next_State=STOP;
            break;
      }
      Main_Page->Sender->File2Win();
   }
}
