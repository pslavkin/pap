#ifndef FIDUCIAL
#define FIDUCIAL

class Fiducial_Class : public Sheet{
   public:
      Fiducial_Class(Sheet* Parent,Dim D);
      void Rti     ( void );
      void Key(int K);
      uint8_t Fiducial_State=0;
   private:
      struct timespec Rti_Delay= { 0, FIDUCIAL_RTI};
};

#endif

