#ifndef HISTOGRAMS
#define HISTOGRAMS

class Histo_Class {
   public:
      Histo_Class(Sheet* Parent,Dim D,uint32_t Max_Value, uint32_t Value);
   void Set_V_Inverted_Rule_Value(uint32_t Value);
   void Rti(void);
   void Set_Coords(Coords_Class* C);

   private:
   Coords_Class* Coords;
   uint32_t Max_Value;
   uint32_t Value;
   Sheet* S;
   struct timespec Rti_Delay= { 0, 500000000}; //   5 milis
   protected:
};
//----------------------------------------------------------------------------------------------------

#endif
