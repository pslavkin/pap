#ifndef rs232_INCLUDED
#define rs232_INCLUDED

#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>

int   setRTS       ( int comport_number, int level );
int   setDTR       ( int comport_number, int level );
int   OpenComport  ( int, int                      );
int   PollComport  ( int, unsigned char *, int     );
int   SendByte     ( int, unsigned char            );
int   SendBuf      ( int, char *, int     );
void  CloseComport ( int                           );
void  cprintf      ( int, const char *             );
int   IsCTSEnabled ( int                           );

#endif


