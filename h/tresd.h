#ifndef TRESD
#define TRESD

class TresD_Class {
   public:
      TresD_Class            ( void );
      void Rti               ( void );
      void Toogle_Plot_Pos2  ( void );
      void Toogle_Plot2      ( void );
      void Toogle_Plot3      ( void );
      void Toogle_Last_Plot2 ( void );
      void Toogle_Last_Plot3 ( void );
   private:
      void Calc_Plot_Limit(void);
      uint32_t Begin,End;
      gnuplot_ctrl    *hPos2;
      gnuplot_ctrl    *h2      ,*h3     ;
      gnuplot_ctrl    *hLast_2 ,*hLast_3;
      bool Plot_Pos2_Enable  = false;
      bool Plot2_Enable      = false;
      bool Plot3_Enable      = false;
      bool Last_Plot2_Enable = false;
      bool Last_Plot3_Enable = false;
      void Plot_Pos2       ( void ) ;
      void Plot2           ( void ) ;
      void Plot3           ( void ) ;
      void Hide_Plot_Pos2  ( void ) ;
      void View_Plot_Pos2  ( void ) ;
      void Hide_Plot2      ( void ) ;
      void View_Plot2      ( void ) ;
      void Hide_Plot3      ( void ) ;
      void View_Plot3      ( void ) ;
      void View_Last_Plot2 ( void ) ;
      void Hide_Last_Plot2 ( void ) ;
      void View_Last_Plot3 ( void ) ;
      void Hide_Last_Plot3 ( void ) ;
      struct timespec Rti_Delay= { 0, TRESD_RTI}; //   5 milis
   private:
};


#endif

