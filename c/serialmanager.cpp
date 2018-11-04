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
   float Speed_X=0,Speed_Y=0,Speed_Z=0;
   while ( 1 ) {
      if(Port_Status==0) {
         serial_send((char*)"pos\rspeed\rq\r",12);
         nanosleep     ( &Rti_Delay,&Rti_Delay );
         n=serial_receive(Buf,200);
         sscanf(Buf,"Pos= %d %d %d\rstep/seg= %f %f %f\rspace=%d",&X,&Y,&Z,&Speed_X,&Speed_Y,&Speed_Z,&Available_Space);
         Time=high_resolution_clock::now();
         duration<double> time_span = duration_cast<duration<double>>(Time-t1);
         Log_File << X << ' ' << Y << ' ' << Z << ' ' << Speed_X << ' ' << Speed_Y << ' ' << Speed_Z << ' ' << time_span.count() << ' ' << Available_Space << std::endl;
            Main_Page->Coords->X=X;
            Main_Page->Coords->Y=Y;
            Main_Page->Coords->Z=Z;
            Main_Page->Coords->Speed_X=Speed_X;
            Main_Page->Coords->Speed_Y=Speed_Y;
            Main_Page->Coords->Speed_Z=Speed_Z;
            Main_Page->Coords->Speed=sqrt(Speed_X*Speed_X+Speed_Y*Speed_Y+Speed_Z*Speed_Z);
         pthread_mutex_lock(&Main_Page->Print_Mutex);
            wprintw(Sub->Win,"X%05d Y%05d Z%05d\nSX%06.2f SY%06.2f SZ%06.2f Q%d\n",X,Y,Z,Speed_X,Speed_Y,Speed_Z,Available_Space);
         pthread_mutex_unlock(&Main_Page->Print_Mutex);
      }
      else {
         nanosleep     ( &Open_Port_Delay,&Open_Port_Delay );
         if(Open(0,115200)==false) {
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
