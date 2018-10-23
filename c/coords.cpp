#include "inc_all.h"

Coords_Class::Coords_Class(Sheet* Parent,Dim D)
{
   S = new Sheet(Parent,D);
   mvwprintw(S->Win ,1 ,7 ,"X         Y         Z");
   X     = 0    ;
   Y     = 0    ;
   Z     = 0    ;
   Max_X = 1000 ;
   Max_Y = 1000 ;
   Max_Z = 20   ;
   Min_X = -1000;
   Min_Y = -1000;
   Min_Z = 1    ;
}
void Coords_Class::Rti(void)
{
   while(1) {
      nanosleep     ( &Rti_Delay,&Rti_Delay );
      switch(rand()%4) {
         case 0:
            if(X<(Max_X-50)) {
               X+=rand()%50;
            }
            else
               X--;
            break;
         case 1:
            if(X>(Min_X+50))
               X-=rand()%50;
            else
               X++;
            break;
         case 2:
            if(Y<(Max_Y-50)) {
               Y+=rand()%50;
            }
            else
               Y--;
            break;
         case 3:
            if(Y>(Min_Y+50))
               Y-=rand()%50;
            else
               Y++;
            break;
      }
      if(rand()%2) {
              if(Z<Max_Z) Z++;
      }
         else if(Z>Min_Z) Z--;
      Write();
   }
}
void Coords_Class::Write(void)
{
   wattron(S->Win,A_BOLD);
   mvwprintw(S->Win,2,3,"%+08.3f  %+08.3f  %+08.3f",(float)X/10,(float)Y/10,(float)Z/10);
   wattroff(S->Win,A_BOLD);
}

void Coords_Class::Update(int32_t X, int32_t Y, int32_t Z)
{
   this->X = X;
   this->Y = Y;
   this->Z = Z;
   Write();
}
