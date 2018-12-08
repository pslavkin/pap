#include "inc_all.h"

Curses_Color_Class*  Curses;
Main_Page_Class*     Main_Page=NULL;


int main(int argc, char **argv)
{
   Main_Page = new Main_Page_Class    (        );
   Params_Parser                      ( argc,argv );
//   printf(Main_Page->GCode_File_Name);
//   return 0;

   Curses    = new Curses_Color_Class (        );
   Main_Page->Init                    ( stdscr );
   for(;;)
      sleep(10);
      ;
   return 0;
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
   const char *const short_options = "hvc:o:f:";
   const struct option long_options[] = {
      { "help"        ,no_argument       ,NULL ,'h' },
      { "version"     ,no_argument       ,NULL ,'v' },
      { "file nc"     ,required_argument ,NULL ,'o' },
      { NULL          ,no_argument       ,NULL ,0   }
   };
   while ( (next_option = getopt_long(argc, argv, short_options, long_options, NULL) ) != -1 ) {
      switch ( next_option ) {
         case 'h':
              Print_Usage(stdout, 0);
              break;
         case 'v':
              printf("Pap v1.0\n");
              printf("Copyright (C) disenioconingenio\n");
              break;
         case 'f':
              Main_Page->Set_GCode_File(optarg);
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
