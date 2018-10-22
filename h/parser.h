#ifndef _PARSER_H
#define _PARSER_H

#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH    100
#define MAX_CODES_PER_LINE 10
#define MAX_CODE_LENGTH    20
#define MIN_PARAM_VALUE    -1000
#define MAX_PARAM_VALUE    +1000

enum COMMAND_CODES
{
   G0_COMMAND    = 0 ,
   G1_COMMAND        ,
   INVALID_XYZ,
   VALID_XYZ,
   INVALID_COMMAND,
   XYZ_NUMBERS_VALID,
   XYZ_NUMBERS_INVALID
};
enum ERROR_CODES
{
   TOO_MANY_CODES = -10 ,
   CODE_TOO_LONG        ,
   LINE_TOO_LONG        ,
   LINE_END             ,
};
typedef struct {
   float X;
   float Y;
   float Z;
} Pos_t;

typedef enum {
   SKIPING=0,
   COPYING
} Parser_State_e;

typedef struct {
   char                    Codes[MAX_CODES_PER_LINE][MAX_CODE_LENGTH];
   uint16_t                C_Index   ;
   uint8_t                 Code_Index;
   uint8_t                 Code_Count;
   char*                   L         ;
   uint16_t                L_Index   ;
   uint8_t                 Command   ;
   Pos_t                   Pos       ;
   Parser_State_e          S         ;
} Codes_t;


class Parser_Class {
   private:
      bool     Inc_C_Index(Codes_t* C);
      bool     Inc_L_Index(Codes_t* C);
      bool     Inc_Codes_Index(Codes_t* C);
      bool     Validate(float N);
   public:
      Parser_Class      ( Sheet* Parent,Dim D );
      Parser_Class      (                     );
      Sheet* S;
      Sheet* Sub;
      int8_t   Extract_Commands ( Codes_t* C          );
      int8_t   Init_Parser      ( Codes_t* C,char* L  );
      int8_t   Parse_Byte       ( Codes_t* C          );
      int8_t   Extract_Info     ( Codes_t* C          );
      void     Init_Info_Parser ( Codes_t* C          );
      int8_t   Info_Parser      ( Codes_t* C          );
      int8_t   XYZ_Parser       ( Codes_t* C          );
      void     Reset_Pos        ( Pos_t* Pos          );
      uint8_t  Validate_XYZ     ( Pos_t* Pos          );
      char*    Give_Next_Line   ( void                );
      void     Rti              ( void                );
      struct timespec Rti_Delay= { 0, 200000000}; //   5 milis
};



#endif // _PARSER_H
