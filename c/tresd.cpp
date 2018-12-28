#include "inc_all.h"

TresD_Class::TresD_Class ( void)
{
   Gcode2Matrix();
};

void TresD_Class::Calc_Plot_Limit(void)
{
   End            = Main_Page->Coords->Plot_Lines;
   Begin          = End>Main_Page->Coords->Plot_Limit?(End-Main_Page->Coords->Plot_Limit):0;
   Original_Begin = Main_Page->Sender->Exec_Line-2;
   Original_End   = Main_Page->Sender->Exec_Line+Main_Page->Coords->Plot_Limit;
}


void TresD_Class::Hide_Plot_Pos (void)
{
   Plot_Pos_Enable=false;
   gnuplot_close(hPos);
}
void TresD_Class::View_Plot_Pos (void)
{
   if(Plot_Pos_Enable==false) {
      hPos           = gnuplot_init ( );
      gnuplot_cmd ( hPos ,"set style line 1 lt 1 lw 1 pt 1 linecolor rgb 'red'"                          );
      gnuplot_cmd ( hPos ,"set style line 2 lt 1 lw 1 pt 1 linecolor rgb 'green'"                         );
      gnuplot_cmd ( hPos ,"set style line 3 lt 1 lw 1 pt 1 linecolor rgb 'blue'"                          );
      gnuplot_cmd ( hPos ,"set xlabel 't [seg]'"                                   );
      gnuplot_cmd ( hPos ,"set ylabel 'Speed [mm/seg]'"                                   );
      Plot_Pos_Enable = true            ;
   }
}
void TresD_Class::Plot_Pos (void)
{
   if(Plot_Pos_Enable) {
      Calc_Plot_Limit();
      gnuplot_cmd ( hPos ,"plot\
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
void TresD_Class::Toogle_Plot_Pos (void)
{
   if(Plot_Pos_Enable) Hide_Plot_Pos();
   else View_Plot_Pos();
}
//-----------------------------------------------------------------------
void TresD_Class::Hide_Plot_Speed (void)
{
   Plot_Speed_Enable=false;
   gnuplot_close(hSpeed);
}
void TresD_Class::View_Plot_Speed (void)
{
   if(Plot_Speed_Enable==false) {
      hSpeed           = gnuplot_init ( );
      gnuplot_cmd ( hSpeed ,"set style line 1 lt 1 lw 1 pt 1 linecolor rgb 'red'"   );
      gnuplot_cmd ( hSpeed ,"set style line 2 lt 1 lw 1 pt 1 linecolor rgb 'green'" );
      gnuplot_cmd ( hSpeed ,"set style line 3 lt 1 lw 1 pt 1 linecolor rgb 'blue'"  );
      gnuplot_cmd ( hSpeed ,"set xlabel 't [seg]'"                                  );
      gnuplot_cmd ( hSpeed ,"set ylabel 'Speed [mm/seg]'"                           );
      Plot_Speed_Enable = true                                                       ;
   }
}
void TresD_Class::Plot_Speed (void)
{
   if(Plot_Speed_Enable) {
      Calc_Plot_Limit();
      gnuplot_cmd ( hSpeed ,"plot\
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
void TresD_Class::Toogle_Plot_Speed (void)
{
   if(Plot_Speed_Enable) Hide_Plot_Speed();
   else View_Plot_Speed();
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
      gnuplot_cmd ( h3 ,"set style line 1 lt palette frac 0.3 lw 4 pt 1 "     );
      gnuplot_cmd ( h3 ,"set style line 2 lt 2 lw 1 pt 1 linecolor rgb 'green'" );
      gnuplot_cmd ( h3 ,"set style line 3 lt 2 lw 1 pt 1 linecolor rgb 'blue'" );
      gnuplot_cmd ( h3 ,"set style line 4 lt 2 lw 2 pt 11 linecolor rgb 'black'" );
      gnuplot_cmd ( h3 ,"set xlabel 'X [mm]'"                                 );
      gnuplot_cmd ( h3 ,"set ylabel 'Y [mm]'"                                 );
      gnuplot_cmd ( h3 ,"set zlabel 'Z [mm]'"                                 );
      Plot3_Enable = true                                                      ;
   }
}

void TresD_Class::Plot3 (void)
{
   if(Plot3_Enable) {
      Calc_Plot_Limit();
      gnuplot_cmd ( h3 ,"splot 'octave/log.txt'             every ::%d::%d u 1:2:3 with lines ls 1 title 'Path',\
                               'gcodes/matrix.txt'          every ::%d::%d u 1:2:3 with lines ls 2 title 'Original',\
                               'gcodes/matrix_modified.txt' every ::%d::%d u 1:2:3 with lines ls 3 title 'Modified',\
                               'octave/log.txt'             every ::%d::%d u 1:2:3 with points ls 4 title 'dwell'",
            Begin,
            End,
            Original_Begin,
            Original_End,
            Original_Begin,
            Original_End,
            End-1,
            End-1);
   }
}
void TresD_Class::Toogle_Plot3 (void)
{
   if(Plot3_Enable) Hide_Plot3();
   else View_Plot3();
}
//-----------------------------------------------------------------------
void TresD_Class::Hide_Plot_Gcode (void)
{
   Plot_Gcode_Enable=false;
   gnuplot_close(hGcode);
}
void TresD_Class::View_Plot_Gcode (void)
{
   if(Plot_Gcode_Enable==false) {
      hGcode           = gnuplot_init ( );
      gnuplot_cmd ( hGcode ,"set style line 1 lt palette frac 0.3 lw 0.5 pt 1 "                          );
      gnuplot_cmd ( hGcode ,"set xlabel 'X [mm]'"                                   );
      gnuplot_cmd ( hGcode ,"set ylabel 'Y [mm]'"                                   );
      gnuplot_cmd ( hGcode ,"set zlabel 'Z [mm]'"                                   );
      Plot_Gcode_Enable = true            ;
   }
}
void TresD_Class::Plot_Gcode (void)
{
   if(Plot_Gcode_Enable) {
      gnuplot_cmd ( hGcode ,"splot 'gcodes/matrix.txt' every ::%d::%d u 1:2:3 with lines ls 1 title 'Original'",
            1,
            Total_Lines
            );
   }
}
void TresD_Class::Toogle_Plot_Gcode (void)
{
   if(Plot_Gcode_Enable) Hide_Plot_Gcode();
   else View_Plot_Gcode();
}
//-----------------------------------------------------------------------
void TresD_Class::Rti(void)
{
   while(1){
      nanosleep     ( &Rti_Delay,&Rti_Delay );
      Plot_Pos   ( );
      Plot_Speed ( );
      Plot3      ( );
      Plot_Gcode ( );
   }
   gnuplot_close ( hPos  );
   gnuplot_close ( hSpeed );
   gnuplot_close ( h3     );
   gnuplot_close ( hGcode );
}

void TresD_Class::Translate(Trilogy Trans)
{
   uint32_t i;
   GMatrix_File.open("gcodes/matrix_modified.txt");
   if(!GMatrix_File.good())
      exit(1);
   for(i=0;i<Total_Lines;i++) {
      Xyz[i].X+=Trans.X;
      Xyz[i].Y+=Trans.Y;
      Xyz[i].Z+=Trans.Z;
      GMatrix_File << Xyz[i].X << ' ' << Xyz[i].Y << ' ' << Xyz[i].Z << std::endl;
   }
   GMatrix_File.close();
}
void TresD_Class::Rotate(float Angle)
{
   uint32_t i;
   float X,Y;
   GMatrix_File.open("gcodes/matrix_modified.txt");
   if(!GMatrix_File.good())
      exit(1);
   for(i=0;i<Total_Lines;i++) {
      X=Xyz[i].X*cos(Angle) - Xyz[i].Y*sin(Angle);
      Y=Xyz[i].X*sin(Angle) + Xyz[i].Y*cos(Angle);
      Xyz[i].X=X;
      Xyz[i].Y=Y;
      GMatrix_File << Xyz[i].X << ' ' << Xyz[i].Y << ' ' << Xyz[i].Z << std::endl;
   }
   GMatrix_File.close();
}
//------------------------------------------------------------
void TresD_Class::Decode_File(void)
{
   size_t Pos;
   uint32_t i;
   std::string Line;
   GMatrix_File.open("gcodes/matrix.txt");
   if(!GMatrix_File.good())
      exit(1);

   for(i=0;i<Main_Page->Sender->Total_Lines;i++) {
      Line=Main_Page->Sender->Lines[i];
      Pos=Line.find('X');
      if(Pos<std::string::npos) sscanf(Line.c_str()+Pos,"X%f", &Xyz[i].X);
      Pos=Line.find('Y');
      if(Pos<std::string::npos) sscanf(Line.c_str()+Pos,"Y%f", &Xyz[i].Y);
      Pos=Line.find('Z');
      if(Pos<std::string::npos) sscanf(Line.c_str()+Pos,"Z%f", &Xyz[i].Z);
      GMatrix_File << Xyz[i].X << ' ' << Xyz[i].Y << ' ' << Xyz[i].Z << std::endl;
      Xyz[i+1]=Xyz[i];
   }
   GMatrix_File.close ( );
   Total_Lines=i;
   Actual_Line=0;
}
void TresD_Class::Gcode2Matrix(void)
{
   Decode_File        ( );
   GMatrix_File.open("gcodes/matrix_modified.txt");
   GMatrix_File.close();
}
//-------------------------------------------
bool TresD_Class::Is_Coord_Line(std::string Line)
{
   size_t X,Y,Z;
   X=Line.find('X');
   Y=Line.find('Y');
   Z=Line.find('Z');
   if(X<std::string::npos || Y<std::string::npos || Z<std::string::npos)
      return true;
   else
      return false;
}

std::string TresD_Class::Replace_Coord(char C,float New_Coord,std::string Line)
{
   size_t Pos,Space;
   std::string New_Line=Line;
   Pos=Line.find(C);
   if(Pos<std::string::npos) {
      New_Line=Line.substr(0,Pos+1) + std::to_string(New_Coord);
      Space=Line.find(' ',Pos);
      if(Space<std::string::npos)
         New_Line+=Line.substr(Space);
   }
   else  {
      New_Line+= " ";
      New_Line+= C;
      New_Line+= std::to_string(New_Coord);
   }
   return New_Line;
}
void TresD_Class::Encode_File(void)
{
   uint32_t i;
   std::string Line;

   for(i=0;i<Main_Page->Sender->Total_Lines;i++) {
      Line=Main_Page->Sender->Lines[i];
      if (Line[Line.size()-1] == '\r')
         Line.resize(Line.size()-1);
      if(Is_Coord_Line(Line)==true) {
         Line=Replace_Coord('X',Xyz[i].X,Line);
         Line=Replace_Coord('Y',Xyz[i].Y,Line);
         Line=Replace_Coord('Z',Xyz[i].Z,Line);
      }
      Main_Page->Sender->Lines[i]= Line + "\n";
   }
}
void TresD_Class::Matrix2GCode(void)
{
   Encode_File  ( );
   Gcode2Matrix ( );
}


void TresD_Class::Set_Fiducial(uint8_t F)
{
   switch(F) {
      case 1:
         Main_Page->Gantry_XY->Jog2New_XY_Zero();
         Trans.X=0-Xyz[0].X;
         Trans.Y=0-Xyz[0].Y;
         Trans.Z=0;//Main_Page->Coords->Actual_Jog_Z-Xyz[0].Z;
         Translate(Trans);
         Matrix2GCode();
         break;
      case 2:
         Delta_Original.X = Xyz[1].X-Xyz[0].X;
         Delta_Original.Y = Xyz[1].Y-Xyz[0].Y;
         Delta_New.X      = Main_Page->Coords->Actual_X-Xyz[0].X;
         Delta_New.Y      = Main_Page->Coords->Actual_Y-Xyz[0].Y;

         Angle_Original   = atan(Delta_Original.Y/Delta_Original.X);
         Angle_New        = atan(Delta_New.Y/Delta_New.X);
         Angle_Diff       = Angle_New-Angle_Original;
         Rotate(Angle_Diff);
         break;
      case 8:
         Gcode2Matrix();
         break;
   }
}




