#include "inc_all.h"

TresD_Class::TresD_Class ( void)
{
};

void TresD_Class::Hide_Plot_Pos2 (void)
{
   Plot_Pos2_Enable=false;
   gnuplot_close(hPos2);
}
void TresD_Class::View_Plot_Pos2 (void)
{
   if(Plot_Pos2_Enable==false) {
      hPos2           = gnuplot_init ( );
      gnuplot_cmd ( hPos2 ,"set style line 1 lt 1 lw 1 pt 1 linecolor rgb 'red'"                          );
      gnuplot_cmd ( hPos2 ,"set style line 2 lt 1 lw 1 pt 1 linecolor rgb 'green'"                         );
      gnuplot_cmd ( hPos2 ,"set style line 3 lt 1 lw 1 pt 1 linecolor rgb 'blue'"                          );
      gnuplot_cmd ( hPos2 ,"set xlabel 't [seg]'"                                   );
      gnuplot_cmd ( hPos2 ,"set ylabel 'Speed [mm/seg]'"                                   );
      Plot_Pos2_Enable = true            ;
   }
}
void TresD_Class::Plot_Pos2 (void)
{
   if(Plot_Pos2_Enable) {
      Calc_Plot_Limit();
      gnuplot_cmd ( hPos2 ,"plot\
            'octave/log.txt' every ::%d::%d u 7:1 w linespoints ls 1 title 'PosX',\
            'octave/log.txt' every ::%d::%d u 7:2 w linespoints ls 2 title 'PosY',\
            'octave/log.txt' every ::%d::%d u 7:3 w linespoints ls 3 title 'PosZ'",
            Begin,
            End,
            Begin,
            End,
            Begin,
            End
            );
   }
}
void TresD_Class::Toogle_Plot_Pos2 (void)
{
   if(Plot_Pos2_Enable) Hide_Plot_Pos2();
   else View_Plot_Pos2();
}
//-----------------------------------------------------------------------
void TresD_Class::Hide_Plot2 (void)
{
   Plot2_Enable=false;
   gnuplot_close(h2);
}
void TresD_Class::View_Plot2 (void)
{
   if(Plot2_Enable==false) {
      h2           = gnuplot_init ( );
      gnuplot_cmd ( h2 ,"set style line 1 lt 1 lw 1 pt 1 linecolor rgb 'red'"                          );
      gnuplot_cmd ( h2 ,"set style line 2 lt 1 lw 1 pt 1 linecolor rgb 'green'"                         );
      gnuplot_cmd ( h2 ,"set style line 3 lt 1 lw 1 pt 1 linecolor rgb 'blue'"                          );
      gnuplot_cmd ( h2 ,"set xlabel 't [seg]'"                                   );
      gnuplot_cmd ( h2 ,"set ylabel 'Speed [mm/seg]'"                                   );
      Plot2_Enable = true            ;
   }
}
void TresD_Class::Plot2 (void)
{
   if(Plot2_Enable) {
      Calc_Plot_Limit();
      gnuplot_cmd ( h2 ,"plot\
            'octave/log.txt' every ::%d::%d u 7:4 w linespoints ls 1 title 'SpeedX',\
            'octave/log.txt' every ::%d::%d u 7:5 w linespoints ls 2 title 'SpeedY',\
            'octave/log.txt' every ::%d::%d u 7:6 w linespoints ls 3 title 'SpeedZ'",
            Begin,
            End,
            Begin,
            End,
            Begin,
            End
            );
   }
}
void TresD_Class::Toogle_Plot2 (void)
{
   if(Plot2_Enable) Hide_Plot2();
   else View_Plot2();
}
//-----------------------------------------------------------------------
void TresD_Class::Hide_Plot3 (void)
{
   Plot3_Enable=false;
   gnuplot_close(h3);
}
void TresD_Class::View_Plot3 (void)
{
   if(Plot3_Enable==false) {
      h3           = gnuplot_init ( );
      gnuplot_cmd ( h3 ,"set style line 1 lt palette frac 0.3 lw 2 pt 1 "                          );
      gnuplot_cmd ( h3 ,"set xlabel 'X [mm]'"                                   );
      gnuplot_cmd ( h3 ,"set ylabel 'Y [mm]'"                                   );
      gnuplot_cmd ( h3 ,"set zlabel 'Z [mm]'"                                   );
      Plot3_Enable = true            ;
   }
}

void TresD_Class::Calc_Plot_Limit(void)
{
   End   = Main_Page->Coords->Plot_Lines;
   Begin = End>Main_Page->Coords->Plot_Limit?(End-Main_Page->Coords->Plot_Limit):0;
}

void TresD_Class::Plot3 (void)
{
   if(Plot3_Enable) {
      Calc_Plot_Limit();
      gnuplot_cmd ( h3 ,"splot 'octave/log.txt' every ::%d::%d u 1:2:3 with lines ls 1 title 'Recorrido'",
            Begin,
            End
            );
   }
}
void TresD_Class::Toogle_Plot3 (void)
{
   if(Plot3_Enable) Hide_Plot3();
   else View_Plot3();
}
//-----------------------------------------------------------------------
void TresD_Class::View_Last_Plot2 (void)
{
   if(Last_Plot2_Enable==false) {
      Calc_Plot_Limit();
      hLast_2           = gnuplot_init ( );
      gnuplot_cmd ( hLast_2 ,"set style line 1 lt 1 lw 1 pt 1 linecolor rgb 'red'"                          );
      gnuplot_cmd ( hLast_2 ,"set style line 2 lt 1 lw 1 pt 1 linecolor rgb 'green'"                         );
      gnuplot_cmd ( hLast_2 ,"set style line 3 lt 1 lw 1 pt 1 linecolor rgb 'blue'"                          );
      gnuplot_cmd ( hLast_2 ,"set xlabel 't [seg]'"                                   );
      gnuplot_cmd ( hLast_2 ,"set ylabel 'Speed [mm/seg]'"                                   );
      gnuplot_cmd ( hLast_2 ,"plot\
            'octave/last_log.txt' every ::%d::%d u 7:4 w linespoints ls 1 title 'SpeedX',\
            'octave/last_log.txt' every ::%d::%d u 7:5 w linespoints ls 2 title 'SpeedY',\
            'octave/last_log.txt' every ::%d::%d u 7:6 w linespoints ls 3 title 'SpeedZ'",
            Begin,
            End,
            Begin,
            End,
            Begin,
            End
            );
      Last_Plot2_Enable = true            ;
   }
}
void TresD_Class::Toogle_Last_Plot2 (void)
{
   if(Last_Plot2_Enable) Hide_Last_Plot2();
   else View_Last_Plot2();
}
void TresD_Class::Hide_Last_Plot2 (void)
{
   Last_Plot2_Enable=false;
   gnuplot_close(hLast_2);
}
//-----------------------------------------------------------------------
void TresD_Class::View_Last_Plot3 (void)
{
   if(Last_Plot3_Enable==false) {
      Calc_Plot_Limit();
      hLast_3           = gnuplot_init ( );
      gnuplot_cmd ( hLast_3 ,"set style line 1 lt palette frac 0.3 lw 2 pt 1 "                          );
      gnuplot_cmd ( hLast_3 ,"set xlabel 'X [mm]'"                                   );
      gnuplot_cmd ( hLast_3 ,"set ylabel 'Y [mm]'"                                   );
      gnuplot_cmd ( hLast_3 ,"set zlabel 'Z [mm]'"                                   );
      gnuplot_cmd ( h3 ,"splot 'octave/log.txt' every ::%d::%d u 1:2:3 with lines ls 1 title 'Recorrido'",
            Begin,
            End
            );
      Last_Plot3_Enable = true            ;
   }
}
void TresD_Class::Hide_Last_Plot3 (void)
{
   Last_Plot3_Enable=false;
   gnuplot_close(hLast_3);
}
void TresD_Class::Toogle_Last_Plot3 (void)
{
   if(Last_Plot3_Enable) Hide_Last_Plot3();
   else View_Last_Plot3();
}
//-----------------------------------------------------------------------
void TresD_Class::Rti(void)
{
   while(1){
      nanosleep     ( &Rti_Delay,&Rti_Delay );
      Plot2     ( );
      Plot3     ( );
      Plot_Pos2 ( );
   }
   gnuplot_close ( hPos2   );
   gnuplot_close ( h2      );
   gnuplot_close ( h3      );
   gnuplot_close ( hLast_2 );
   gnuplot_close ( hLast_3 );
}

