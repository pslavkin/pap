#include "inc_all.h"

Sender_Class::Sender_Class(Sheet* Parent,Dim D):Sheet(Parent,D)
{
   scrollok(Sub_Win,TRUE);
   Read_File();
   Print_Stop();
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
         Play();
         break;
      case 'r':
         Next_State=RESTART;
         break;
      case 't':
         Next_State=STOP;
         Resume();
         Print_Stop();
         break;
      case ' ':
         Pause();
         Print_Pause();
         break;
      case 'R':
         Reload_File();
         Main_Page->TresD->Gcode2Matrix();
         break;
      case 'u':
         Toogle_Full_Restore_Screen();
         break;
      case 'K':
         Hiz_Now();
//         Next_State=STOP;
         break;
   }
}
void Sender_Class::Play(void)
{
   Next_State=PLAY;
   Resume();
   Print_Play();
}
void Sender_Class::Hiz_Now(void)
{
   Main_Page->Serial->Send_And_Forget("hiz\n");
   Main_Page->Serial->Send_And_Forget("s\n"); //tengo que pedir status por si se chiflo
}
void Sender_Class::Pause(void)
{
   Main_Page->Serial->Send_And_Forget("pause\n"); //tengo que pedir status por si se chiflo
}
void Sender_Class::Resume(void)
{
   Main_Page->Serial->Send_And_Forget("resume\n"); //tengo que pedir status por si se chiflo
}
void Sender_Class::Restart(void)
{
   Main_Page->Serial->Send_And_Forget ( "s\n"        ); // tengo que pedir status por si se chiflo
   Main_Page->Serial->Send_And_Forget ( "halt\n"     );
   Main_Page->Serial->Reopen_Log();
}
void Sender_Class::Reload_File(void)
{
   Read_File();
   Next_State=RESTART;
}

void Sender_Class::Read_File(void)
{
   uint32_t i;
   GFile.open(Main_Page->GCode_File_Name);
   if(!GFile.good())
      exit(1);
   for(i=0;i<MAX_GCODE_LINES && std::getline(GFile,Lines[i]);i++)
//      if (Lines[i][Lines[i].size() - 1] == '\r')
//         Lines[i].resize(Lines[i].size() - 1);
      ;
   GFile.close();
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
   pthread_mutex_lock(&Main_Page->Print_Mutex);
   wclear(Sub_Win);
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
   Print_Queue_State_Histo();
   Touch_Win();
   pthread_mutex_unlock(&Main_Page->Print_Mutex);
   }
}
void Sender_Class::Print_Queue_State_Histo(void)
{
   uint8_t Length=(Dims.H-4)-((Actual_Line-Exec_Line)*(Dims.H-4)/MAX_SENDER_QUEUE);
   uint8_t i;
   for(i=0;i<Dims.H-4;i++)
      mvwaddch(Win,i+2,0,'.'|COLOR_PAIR(i>=Length?4:0));
}
void Sender_Class::Print_Pause(void)
{
   WINDOW* W=Main_Page->Main->Win;
   wclear(W);
   Main_Page->Main->Redraw_Box(Main_Page->Main->Selected);
   pthread_mutex_lock(&Main_Page->Print_Mutex);
      mvwaddch(W ,1 ,8  ,' '|COLOR_PAIR(250));
      mvwaddch(W ,2 ,8  ,' '|COLOR_PAIR(250));
      mvwaddch(W ,3 ,8  ,' '|COLOR_PAIR(250));

      mvwaddch(W ,1 ,11 ,' '|COLOR_PAIR(250));
      mvwaddch(W ,2 ,11 ,' '|COLOR_PAIR(250));
      mvwaddch(W ,3 ,11 ,' '|COLOR_PAIR(250));
   pthread_mutex_unlock(&Main_Page->Print_Mutex);

}
void Sender_Class::Print_Play(void)
{
   WINDOW* W=Main_Page->Main->Win;
   wclear(W);
   Main_Page->Main->Redraw_Box(Main_Page->Main->Selected);
   pthread_mutex_lock(&Main_Page->Print_Mutex);
      mvwaddch ( W ,1 ,8  ,' '|COLOR_PAIR(180 ));
      mvwaddch ( W ,1 ,9 ,' '|COLOR_PAIR(180 ));
      mvwaddch ( W ,2 ,8  ,' '|COLOR_PAIR(180 ));
      mvwaddch ( W ,2 ,9 ,' '|COLOR_PAIR(180 ));
      mvwaddch ( W ,2 ,10 ,' '|COLOR_PAIR(180 ));
      mvwaddch ( W ,3 ,8  ,' '|COLOR_PAIR(180 ));
      mvwaddch ( W ,3 ,9 ,' '|COLOR_PAIR(180 ));
   pthread_mutex_unlock(&Main_Page->Print_Mutex);

}
void Sender_Class::Print_Stop(void)
{
   WINDOW* W=Main_Page->Main->Win;
   wclear(W);
   Main_Page->Main->Redraw_Box(Main_Page->Main->Selected);
   pthread_mutex_lock(&Main_Page->Print_Mutex);
      mvwaddch(W ,1 ,8  ,' '|COLOR_PAIR(95));
      mvwaddch(W ,2 ,8  ,' '|COLOR_PAIR(95));
      mvwaddch(W ,3 ,8  ,' '|COLOR_PAIR(95));

      mvwaddch(W ,1 ,9  ,' '|COLOR_PAIR(95));
      mvwaddch(W ,2 ,9  ,' '|COLOR_PAIR(95));
      mvwaddch(W ,3 ,9  ,' '|COLOR_PAIR(95));

      mvwaddch(W ,1 ,10 ,' '|COLOR_PAIR(95));
      mvwaddch(W ,2 ,10 ,' '|COLOR_PAIR(95));
      mvwaddch(W ,3 ,10 ,' '|COLOR_PAIR(95));
   pthread_mutex_unlock(&Main_Page->Print_Mutex);

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
            if(Actual_Line==Exec_Line) {
               Next_State=STOPED;
               Print_Stop();
            }
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
      }
      Main_Page->Sender->File2Win();
   }
}
