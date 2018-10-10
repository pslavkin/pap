#ifndef HISTOGRAMS
#define HISTOGRAMS

class Histo_Class {
   public:
      Histo_Class(Sheet* Parent,Dim D,uint32_t Max_Value, uint32_t Value);
   void Set_V_Inverted_Rule_Value(uint16_t Value);
   void Rti(void);

   private:
   uint32_t Max_Value;
   uint32_t Value;
   protected:
   Sheet* S;
};
//----------------------------------------------------------------------------------------------------

#endif
