#ifndef TIMER
#define TIMER

#include <thread>

class Timer_Class {
   public:
      Timer_Class ();
      void Set_Gantry_Rti ( Gantry_Class* G );
      void Set_Histo_Rti  ( Histo_Class* H  );
   protected:
   private:
      std::thread GRti;
      std::thread HRti;
};

#endif

