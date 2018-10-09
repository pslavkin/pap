#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <cdk/cdk.h>
#include <panel.h>
#include <pthread.h>

#include "dim.h"
#include "sheet.h"
#include "screen_update.h"
#include "serialmanager.hpp"
#include "menu.h"
#include "histograms.h"

//----------------------------------------------------------------------------------------------------
Histo_Class::Histo_Class(Sheet* Parent,uint16_t Y,uint16_t X,uint16_t Height, uint16_t Width,char* Tittle,\
          uint32_t Max_Value, uint32_t Value) \
         : Sheet(Parent,Y,X,Height+2,Width+2,Tittle)
{
   this->Y         = Y;
   this->X         = X;
   this->Max_Value = Max_Value;
   this->Value     = Value;
   this->Height    = Height;
   Set_V_Inverted_Rule_Value(Value);
};
void Histo_Class::Set_V_Inverted_Rule_Value(uint16_t Value)
{
   uint16_t i;
   Value=((Value/(float)Max_Value))*(Height-1);
   for(i=0;i<(Height);i++)
      mvwaddch(Win,Height-i,1,Value<=(Height-i)?('.'|COLOR_PAIR(0)):(' '|COLOR_PAIR(3)));
}

