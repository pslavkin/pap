#ifndef SCREEN_UPDATE
#define SCREEN_UPDATE

#include <thread>

class Screen_Update_Class {

   public:
      Screen_Update_Class ( void      );
      void Start_Rti      ( void      );
      void Rti            ( void );
      void Set_Gantry_Rti ( Gantry_Class* G );
      void Set_Histo_Rti  ( Histo_Class* H  );
      Gantry_Class* G;
      Histo_Class* H;
   private:
      std::thread TRti;
      struct timespec Rti_Delay= { 0, 2000000}; //   5 milis
};

#endif
//----------------------------------------------------------------------------------------------------
