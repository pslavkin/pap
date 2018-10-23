#ifndef GANTRY
#define GANTRY

#define FADE 190
#define MAX_W 2000
#define MAX_H 2000

class Gantry_Class : public Sheet{
   public:
      Gantry_Class ( Sheet* Parent,Dim D );
 //     Sheet* S;
      void Set_Coords(Coords_Class* C);
      void Rti(void);
      int32_t Last_X[FADE];
      int32_t Last_Y[FADE];
      int Fade;
      int32_t View_Max_X = 1000;
      int32_t View_Min_X = -1000;
      int32_t View_Max_Y = 1000;
      int32_t View_Min_Y = -1000;
      uint16_t  View_Scale = 1;
      int32_t View_Center_X = 0;
      int32_t View_Center_Y = 0;
      uint32_t View_W=2000;
      uint32_t View_H=2000;
      void Change_Scale(float New_Scale);
      void Change_Center(int32_t New_Center_Y, int32_t New_Center_X);
      void Key(char K);

   protected:
   private:
      Coords_Class* Coords;
      void Toogle_Pixel ( int32_t Y, int32_t X );
      void Fade_Pixels  ( int32_t Y, int32_t X );
      struct timespec Rti_Delay= { 0, 20000000}; //   5 milis
      bool Absolute_X2Gantry(int32_t In_X,int32_t* Out_X);
      bool Absolute_Y2Gantry(int32_t In_Y,int32_t* Out_Y);
};

#endif

