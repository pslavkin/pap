#ifndef GANTRY
#define GANTRY

#include <thread>

#define FADE 100

class Gantry_Class:public Sheet {
   public:
      Gantry_Class(Sheet* Parent,uint16_t Y,uint16_t X,uint16_t Height, uint16_t Width,const char* Tittle);
      std::thread TRti;
      void Rti(void);
      void Start_Rti(void);
   protected:
   private:
      int Fade;
      uint16_t Last_X[FADE];
      uint16_t Last_Y[FADE];
      void Toogle_Pixel ( unsigned char Y, unsigned char X );
      void Fade_Pixels  ( unsigned char Times              );
};

#endif

