#include <thread>
#include "timer.hpp"


Timer_Class::Timer_Class (void)
{
}
void Timer_Class::Start_Rti(void )
{
  TRti=  std::thread (&Timer_Class::Rti,this);
}

void Timer_Class::Rti(void )
{
      //do
}

