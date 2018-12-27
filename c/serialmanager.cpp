#include "inc_all.h"
using namespace std::chrono;

int Serial_Manager_Class::serial_send(char* pData,int size)
{
   SendBuf(Port_Number, pData, size);
}
void Serial_Manager_Class::serial_close(void)
{
   CloseComport ( Port_Number             );
   printf ( "serial port closed\n" );
}
void Serial_Manager_Class::Serial_Bloked_Get_Line(char* Buf,uint8_t Size)
{
   uint8_t Index = 0;
   unsigned char  Data;
   while(1) {
      while ( Get_Byte(Port_Number,&Data )!=1)
         nanosleep ( &Rti_Delay,&Rti_Delay );

      if ( (Data == '\r' )|| (Data == '\n') || (Data == 0x1b)) {
         break;
      }
      if(Index < Size) {
         Buf[Index] = Data;
         Index++;
      }
   }
   Buf[Index] = 0;
}

int Serial_Manager_Class::serial_receive(char* buf,int size)
{
   int Ans;
   Ans=PollComport(Port_Number, (unsigned char*) buf,size);
   return Ans;
}
int Serial_Manager_Class::Open(int pn,int baudrate)
{
   char Buf[MAX_ANS_SIZE];
   Port_Status = OpenComport(Port_Number,baudrate);
   wprintw(Sub_Win,"\n serial port %d status %s \n",Port_Number,(Port_Status?"error":"opened"));
   if(Port_Status==0){
   }
   else {
      if(Port_Number<MAX_SERIAL_PORTS)
         Port_Number++;
      else
         Port_Number=0;
   }
   return Port_Status;
}

uint8_t Serial_Manager_Class::Send_And_Forget(const char* S)
{
   if(Port_Status==0) {
      pthread_mutex_lock(&Main_Page->Serial_Mutex);
      serial_send ( (char* )S,strlen(S));
      pthread_mutex_unlock(&Main_Page->Serial_Mutex);
   }
}

void Serial_Manager_Class::Log(void)
{
   Coords_Class* C=Main_Page->Coords;
   high_resolution_clock::time_point Time;
   Time                       = high_resolution_clock::now();
   duration<double> time_span = duration_cast<duration<double>>(Time-t1);
//   if(Log_File.good() && Main_Page->Sender->Is_Running()) {
      C->Plot_Lines++;
      Log_File << C->Actual_X       << ' ' << C->Actual_Y       << ' ' << C->Actual_Z       << ' ' <<
                  C->Actual_Speed_X << ' ' << C->Actual_Speed_Y << ' ' << C->Actual_Speed_Z << ' ' << 
                  time_span.count() << std::endl;
 //  }
}

void Serial_Manager_Class::Rti(void)
{
   char        Buf[MAX_ANS_SIZE];
   int32_t     Y       ,X      ,Z      ;
   float       Speed_X ,Speed_Y,Speed_Z;
   while(Open(Port_Number,115200)!=0)
      nanosleep ( &Open_Port_Delay,&Open_Port_Delay );

   t1 = high_resolution_clock::now();

   while ( 1 ) {
      Serial_Bloked_Get_Line(Buf,sizeof(Buf));
      sscanf(Buf,"%d %d %d %f %f %f %d %d %d %f %f %d %d"
            ,&X,&Y,&Z,&Speed_X,&Speed_Y,&Speed_Z,&Space,
            &Main_Page->Sender->Exec_Line,
            &Main_Page->Sender->Actual_Line,
            &Main_Page->Coords->Acc,
            &Main_Page->Coords->Dec,
            &Main_Page->Coords->Speed_Limit,
            &Main_Page->Coords->Speed_Scale
            );
      Main_Page->Coords->Machine2Coords(X,Y,Z,Speed_X,Speed_Y,Speed_Z);
      Log();
      pthread_mutex_lock(&Main_Page->Print_Mutex);
      wprintw(Sub_Win,"X%05d Y%05d Z%05d SX%06.2f SY%06.2f SZ%06.2f Q%d EN%d WN%d Acc%8.2f Dec%8.2f SL%d SS%d\n"
            ,X,Y,Z,Speed_X,Speed_Y,Speed_Z,Space,
            Main_Page->Sender->Exec_Line,
            Main_Page->Sender->Actual_Line,
            Main_Page->Coords->Acc,
            Main_Page->Coords->Dec,
            Main_Page->Coords->Speed_Limit,
            Main_Page->Coords->Speed_Scale
            );
      pthread_mutex_unlock(&Main_Page->Print_Mutex);
      Touch_Win();
   }
}
Serial_Manager_Class::Serial_Manager_Class( Sheet* Parent,Dim D ):Sheet(Parent,D)
{
   scrollok ( Sub_Win, TRUE );
   Port_Status = 1;
   Port_Number = 0;
   Log_File.open("octave/log.txt");

//   Log_File_Lines=0;
}
void Serial_Manager_Class::Reopen_Log(void)
{
   Log_File.close();
   Log_File.open("octave/log.txt");
   Main_Page->Coords->Plot_Lines=0;
}
void Serial_Manager_Class::Key(int K)
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
      case 'S':
         Toogle_Simulation();
         break;
      case 'u':
         Toogle_Full_Restore_Screen();
         break;
      case 'W':
         {
         std::string S;
         Input_Log_File.open ( "octave/log.txt"      );
         Last_Log_File.open  ( "octave/last_log.txt" );
         while(std::getline(Input_Log_File,S)) {
            Last_Log_File << S << std::endl;
         }
         Last_Log_File.close();
         Input_Log_File.close();
         }
         break;
   }
}

void Serial_Manager_Class::Toogle_Simulation (void)
{
   if(Simulation==true)
      Simulation=false;
   else
      Simulation=true;
}
//----------------------------------------------------------------------------------------------------
