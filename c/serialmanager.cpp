#include "inc_all.h"

int Serial_Manager_Class::serial_send(char* pData,int size)
{
   SendBuf(portNumber, pData, size);
}
void Serial_Manager_Class::serial_close(void)
{
   CloseComport ( portNumber               );
   printf       ( "serial port closed\r\n" );
}
int Serial_Manager_Class::serial_receive(char* buf,int size)
{
   return PollComport(portNumber, (unsigned char*) buf,size);
}
int Serial_Manager_Class::Open(int pn,int baudrate)
{
   portNumber  = pn;
   Port_Status = OpenComport(portNumber,baudrate);
   mvwaddstr(S->Win,1,2,Port_Status?"error":"opened");
   return Port_Status;
}
void Serial_Manager_Class::Rti(void)
{
   using namespace std::chrono;
   high_resolution_clock::time_point t1 = high_resolution_clock::now();
   high_resolution_clock::time_point Time;
   char Buf[200],n;
   int32_t Y=0,X=0,Z=0;
   uint32_t Exec_Line;
   float Speed_X=0,Speed_Y=0,Speed_Z=0;
   while ( 1 ) {
      if(Port_Status==0) {
         nanosleep     ( &Rti_Delay,&Rti_Delay );
         serial_send((char*)"pos\rspeed\rspace\rline\r",21);
         nanosleep     ( &Ans_Delay,&Ans_Delay );
         n=serial_receive(Buf,200);
         sscanf(Buf,"Pos= %d %d %d\rstep/seg= %f %f %f\rspace=%d\rline=%d\r"
               ,&X,&Y,&Z,&Speed_X,&Speed_Y,&Speed_Z,&Available_Space,&Exec_Line);
         Time                       = high_resolution_clock::now();
         duration<double> time_span = duration_cast<duration<double>>(Time-t1);
         Main_Page->Sender->Exec_Line      = Exec_Line>0?(Exec_Line-1):Exec_Line;
         Main_Page->Coords->Actual_Y       = (float)Y/Y_SCALE;
         Main_Page->Coords->Actual_X       = (float)X/X_SCALE;
         Main_Page->Coords->Actual_Z       = (float)Z/Z_SCALE;
         Main_Page->Coords->Actual_Speed_Y = (float)((float)Speed_Y*MICROSTEP)/Y_SCALE;
         Main_Page->Coords->Actual_Speed_X = (float)((float)Speed_X*MICROSTEP)/X_SCALE;
         Main_Page->Coords->Actual_Speed_Z = (float)((float)Speed_Z*MICROSTEP)/Z_SCALE;
         Main_Page->Coords->Actual_Speed   = sqrt(
               Main_Page->Coords->Actual_Speed_Y*Main_Page->Coords->Actual_Speed_Y+\
               Main_Page->Coords->Actual_Speed_X*Main_Page->Coords->Actual_Speed_X+\
               Main_Page->Coords->Actual_Speed_Z*Main_Page->Coords->Actual_Speed_Z
               );
         Main_Page->Coords->X       = X;
         Main_Page->Coords->Y       = Y;
         Main_Page->Coords->Z       = Z;
         Main_Page->Coords->Speed_Y = Speed_Y;
         Main_Page->Coords->Speed_X = Speed_X;
         Main_Page->Coords->Speed_Z = Speed_Z;
         Main_Page->Coords->Speed   = sqrt(Speed_X*Speed_X+Speed_Y*Speed_Y+Speed_Z*Speed_Z);
         Log_File                                      <<
            Main_Page->Coords->Actual_X       <<
            ' '                               <<
            Main_Page->Coords->Actual_Y       <<
            ' '                               <<
            Main_Page->Coords->Actual_Z       <<
            ' '                               <<
            Main_Page->Coords->Actual_Speed_X <<
            ' '                               <<
            Main_Page->Coords->Actual_Speed_Y <<
            ' '                               <<
            Main_Page->Coords->Actual_Speed_Z <<
            ' '                               <<
            time_span.count()                 <<
            ' '                               <<
            Available_Space                   <<
            std::endl;
         pthread_mutex_lock(&Main_Page->Print_Mutex);
         wprintw(Sub->Win,"X%05d Y%05d Z%05d\nSX%06.2f SY%06.2f SZ%06.2f Q%d N%d\n"
               ,X,Y,Z,Speed_X,Speed_Y,Speed_Z,Available_Space,Exec_Line);
         pthread_mutex_unlock(&Main_Page->Print_Mutex);

         Main_Page->Sender->File2Win();
         if(Available_Space>0) {
            if(Main_Page->Sender->Actual_Line<=Main_Page->Sender->Total_Lines) {
               serial_send((char*)"GL ",3);
               serial_send((char*)Main_Page->Sender->Lines[Main_Page->Sender->Actual_Line].c_str(),Main_Page->Sender->Lines[Main_Page->Sender->Actual_Line].length());
               serial_send((char*)"\r",1);
               nanosleep     ( &Ans_Delay,&Ans_Delay );
               n=serial_receive(Buf,200);
               sscanf(Buf,"ok\r");
               Main_Page->Sender->Actual_Line++;
            }
         }
      }
      else {
         nanosleep     ( &Open_Port_Delay,&Open_Port_Delay );
         if(Open(0,115200)==0) {
            serial_send((char*)"init\rhome\r",10);
         }
      }
   }
}
Serial_Manager_Class::Serial_Manager_Class( Sheet* Parent,Dim D )
{
   S           = new Sheet(Parent,D);
   Dim Sub_Dim(2,2,D.H-4,D.W-4,"");
   Sub = new Sheet ( S,Sub_Dim,false);
   scrollok        ( Sub->Win, TRUE );
   Port_Status = 1;
   portNumber  = 0;
   Log_File.open("./octave/log.txt");
}
//----------------------------------------------------------------------------------------------------
