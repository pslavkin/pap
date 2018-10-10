#ifndef TIMER
#define TIMER

#include <thread>

class Timer_Class {
   public:
      Timer_Class ();
      void Rti       ( void );
      void Start_Rti ( void );
   protected:
   private:
      std::thread TRti;
};

#endif

