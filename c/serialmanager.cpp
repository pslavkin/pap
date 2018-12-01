#include "inc_all.h"
using namespace std::chrono;

int Serial_Manager_Class::serial_send(char* pData,int size)
{
   SendBuf(portNumber, pData, size);
   Log_File << "<" << pData << std::endl;
}
void Serial_Manager_Class::serial_close(void)
{
   CloseComport ( portNumber             );
   printf       ( "serial port closed\n" );
}
int Serial_Manager_Class::serial_receive(char* buf,int size)
{
   int Ans;
   Ans=PollComport(portNumber, (unsigned char*) buf,size);
   Log_File << ">" << buf << std::endl;
   return Ans;
}
int Serial_Manager_Class::Open(int pn,int baudrate)
{
   char Buf[MAX_ANS_SIZE];
   Port_Status = OpenComport(portNumber,baudrate);
   mvwaddstr(Sub_Win,0,0,Port_Status?"error":"opened");
   if(Port_Status==0)
      Send_And_Receive("halt\nrstpos\nhalt\n",Buf,sizeof(Buf));
   return Port_Status;
}

uint8_t Serial_Manager_Class::Send_And_Receive(const char* S, char* Buf, uint8_t Length)
{
   uint8_t Aux_Buf[100];
   uint8_t Ans;
   pthread_mutex_lock(&Main_Page->Serial_Mutex);
   {
      while(PollComport(portNumber, Aux_Buf,sizeof(Aux_Buf))==sizeof(Aux_Buf)) //purga basura pendiente
         ;
      serial_send ( (char* )S,strlen(S));
      nanosleep             ( &Ans_Delay,&Ans_Delay );
      Ans=serial_receive ( Buf,Length );
   }
   pthread_mutex_unlock(&Main_Page->Serial_Mutex);
   return Ans;
}

void Serial_Manager_Class::Log(void)
{
   Coords_Class* C=Main_Page->Coords;
   high_resolution_clock::time_point Time;
   Time                       = high_resolution_clock::now();
   duration<double> time_span = duration_cast<duration<double>>(Time-t1);
   if(Log_File.good()) {
   Log_File << C->Actual_X       << ' ' << C->Actual_Y       << ' ' << C->Actual_Z       << ' ' <<
               C->Actual_Speed_X << ' ' << C->Actual_Speed_Y << ' ' << C->Actual_Speed_Z << ' ' << 
               time_span.count() << std::endl;
   }
}

void Serial_Manager_Class::Rti(void)
{
   char Buf[MAX_ANS_SIZE],n;
   int32_t Y=0,X=0,Z=0;
   uint32_t Exec_Line;
   float Speed_X=0,Speed_Y=0,Speed_Z=0;
   while ( 1 ) {
      if(Port_Status==0) {
         nanosleep ( &Rti_Delay,&Rti_Delay );
         Send_And_Receive("pos\nspeed\nspace\nline\n",Buf,sizeof(Buf));
         sscanf(Buf,"pos= %d %d %d step/seg= %f %f %f space=%d line=%d"
               ,&X,&Y,&Z,&Speed_X,&Speed_Y,&Speed_Z,&Space,&Exec_Line);

         Main_Page->Coords->Machine2Coords(X,Y,Z,Speed_X,Speed_Y,Speed_Z);
         Main_Page->Sender->Exec_Line      = Exec_Line;
         //Log();
         pthread_mutex_lock(&Main_Page->Print_Mutex);
            wprintw(Sub_Win,"X%05d Y%05d Z%05d SX%06.2f SY%06.2f SZ%06.2f Q%d N%d\n"
                  ,X,Y,Z,Speed_X,Speed_Y,Speed_Z,Space,Exec_Line);
         pthread_mutex_unlock(&Main_Page->Print_Mutex);
      }
      else {
         nanosleep     ( &Open_Port_Delay,&Open_Port_Delay );
         if(Open(portNumber,115200)==0)
            t1 = high_resolution_clock::now();
      }
   Touch_Win();
   }
}
Serial_Manager_Class::Serial_Manager_Class( Sheet* Parent,Dim D ):Sheet(Parent,D)
{
   scrollok ( Sub_Win, TRUE );
   Port_Status = 1;
   portNumber  = 1;
   Log_File.open("octave/log.txt");
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
      case 'u':
         Toogle_Full_Restore_Screen();
         break;
   }
}
//----------------------------------------------------------------------------------------------------
