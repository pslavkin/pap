#ifndef TRESD
#define TRESD

class TresD_Class {
   public:
      TresD_Class            ( void );
      void Rti               ( void );
      void Toogle_Plot_Pos   ( void );
      void Toogle_Plot_Speed ( void );
      void Toogle_Plot3      ( void );
      void Toogle_Plot_Gcode ( void );
      void Gcode2Matrix ( void );
      void Matrix2GCode ( void );
      void Translate    ( void );
      void Rotate       ( void );
   private:
      void Calc_Plot_Limit(void);
      uint32_t Begin,End;
      gnuplot_ctrl    *hSpeed;
      gnuplot_ctrl    *hPos;
      gnuplot_ctrl    *h3;
      gnuplot_ctrl    *hGcode;
      bool Plot_Pos_Enable   = false;
      bool Plot_Speed_Enable = false;
      bool Plot3_Enable      = false;
      bool Plot_Gcode_Enable = false;
      void Plot_Pos        ( void );
      void Plot_Speed      ( void );
      void Plot3           ( void );
      void Plot_Gcode      ( void );
      void Hide_Plot_Pos   ( void );
      void View_Plot_Pos   ( void );
      void Hide_Plot_Speed ( void );
      void View_Plot_Speed ( void );
      void Hide_Plot3      ( void );
      void View_Plot3      ( void );
      void Hide_Plot_Gcode ( void );
      void View_Plot_Gcode ( void );
      struct timespec Rti_Delay= { 0, TRESD_RTI}; //   5 milis
      std::ifstream GFile;
      std::ofstream GMatrix_File;
      uint32_t Actual_Line=0;
      uint32_t Total_Lines=0;
      void Decode_File  ( void );
      void Encode_File  ( void );
      struct Trilogy {
         float X,Y,Z;
      };
      Trilogy Xyz[MAX_GCODE_LINES];
      Trilogy Trans;
      float Angle;
      std::string Replace_Coord(char C,float New_Coord,std::string Line);
      bool Is_Coord_Line(std::string Line);
};


#endif

