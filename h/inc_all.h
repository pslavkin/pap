#include "opt.h"

#include <panel.h>
#include <ncurses.h>
#include <unistd.h>
//#include <GL/gl.h>
//#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <termios.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <chrono>

#include "gnuplot_i.h"

#include "tresd.h"
#include "dim.h"
#include "sheet.h"
#include "coords.h"
#include "gantry.h"
#include "rs232.h"
#include "serialmanager.h"
#include "histograms.h"
#include "screen_update.h"
#include "curses_color.h"
#include "fiducial.h"
#include "openmv.h"
#include "sender.h"
#include "timer.h"
#include "main_page.h"
#include "main.h"




