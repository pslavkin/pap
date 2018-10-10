#include <cdk/cdk.h>
#include <thread>
#include <panel.h>

#include "dim.h"
#include "sheet.h"
#include "menu.h"
#include "gantry.h"
#include "serialmanager.hpp"
#include "histograms.h"
#include "timer.hpp"
#include "screen_update.h"


Timer_Class::Timer_Class (void)
{
}
void Timer_Class::Set_Gantry_Rti ( Gantry_Class* G )
{
   GRti = std::thread (&Gantry_Class::Rti,G);
}
void Timer_Class::Set_Histo_Rti  ( Histo_Class* H  )
{
   HRti = std::thread (&Histo_Class::Rti,H);
}


