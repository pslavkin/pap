#ifndef GANTRY
#define GANTRY

#define FADE 190

class Gantry_Class {
   public:
      Gantry_Class ( Sheet* Parent,Dim D );
      Sheet* S;
      void Set_Coords(Coords_Class* C);
      void Rti(void);
   protected:
   private:
      Coords_Class* Coords;
      int Fade;
      uint16_t Last_X[FADE];
      uint16_t Last_Y[FADE];
      void Toogle_Pixel ( uint32_t Y, uint32_t X );
      void Fade_Pixels  ( uint32_t Y, uint32_t X );
      struct timespec Rti_Delay= { 0, 20000000}; //   5 milis
};

#endif

