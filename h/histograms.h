#ifndef HISTOGRAMS
#define HISTOGRAMS

class Histo_Class:public Sheet {
   public:
      Histo_Class(uint16_t Y,uint16_t X,uint16_t Height, uint16_t Width,char* Tittle,
                  uint32_t Max_Value, uint32_t Value);
   void Set_V_Inverted_Rule_Value(uint16_t Value);

   private:
   uint16_t Y;
   uint16_t X;
   uint16_t Height;
   uint32_t Max_Value;
   uint32_t Value;
   protected:
};
//----------------------------------------------------------------------------------------------------

#endif
