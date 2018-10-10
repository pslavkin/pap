#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <cdk/cdk.h>
#include <panel.h>
#include <pthread.h>

#include "dim.h"
#include "sheet.h"
#include "gantry.h"
#include "serialmanager.hpp"
#include "menu.h"
#include "histograms.h"
#include "screen_update.h"

//----------------------------------------------------------------------------------------------------
Histo_Class::Histo_Class(Sheet* Parent,Dim D ,uint32_t Max_Value, uint32_t Value)
{
   this->S = new Sheet(Parent,D);
   this->Max_Value = Max_Value;
   this->Value     = Value;
   Set_V_Inverted_Rule_Value(Value);
};
void Histo_Class::Set_V_Inverted_Rule_Value(uint16_t Value)
{
   uint16_t i;
   uint16_t Height=S->Dims.H-2;
   Value= ( Value*Height )/Max_Value;
   for(i=0;i<Height;i++)
      mvwaddch(S->Win,Height-i,1,Value<(Height-i)?('.'|COLOR_PAIR(0)):(' '|COLOR_PAIR(3)));
}
void Histo_Class::Rti(void)
{
   Set_V_Inverted_Rule_Value(rand()%Max_Value);
}

