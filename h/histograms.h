#ifndef HISTOGRAMS
#define HISTOGRAMS

class Histo_Class : public Sheet {
   public:
      Histo_Class                    ( Sheet* Parent,Dim D,int32_t Max_Value,int32_t Min_Value, int32_t Value );
      void Set_V_Inverted_Rule_Value ( int32_t Value                                                          );
      void Rti                       ( void                                                                   );
      void Set_Coords                ( Coords_Class* C                                                        );
//      Sheet* S;

   private:
      Coords_Class* Coords;
      int32_t Max_Value;
      int32_t Min_Value;
      int32_t Value;
      struct timespec Rti_Delay= { 0,HISTOGRAMS_RTI }; //   5 milis
      void Key(int K);
   protected:
};
//----------------------------------------------------------------------------------------------------

#endif
