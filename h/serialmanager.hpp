#ifndef SERIALMANAGER
#define SERIALMANAGER

class    Serial_Manager:public Sheet
{
   Serial_Manager  (      );
   ~Serial_Manager ( void );
public:
   pthread_t                     Pt_Serial_Manager_Rti;
   static Serial_Manager*        Serial_Manager_Inst  ;
   static struct timespec        Serial_Manager_Delay ;
   static void                   Init                          ( void                );
   static void*                  Rti                           ( void* Arg1          );
   void                          Destroy_Serial_Manager_Thread ( void                );
   int                           Open                          ( int pn,int baudrate );
   int   serial_send    ( char* pData ,int size     );
   void  serial_close   ( void                      );
   int   serial_receive ( char* buf   ,int size     );
private:
   bool Port_Status;
};

#endif


