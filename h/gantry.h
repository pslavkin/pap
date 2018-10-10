#ifndef GANTRY
#define GANTRY

#define FADE 100

class Gantry_Class {
   public:
      Gantry_Class ( Sheet* Parent,Dim D );
      Sheet* S;
      void Rti(void);
   protected:
   private:
      int Fade;
      uint16_t Last_X[FADE];
      uint16_t Last_Y[FADE];
      void Toogle_Pixel ( unsigned char Y, unsigned char X );
      void Fade_Pixels  ( unsigned char Times              );
};

#endif

