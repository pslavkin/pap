#include <cdk/cdk.h>
#include <panel.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "screen_update.h"
#include "sheet.h"
#include "rs232.h"
#include "menu.h"
#include "serialmanager.hpp"

static int portNumber=0;

//hago que retorne int porque quiero chequear errores al llamar..
//no se porque no lo tienee implementado...
int serial_send(char* pData,int size)
{
   SendBuf(portNumber, (unsigned char*)pData, size);
}

void serial_close(void)
{
   CloseComport(portNumber);
   printf("serial port closed\r\n");
}

int serial_receive(char* buf,int size)
{
   return PollComport(portNumber, (unsigned char*) buf,size);
}


struct timespec      Serial_Manager::Serial_Manager_Delay={0,50000000}; //100 milis
Serial_Manager*      Serial_Manager::Serial_Manager_Inst;

int Serial_Manager::Open(int pn,int baudrate)
{
   portNumber = pn;
   Port_Status=OpenComport(portNumber,baudrate);
   mvwaddstr(Serial_Manager_Inst->Win,10,10,Port_Status?"error":"opened");
   return Port_Status;
}
void Serial_Manager::Init(void)
{
   Serial_Manager_Inst = new Serial_Manager;
   Serial_Manager_Inst->Set_Panel_User_Pointer ( Serial_Manager_Inst );
   Serial_Manager_Inst->Set_Size   ( 20,30  )        ;
   Serial_Manager_Inst->Set_Pos    ( 10,10  )        ;
   Serial_Manager_Inst->Set_Name   ( (char* )"rs232");
   Serial_Manager_Inst->Redraw_Box (        )        ;
   Serial_Manager_Inst->Port_Status=1;
}

void* Serial_Manager::Rti(void* Arg1)
{
   while ( 1 ) {
      nanosleep ( &Serial_Manager_Delay,&Serial_Manager_Delay );
      if(Serial_Manager_Inst->Port_Status==0) {
         waddstr(Serial_Manager_Inst->Win,"abierto!");
      }
      
   }
}

Serial_Manager::Serial_Manager():Sheet(NULL)
{
   pthread_create ( &Pt_Serial_Manager_Rti, NULL, Rti, NULL );
}
Serial_Manager::~Serial_Manager(void)
{
   pthread_exit ( &Pt_Serial_Manager_Rti );
}
//----------------------------------------------------------------------------------------------------

