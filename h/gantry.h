#ifndef GANTRY
#define GANTRY

#define FADE 190
#define MAX_SCALE_INDEX 2000000

class Gantry_Class : public Sheet{
   public:
      Gantry_Class    ( Sheet* Parent,Dim D );
      void Set_Coords ( Coords_Class* C     );
      void Rti        ( void                );
      int32_t  Last_X[FADE]                  ;
      int32_t  Last_Y[FADE]                  ;
      int      Fade                          ;
      int32_t  View_Max_X                    ;
      int32_t  View_Min_X                    ;
      int32_t  View_Max_Y                    ;
      int32_t  View_Min_Y                    ;
      int32_t  View_W                        ;
      int32_t  View_H                        ;
      uint32_t  Scale_Index                  ;
      int32_t  View_X_Scale                  ;
      int32_t  View_Y_Scale                  ;
      int32_t  View_Center_X = 0             ;
      int32_t  View_Center_Y = 0             ;
      void Change_Scale  ( void                                       );
      void Change_Center ( int32_t New_Center_Y, int32_t New_Center_X );
      void Key           ( int K                                      );
      void Grid          ( int16_t G                                  );

   protected:
   private:
      Coords_Class* Coords;
      struct   timespec Rti_Delay= { 0,10000000}             ; // 5 milis
      void     Toogle_Pixel      ( int32_t Y, int32_t X        );
      void     Fade_Pixels       ( int32_t Y, int32_t X        );
      bool     Absolute_X2Gantry ( int32_t In_X,int32_t* Out_X );
      bool     Absolute_Y2Gantry ( int32_t In_Y,int32_t* Out_Y );
      void     Inc_Fade          ( uint16_t Inc                );
      void     Dec_Fade          ( uint16_t Dec                );
      void     Inc_Scale         ( void                        );
      void     Dec_Scale         ( void                        );
      void     Print_Jog_Pixel   ( void                        );
      void     Jog2Left          ( void                        );
      void     Jog2Right         ( void                        );
      void     Jog2Up            ( void                        );
      void     Jog2Down          ( void                        );
      int32_t  Pixel_X_Distance  ( void                        );
      int32_t  Pixel_Y_Distance  ( void                        );
};

#endif

