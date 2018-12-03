#ifndef SCREEN_UPDATE
#define SCREEN_UPDATE

#include <thread>

class Screen_Update_Class {

   public:
      Screen_Update_Class ( void );
      void Rti            ( void );
   private:
      struct timespec Rti_Delay= { 0,SCREEN_UPDATE_RTI }; //   5 milis
};

#endif
//----------------------------------------------------------------------------------------------------
