#ifndef TIMER
#define TIMER

#include <thread>

class Timer_Class {
   public:
      Timer_Class ();
      void Set_Gantry_Rti ( Gantry_Class* G );
      void Set_Histo_Rti  ( Histo_Class* H  );
      void Set_Coords_Rti ( Coords_Class* C );
      void Set_Serial_Manager_Rti ( Serial_Manager_Class* S );
   protected:
   private:
      std::thread GRti;
      std::thread HRti;
      std::thread SRti;
      std::thread CRti;
};

#endif

