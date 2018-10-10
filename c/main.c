#include <cdk/cdk.h>
#include <panel.h>
#include <ncurses.h>
#include <string.h>

#include "dim.h"
#include "sheet.h"
#include "gantry.h"
#include "menu.h"
#include "main.h"
#include "bed.hpp"
#include "serialmanager.hpp"
#include "histograms.h"
#include "dim.h"
#include "screen_update.h"

void Init_Curses (void);

Gantry_Class* G,*H;

int main(int argc, char **argv)
{
   Init_Curses        (            );
   Init_Menu          (            );
   Params_Parser      ( argc,argv  );
   for(;;)
      sleep(10);
      ;
   return 0;
}

void Init_Super_Colours(unsigned char R,unsigned char G,unsigned char B,unsigned char From, unsigned char Count)
{
   unsigned short int i,Bg,Pair;
   Pair=MIN_COLOUR_PAIR+From; // los primeros 64 se los regalo a CDK en su llamada a initCDKColor
   Bg=16+From;                // cdk usa solo 8 colores... me agarro el resto (parece que tambien usa el 15...raaaro)
   for(i=1;i<Count;i++)    {  // no me puedo pasar de 255 pares... no da mas la funcion PAIR_NUMBER.. si no fuera por eso podria seguir...
      init_pair (Pair,255,Bg);
      init_color(Bg,(i*1000/Count)*R,(i*1000/Count)*G,(i*1000/Count)*B);
      Bg++;
      Pair++;
   }
}
void Init_Curses (void)
{
   initscr ( );
   cbreak       (              );
   noecho       (              );
   keypad       ( stdscr, TRUE );
   nodelay      ( stdscr,true  );
   initCDKColor (              );
   //start_color        (                                    );
   Init_Super_Colours ( 0,0,1,  0,192                      );
   curs_set           ( 0                                  );
}
//----------------------------------------------------------------------------------------------------
void Print_Usage(FILE *stream, int exit_code)
{
   fprintf(stream, "Usage options\n");
   fprintf(stream,
      "  -h  --help           Display this usage information.\n"
      "  -v  --version        Print version.\n"
      "  -c  --config-file windows organization file\n"
      "  -r  --opeation start operation\n");
   exit(exit_code);
}
//----------------------------------------------------------------------------------------------------
void Params_Parser(int argc, char **argv)
{
   int next_option;
   const char *const short_options = "hvc:o:";
   const struct option long_options[] = {
      { "help"        ,no_argument       ,NULL ,'h' },
      { "version"     ,no_argument       ,NULL ,'v' },
      { "config-file" ,required_argument ,NULL ,'c' },
      { "operation"   ,required_argument ,NULL ,'o' },
      { NULL          ,no_argument       ,NULL ,0   }
   };
   while ( (next_option = getopt_long(argc, argv, short_options, long_options, NULL) ) != -1 ) {
      switch ( next_option ) {
         case 'h':
             // Print_Usage(stdout, 0);
              break;
         case 'v': 
              printf("cdk v1.0\n");
              printf("Copyright (C) disenioconingenio\n");
              break;
         case 'c':
              break;
         case 'o':
              break;
         case '?':
            //  Print_Usage(stdout, 1);
              break;
      }
   }
}
