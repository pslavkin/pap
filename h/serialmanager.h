#ifndef SERIALMANAGER
#define SERIALMANAGER

class    Serial_Manager_Class:public Sheet {
   public:
      Serial_Manager_Class  ( Sheet* Parent,Dim D );
      std::chrono::high_resolution_clock::time_point t1;
      bool     Port_Status;
      uint16_t Space=0;
      void Rti ( void );
      void Log                 ( void                                     );
      int      serial_send     ( char* pData ,int size                    );
      int      serial_receive  ( char* buf   ,int size                    );
      uint8_t Send_And_Forget     ( const char* S);
      void Serial_Bloked_Get_Line ( char* Buf,uint8_t Size                       );
      void Toogle_Simulation (void);
      void Reopen_Log(void);
   private:
      std::ofstream Log_File;
      std::ofstream Full_Log_File;
      std::ifstream Input_Log_File;
      std::ofstream Last_Log_File    ;
      std::ifstream Simul_Log_File    ;
      bool Simulation=false;
      uint8_t       Port_Number ;
      int      Open         ( int pn,int baudrate );
      void     Key              ( int K               );
      void     serial_close ( void                );
      struct timespec Rti_Delay       = { 0 ,SERIAL_MANAGER_RTI}    ;
      struct timespec Open_Port_Delay = { 0 ,SERIAL_OPEN_PORT_DELAY};
};

#endif


