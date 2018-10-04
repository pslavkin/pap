#ifndef HISTOGRAMS
#define HISTOGRAMS

struct Struct_Histo {
   unsigned short int   X;
   unsigned short int   Y;
   unsigned short int   Width;
   unsigned int         Value;
   unsigned int         Max_Value;
            char        Tittle[100];
   WINDOW*              Win;
   };
void Init_Histogram(struct Struct_Histo *Histo,WINDOW *Win,unsigned short int Y,unsigned short int X,const char* Tittle, \
          unsigned int Max_Value, unsigned int Value,unsigned short int Width);
extern void    Set_Histogram_Value     ( struct Struct_Histo *Histo, unsigned int Value                      );
extern void    Set_Rule_Value          ( struct Struct_Histo *Histo, unsigned int Value                      );
extern void    Set_V_Histogram_Value   ( struct Struct_Histo *Histo, unsigned int Value                      );
extern void    Set_V_Rule_Value        ( struct Struct_Histo *Histo, unsigned int Value                      );
extern void    Set_V_Double_Rule_Value ( struct Struct_Histo *Histo, unsigned int ValueA,unsigned int ValueB );
extern void    Set_V_Y_Scale           ( struct Struct_Histo *Histo                                          );
extern void    Init_Histograms         ( void                                                                );
extern void*   Histogram_Rti           ( void* Arg1                                                          );
extern void    Destroy_Histograms      ( void                                                                );
//----------------------------------------------------------------------------------------------------

#endif
