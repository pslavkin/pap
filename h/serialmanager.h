#ifndef SERIALMANAGER
#define SERIALMANAGER

#define MAX_ANS_SIZE 200
class    Serial_Manager_Class:public Sheet {
   public:
      Serial_Manager_Class  ( Sheet* Parent,Dim D );
      std::chrono::high_resolution_clock::time_point t1;
      void Rti ( void );
      int      serial_send    ( char* pData ,int size );
      int      serial_receive ( char* buf   ,int size );
      bool     Port_Status;
      void Log(void);
      uint16_t Space=0;
      uint8_t Send_And_Receive(const char* S, char* Buf, uint8_t Length);
   private:
      std::ofstream Log_File;
      int      Open         ( int pn,int baudrate );
      void Key              ( int K               );
      void     serial_close ( void                );
      uint8_t  portNumber ;
      struct timespec Rti_Delay= { 0, 3000000};
      struct timespec Ans_Delay= { 0, 20000000}; //ans delay
      struct timespec Open_Port_Delay= { 0,900000000};
};

#endif


