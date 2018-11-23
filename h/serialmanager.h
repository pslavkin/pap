#ifndef SERIALMANAGER
#define SERIALMANAGER

class    Serial_Manager_Class
{
   public:
      Serial_Manager_Class  ( Sheet* Parent,Dim D );
      Serial_Manager_Class  (          );
      Sheet* S;
      Sheet* Sub;
      void Rti ( void );
      int      serial_send    ( char* pData ,int size );
      int      serial_receive ( char* buf   ,int size );
      bool     Port_Status;
      uint16_t Available_Space=0;
   private:
      std::ofstream Log_File;
      int      Open           ( int pn,int baudrate   );
      void     serial_close   ( void                  );
      uint8_t  portNumber ;
      struct timespec Rti_Delay= { 0,  50000000};
      struct timespec Open_Port_Delay= { 0,900000000};
};

#endif


