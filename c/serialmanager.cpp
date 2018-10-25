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
   mvwaddstr(S->Win,2,2,Port_Status?"error":"opened");
   return Port_Status;
}
void Serial_Manager_Class::Rti(void)
{
   char Buf[200],n;
   int Y,X;
   while ( 1 ) {
      if(Port_Status==0) {

         serial_send((char*)"pos\r",4);
         nanosleep     ( &Rti_Delay,&Rti_Delay );
         n=serial_receive(Buf,200);
         sscanf(Buf,"Pos= %d %d",&Y,&X);
         pthread_mutex_lock(&Main_Page->Print_Mutex);
            wprintw(S->Win,"Y=%d X=%d\n",Y,X);
            Main_Page->Coords->X=X;
            Main_Page->Coords->Y=Y;
         pthread_mutex_unlock(&Main_Page->Print_Mutex);
      }
      else
         nanosleep     ( &Rti_Delay,&Rti_Delay );
   }
}
Serial_Manager_Class::Serial_Manager_Class( Sheet* Parent,Dim D )
{
   S           = new Sheet(Parent,D);
   scrollok        ( S->Win, TRUE );
   Port_Status = 1;
   portNumber  = 0;
   Open(0,115200);
}
//----------------------------------------------------------------------------------------------------
