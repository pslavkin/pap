#ifndef SHEET
#define SHEET


#define MIN_WIDTH  4
#define MIN_HEIGHT 4

//---------------------------------------------------------------------------------------------------
class Sheet{
   public:
      static  Sheet* Sheet4Top_Panel ( void         );
      static  Sheet* Sheet4Panel     ( PANEL* Panel );
protected:
public:
   Sheet ( WINDOW* W     ,Dim D           );
   Sheet ( Sheet* Parent ,Dim D           );
   Sheet ( Sheet* Parent ,Dim D ,bool Box );
   WINDOW*                    Win;
   WINDOW*                    Sub_Win;
   Sheet*                     Parent_Sheet;
   PANEL*                     Panel;
   char                       Name    [ 100 ];
   Dim Dims;
   Dim Restore_Dims;

   void                 Set_Parent_Sheet       ( Sheet* P                                           );
   void                 Redraw_Box             ( bool Selected                                      );
   void                 Hide_Box               ( void                                               );
   void                 Set_Name               ( const char* Sheet_Name                             );
   void                 Set_Size               ( unsigned short int Height,unsigned short int Width );
   unsigned short int   Get_Height             ( void                                               );
   unsigned short int   Get_Width              ( void                                               );
   void                 Set_Pos                ( unsigned short int Y,unsigned short int X          );
   void                 To_Up                  ( void                                               );
   void                 To_Down                ( void                                               );
   void                 To_Right               ( void                                               );
   void                 To_Left                ( void                                               );
   void                 Inc_Width              ( void                                               );
   void                 Dec_Width              ( void                                               );
   void                 Inc_Height             ( void                                               );
   void                 Dec_Height             ( void                                               );
   void                 Full_Screen            ( void                                               );
   void                 Restore_Screen(void);
   void                 Hide                   ( void                                               );
   void                 Unhide                 ( void                                               );
   void                 Top                    ( void                                               );
   void                 Bottom                 ( void                                               );
   void  Toogle_Select                         ( void                                               );
   void                 Select                 ( void                                               );
   void                 Deselect               ( void                                               );
   void                 Set_Panel_User_Pointer (                                                    );
   void                 Set_Panel_User_Pointer ( Sheet* Ptr                                         );
   void                 Touch_Win              ( void                                               );
   unsigned short int   Max_Y                  ( void                                               );
   unsigned short int   Max_X                  ( void                                               );
   unsigned short int   Beg_Y                  ( void                                               );
   unsigned short int   Beg_X                  ( void                                               );
   ~Sheet                                      ( void                                               );
   virtual void Key ( int K );
   bool Selected=0;
private:
   void     Move_Panel        (PANEL* Panel,unsigned short int Y,unsigned short int X);
   void Normalize_W(void);
   void Normalize_H(void);
   void Normalize_X(void);
   void Normalize_Y(void);
};

#endif
