#ifndef GANTRY
#define GANTRY

class Gantry_Class : public Sheet{
   public:
      Gantry_Class ( Sheet* Parent,Dim D );
      void Set_Coords(Coords_Class* C);
      void Rti(void);
      int32_t Path_X[MAX_PATH];
      int32_t Path_Y[MAX_PATH];
      int32_t Path_Z[MAX_PATH];
      int32_t Path_Index=1;
      int32_t  View_Max_X       ;
      int32_t  View_Min_X       ;
      int32_t  View_Max_Y       ;
      int32_t  View_Min_Y       ;
      int32_t View_W           ;
      int32_t View_H           ;
      uint32_t  Scale_Index                   ;
      int32_t View_Y_Scale;
      int32_t  View_Center_X = 0;
      int32_t  View_Center_Y = 0;
      void Change_Scale(void);
      void Change_Center(int32_t New_Center_Y, int32_t New_Center_X);
      void Key(int K);
      void Grid(int16_t G);
      uint8_t  Color4Hight       ( int32_t Z                              );
      void     Redraw_Path       ( void                                   );
      void Goto_Jog_XY(void);
      void Jog2New_XY_Zero(void);

   protected:
   private:
      Coords_Class* Coords                                               ;
      struct timespec Rti_Delay= { 0, GANTRY_RTI}                         ;
      bool  Auto_Center_Enabled=true;
      void Toogle_Auto_Center    ( void                                       );
      void Auto_Center           ( int32_t New_Center_Y, int32_t New_Center_X );
      void     Toogle_Pixel      ( int32_t Y, int32_t X                       );
      void     Draw_Path         ( int32_t Y, int32_t X        ,int32_t Z     );
      void     Clear_Path        ( void                                       );
      bool     Absolute_X2Gantry ( int32_t In_X,int32_t* Out_X                );
      bool     Absolute_Y2Gantry ( int32_t In_Y,int32_t* Out_Y                );
      void     Inc_Scale         ( void                                       );
      void     Dec_Scale         ( void                                       );
      void     Print_Jog_Pixel   ( void                                       );
      void     Jog2Left          ( void                                       );
      void     Jog2Right         ( void                                       );
      void     Jog2Up            ( void                                       );
      void     Jog2Down          ( void                                       );
      int32_t  Pixel_X_Distance  ( void                                       );
      int32_t  Pixel_Y_Distance  ( void                                       );
     void Print_Scale(void);
};

#endif

