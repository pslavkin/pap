#ifndef COORDS
#define COORDS

class Coords_Class : public Sheet {
   public:
      Coords_Class ( Sheet* Parent,Dim D );
//      Sheet* S;
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
      float   Acc;
      float   Dec;
      uint32_t   Plot_Lines;
      uint32_t   Plot_Limit;
      uint16_t Speed_Limit;
      void Inc_Speed_Limit(void);
      void Dec_Speed_Limit(void);
      void Send_Speed_Limit2Controller(uint16_t Limit);
      void Send_Acc_Dec2Controller(float Acc, float Dec);
      void Machine2Coords(int32_t X, int32_t Y,int32_t Z, float Speed_X, float Speed_Y, float Speed_Z);
      void Key(int K);
   protected:
   private:
      void Dec_Plot_Limit(void);
      void Inc_Plot_Limit(void);
      void Write ( void );
      struct timespec Rti_Delay= { 0, COORDS_RTI};
      void Inc_Acc(void);
      void Dec_Acc(void);
      void Inc_Dec(void);
      void Dec_Dec(void);
};

#endif

