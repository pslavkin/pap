#ifndef TIMER
#define TIMER

#include <thread>

class Timer_Class {
   public:
      Timer_Class                 (                              );
      void Set_Gantry_Rti         ( Gantry_Class* G              );
      void Set_Histo_Rti          ( Histo_Class* H               );
      void Set_Coords_Rti         ( Coords_Class* C              );
      void Set_Parser_Rti         ( Parser_Class* P              );
      void Set_TresD_Rti          ( TresD_Class* TresD           );
      void Set_Serial_Manager_Rti ( Serial_Manager_Class* S      );
      void Set_Screen_Update_Rti  ( Screen_Update_Class* SUpdate );
   protected:
   private:
      std::thread GRti;
      std::thread HRti;
      std::thread SRti;
      std::thread CRti;
      std::thread PRti;
      std::thread TresD_Rti;
      std::thread SUpdate_Rti;
};

#endif

