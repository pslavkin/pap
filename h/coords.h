#ifndef COORDS
#define COORDS

#define MAX_JOG_SPEED 1000
#define X_SCALE       600  // micropasos por mm
#define Y_SCALE       600  // micropasos por mm
#define Z_SCALE       2560 // micropasos por mm
#define MICROSTEP     128

class Coords_Class {
   public:
      Coords_Class ( Sheet* Parent,Dim D );
      Sheet* S;
      void Rti(void);
      void Jog2Machine(void);
      int32_t X;
      int32_t Y;
      int32_t Z;
      float   Actual_X;
      float   Actual_Y;
      float   Actual_Z;
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
      float   Actual_Jog_X;
      float   Actual_Jog_Y;
      float   Actual_Jog_Z;
      float   Speed_X;
      float   Speed_Y;
      float   Speed_Z;
      float   Actual_Speed_X;
      float   Actual_Speed_Y;
      float   Actual_Speed_Z;
      float   Actual_Speed;
      float   Speed;
      void Inc_Jog_Speed(void);
      void Dec_Jog_Speed(void);
      void Machine2Coords(int32_t X, int32_t Y,int32_t Z, float Speed_X, float Speed_Y, float Speed_Z);
   protected:
   private:
      void Write ( void );
      struct timespec Rti_Delay= { 0, 50000000};
};

#endif

