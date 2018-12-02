#include "inc_all.h"

TresD_Class::TresD_Class ( void)
{
};

void TresD_Class::Splot (void)
{
   gnuplot_resetplot(h1) ;
   gnuplot_cmd(h1, "splot 'octave/xyz.tsv' u 1:2:3 with lines");
}
void TresD_Class::Rti(void)
{
   h1 = gnuplot_init() ;
   while(1){
      nanosleep     ( &Rti_Delay,&Rti_Delay );
      Splot();
   }
   gnuplot_close(h1);

}

