#include "inc_all.h"

Coords_Class::Coords_Class(Sheet* Parent,Dim D)
{
   S = new Sheet(Parent,D);
   mvwprintw(S->Win ,1 ,7 ,"X         Y         Z");
   X     = 0       ;
   Y     = 0       ;
   Z     = 0       ;
   Jog_X = 0       ;
   Jog_Y = 0       ;
   Jog_Z = 0       ;
   Max_X = 2097152 ;
   Max_Y = 2097152 ;
   Max_Z = 20      ;
   Min_X = -2097152;
   Min_Y = -2097152;
   Min_Z = 1       ;
}
void Coords_Class::Rti(void)
{
   while(1) {
      nanosleep     ( &Rti_Delay,&Rti_Delay );

#define INC 1
//      switch(rand()%4) {
//         case 0:
//            if(X<(Max_X-INC)) {
//               X+=INC;
//            }
//            else
//               X--;
//            break;
//         case 1:
//            if(X>(Min_X+INC))
//               X-=INC;
//            else
//               X++;
//            break;
//         case 2:
//            if(Y<(Max_Y-INC)) {
//               Y+=INC;
//            }
//            else
//               Y--;
//            break;
//         case 3:
//            if(Y>(Min_Y+INC))
//               Y-=INC;
//            else
//               Y++;
//            break;
//      }
      if(rand()%2) {
              if(Z<Max_Z) Z++;
      }
         else if(Z>Min_Z) Z--;
      Write();
   }
}
void Coords_Class::Write(void)
{
   pthread_mutex_lock(&Main_Page->Print_Mutex);
      wattron(S->Win,A_BOLD);
      mvwprintw(S->Win,2,3,"%+011.3f  %+011.3f  %+011.3f",(float)X/10,(float)Y/10,(float)Z/10);
      wattroff(S->Win,A_BOLD);
      wcolor_set(S->Win, 2,NULL);
      mvwprintw(S->Win,3,3,"%+011.3f  %+011.3f  %+011.3f",(float)Jog_X/10,(float)Jog_Y/10,(float)Jog_Z/10);
      wcolor_set(S->Win, 0,NULL);
   pthread_mutex_unlock(&Main_Page->Print_Mutex);
}

void Coords_Class::Update(int32_t X, int32_t Y, int32_t Z)
{
   this->X = X;
   this->Y = Y;
   this->Z = Z;
   Write();
}

void Coords_Class::Jog2Machine(void)
{
   Jog_Y=Y;
   Jog_X=X;
}
