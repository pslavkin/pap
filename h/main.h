#ifndef PAP
#define PAP

void    Print_Usage ( FILE *stream, int exit_code );
void    Params_Parser  (int argc, char **argv);
extern Curses_Color_Class*  Curses;
extern Main_Page_Class*     Main_Page;

#endif
