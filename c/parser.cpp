#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "inc_all.h"

Parser_Class::Parser_Class( Sheet* Parent,Dim D )
{
   S = new Sheet(Parent,D);
   Dim Sub_Dim(2,2,D.H-4,D.W-4,"");
   Sub = new Sheet ( S,Sub_Dim,false);
   scrollok        ( Sub->Win, TRUE );
}
char* Parser_Class::Give_Next_Line (void)
{
   return (char*)"G1 X10 Y10 Z10";
};

int8_t Parser_Class::Extract_Commands(Codes_t* C)
{
   int8_t   Ans;
   char*    L;
   L=Give_Next_Line (     );
   Init_Parser      ( C,L );
   while((Ans=Parse_Byte(C))==0)
      ;
   C->Code_Count = C->Code_Index;
   return Ans;
}

int8_t Parser_Class::Init_Parser(Codes_t* C,char* L)
{
   C->Code_Index = 0;
   C->Code_Count = 0;
   C->S          = SKIPING;
   C->L          = L;
   C->L_Index    = 0;
}

bool Parser_Class::Inc_L_Index(Codes_t* C)
{
   bool Ans;
   if(C->L_Index<MAX_LINE_LENGTH) {
      C->L_Index++;
      Ans=true;
   }
   else Ans=false;
   return Ans;
}
bool Parser_Class::Inc_C_Index(Codes_t* C)
{
   bool Ans;
   if(C->C_Index<MAX_CODE_LENGTH) {
      C->C_Index++;
      Ans=true;
   }
   else Ans=false;
   return Ans;
}
bool Parser_Class::Inc_Codes_Index(Codes_t* C)
{
   bool Ans;
   if(C->Code_Index<MAX_CODES_PER_LINE) {
      C->Code_Index++;
      Ans=true;
   }
   else Ans=false;
   return Ans;
}

int8_t Parser_Class::Parse_Byte(Codes_t* C)
{
   int8_t Ans=0;
   char B=C->L[C->L_Index];
   switch(C->S) {
      case SKIPING:
         switch(B) {
            case '\0':
               Ans=LINE_END;
               break;
            case ' ':
               if(Inc_L_Index(C)==false)
                  Ans=LINE_TOO_LONG;
               break;
            default:
               C->S       = COPYING;
               C->C_Index = 0;
               if(Inc_Codes_Index(C)==false)
                  Ans=TOO_MANY_CODES;
               break;
         }
         break;
      case COPYING:
         switch(B) {
            case '\0':
               Ans=LINE_END;
               C->Codes[C->Code_Index-1][C->C_Index]='\0';
               break;
            case ' ':
               C->Codes[C->Code_Index-1][C->C_Index]='\0';
               if(Inc_L_Index(C)==false)
                  Ans=LINE_TOO_LONG;
               C->S=SKIPING;
               break;
            default:
               C->Codes[C->Code_Index-1][C->C_Index]=B;
               if(Inc_L_Index(C)==false)
                  Ans=LINE_TOO_LONG;
               if(Inc_C_Index(C)==false)
                  Ans=CODE_TOO_LONG;
               break;
         }
   }
   return Ans;
}

int8_t Parser_Class::Extract_Info(Codes_t* C)
{
   int8_t Ans;
   Init_Info_Parser ( C );
   Ans=Info_Parser(C);
   if(Ans!=INVALID_COMMAND) {
      C->Command=Ans;
      Ans=XYZ_Parser(C);
      if(Ans!=INVALID_XYZ) {
         Ans=Validate_XYZ(&(C->Pos));
         if(Ans==XYZ_NUMBERS_VALID) {
            //linea acepctada
         }
      }
   }
   return Ans;
}

void Parser_Class::Init_Info_Parser(Codes_t* C)
{
   C->Code_Index = 0;
   C->C_Index    = 0;
}

int8_t Parser_Class::Info_Parser(Codes_t* C)
{
   int8_t Ans;
   char B=C->Codes[C->Code_Index][C->C_Index];
   switch(B) {
      case 'G':
         C->C_Index++;
         B=C->Codes[C->Code_Index][C->C_Index];
         switch(B) {
            case '0':
               C->Code_Index++;
               C->C_Index=0;
               C->Code_Count--;
               Ans=G0_COMMAND;
               break;
            case '1':
               C->Code_Index++;
               C->C_Index=0;
               C->Code_Count--;
               Ans=G1_COMMAND;
               break;
            default:
               Ans=INVALID_COMMAND;
               break;
         }
         break;
      default:
         Ans=INVALID_COMMAND;
         break;
   }
   return Ans;
}

int8_t Parser_Class::XYZ_Parser(Codes_t* C)
{
   int8_t Ans=VALID_XYZ;
   while(C->Code_Count>0) {
      C->Code_Count--;
      char B=C->Codes[C->Code_Index][C->C_Index];
      switch(B) {
         case 'X':
            C->C_Index++;
            C->Pos.X=strtof(&C->Codes[C->Code_Index][C->C_Index],NULL);
            C->Code_Index++;
            C->C_Index=0;
            break;
         case 'Y':
            C->C_Index++;
            C->Pos.Y=strtof(&C->Codes[C->Code_Index][C->C_Index],NULL);
            C->Code_Index++;
            C->C_Index=0;
            break;
         case 'Z':
            C->C_Index++;
            C->Pos.Z=strtof(&C->Codes[C->Code_Index][C->C_Index],NULL);
            C->Code_Index++;
            C->C_Index=0;
            break;
         default:
            Ans=INVALID_XYZ;
            return Ans;
            break;
      }
   }
   return Ans;
}



void Parser_Class::Reset_Pos(Pos_t* Pos)
{
   Pos->X=0;
   Pos->Y=0;
   Pos->Z=0;
}

bool Parser_Class::Validate(float N)
{
   if(N>MIN_PARAM_VALUE && N<MAX_PARAM_VALUE)
      return true;
   else
      return false;
}
uint8_t Parser_Class::Validate_XYZ(Pos_t* Pos)
{
   return Validate(Pos->X) && Validate(Pos->Y) && Validate(Pos->Z)? \
      XYZ_NUMBERS_VALID: \
      XYZ_NUMBERS_INVALID;
}

void Parser_Class::Rti(void)
{
   Codes_t C;
   Extract_Commands ( &C );
   Extract_Info     ( &C );
//   wprintw(S->Win,2,2,"X=%f Y=%f Z=%f",C.Pos.X,C.Pos.Y,C.Pos.Z);


   while(1) {
      nanosleep   ( &Rti_Delay ,&Rti_Delay );
      wprintw(Sub->Win,"X=%f Y=%f Z=%f \n",C.Pos.X,C.Pos.Y,C.Pos.Z);
   }
}

