#include <stdio.h>
#include <panel.h>
#include <string.h>
#include "dim.h"
#include "sheet.h"

Dim::Dim()
{
}
Dim::Dim(uint16_t Y, uint16_t X, uint16_t H, uint16_t W, const char* N)
{
   this->Y    = Y;
   this->X    = X;
   this->H    = H;
   this->W    = W;
   strncpy(this->Name,N,sizeof(this->Name)-1);
}

