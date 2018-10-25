#ifndef COORDS
#define COORDS

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
      int32_t Max_X;
      int32_t Max_Y;
      int32_t Max_Z;
      int32_t Min_X;
      int32_t Min_Y;
      int32_t Min_Z;
      int32_t Jog_X;
      int32_t Jog_Y;
      int32_t Jog_Z;
   protected:
   private:
      void Write ( void );
      struct timespec Rti_Delay= { 0, 200000000};
};

#endif

