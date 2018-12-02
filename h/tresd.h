#ifndef TRESD
#define TRESD

class TresD_Class {
   public:
      TresD_Class ( void                  );
      void Rti    ( void                  );
   private:
      gnuplot_ctrl    *   h1;
      void Splot    ( void );
      struct timespec Rti_Delay= { 0, 500000000}; //   5 milis
   private:
};

#endif

