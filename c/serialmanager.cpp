#include "inc_all.h"

int Serial_Manager_Class::serial_send(char* pData,int size)
{
   SendBuf(portNumber, (unsigned char*)pData, size);
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
   while ( 1 ) {
      nanosleep     ( &Rti_Delay,&Rti_Delay );
      }
}
Serial_Manager_Class::Serial_Manager_Class( Sheet* Parent,Dim D )
{
   S           = new Sheet(Parent,D);
   Port_Status = 1;
   portNumber  = 0;
   Open(0,115200);
}
//----------------------------------------------------------------------------------------------------
