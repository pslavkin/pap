#ifndef COORDS
#define COORDS

class Coords_Class {
   public:
      Coords_Class ( Sheet* Parent,Dim D );
      Sheet* S;
      void Rti(void);
      void Update(uint32_t X, uint32_t Y, uint32_t Z);
      uint32_t X;
      uint32_t Y;
      uint32_t Z;
      uint32_t Max_X;
      uint32_t Max_Y;
      uint32_t Max_Z;
      uint32_t Min_X;
      uint32_t Min_Y;
      uint32_t Min_Z;
   protected:
   private:
      void Write ( void );
      struct timespec Rti_Delay= { 0, 20000000};
};

#endif

