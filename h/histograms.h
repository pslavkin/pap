#ifndef HISTOGRAMS
#define HISTOGRAMS

class Histo_Class : public Sheet {
   public:
      Histo_Class                    ( Sheet* Parent,Dim D,int32_t Max_Value,int32_t Min_Value, int32_t Value );
      void Set_V_Inverted_Rule_Value ( int32_t Value                                                          );
      void Rti                       ( void                                                                   );
      void Set_Coords                ( Coords_Class* C                                                        );
      void Change_Center    ( int32_t New_Center_Z        );
      float Pixel_Z_Distance(void);

   private:
      Coords_Class* Coords;
      int32_t  Max_Value         ;
      int32_t  Min_Value         ;
      int32_t  Value             ;
      int32_t  View_Max_Z        ;
      int32_t  View_Min_Z        ;
      int32_t  View_H            ;
      uint32_t Scale_Index     ;
      int32_t  View_Z_Scale      ;
      int32_t  View_Center_Z =  0;
      bool Auto_Center_Enabled=true;
      int32_t Absolute_Z2Histo(int32_t In_Z);
      int32_t Histo_2ZAbsolute(uint8_t Histo_Z);
      void Print_Scale(void);
      void Inc_Scale        ( void                        );
      void Dec_Scale        ( void                        );
      void Change_Scale     ( void                        );
      void Jog2Up           ( void                        );
      void Jog2Down         ( void                        );
      void Print_Jog_Pixel(void);
      void Auto_Center(int32_t New_Center_Z);
      void Toogle_Auto_Center(void);
      void Goto_Jog_Z(void);
      void Key              ( int K                       );
      void Jog2New_Z_Zero(void);
      struct timespec Rti_Delay= { 0,HISTOGRAMS_RTI }; //   5 milis
   protected:
};
//----------------------------------------------------------------------------------------------------

#endif
