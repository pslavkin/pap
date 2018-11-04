#ifndef COORDS
#define COORDS

#define MAX_JOG_SPEED 1000

class Coords_Class {
   public:
      Coords_Class ( Sheet* Parent,Dim D );
      Sheet* S;
      void Rti(void);
      void Update(int32_t X, int32_t Y, int32_t Z);
      void Jog2Machine(void);
      int32_t X;
      int32_t Y;
      int32_t Z;
      float   Jog_Speed;
      int32_t Max_X;
      int32_t Max_Y;
      int32_t Max_Z;
      int32_t Min_X;
      int32_t Min_Y;
      int32_t Min_Z;
      int32_t Jog_X;
      int32_t Jog_Y;
      int32_t Jog_Z;
      float   Speed_X;
      float   Speed_Y;
      float   Speed_Z;
      float   Speed;
      void Inc_Jog_Speed(void);
      void Dec_Jog_Speed(void);
   protected:
   private:
      void Write ( void );
      struct timespec Rti_Delay= { 0, 200000000};
};

#endif

