#ifndef SERIALMANAGER
#define SERIALMANAGER

class    Serial_Manager_Class
{
   public:
      Serial_Manager_Class  ( Sheet* Parent,Dim D );
      Serial_Manager_Class  (          );
      Sheet* S;
      void Rti ( void );
      int      serial_send    ( char* pData ,int size );
   private:
      int      Open           ( int pn,int baudrate   );
      void     serial_close   ( void                  );
      int      serial_receive ( char* buf   ,int size );
      bool     Port_Status;
      uint8_t  portNumber ;
      struct timespec Rti_Delay= { 0,100000000};
};

#endif


