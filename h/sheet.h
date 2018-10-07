#ifndef SHEET
#define SHEET

#include <panel.h>


#define MIN_WIDTH  4
#define MIN_HEIGHT 4

//---------------------------------------------------------------------------------------------------
class Sheet{
   public:
   static Sheet* Sheet4Top_Panel(void);
   static Sheet* Sheet4Panel(PANEL* Panel);
protected:
public:
   Sheet                ( WINDOW *Ext_Win ); //con arfs
   Sheet(uint16_t X, uint16_t Y, uint16_t Height, uint16_t Width,const char* Tittle);
   Sheet                (                 ); //sin args
   WINDOW*                    Win;
   PANEL*                     Panel;
   char                       Name    [ 100 ];

   void                 Redraw_Box             ( void                                               );
   void                 Hide_Box               ( void                                               );
   void                 Set_Name               ( const char* Sheet_Name                                   );
   void                 Set_Size               ( unsigned short int Height,unsigned short int Width );
   unsigned short int   Get_Height             ( void                                               );
   unsigned short int   Get_Width              ( void                                               );
   void                 Set_Pos                ( unsigned short int Y,unsigned short int X          );
   char                 To_Up                  ( void                                               );
   char                 To_Down                ( void                                               );
   char                 To_Right               ( void                                               );
   char                 To_Left                ( void                                               );
   void                 Inc_Width              ( void                                               );
   void                 Dec_Width              ( void                                               );
   void                 Inc_Height             ( void                                               );
   void                 Dec_Height             ( void                                               );
   void                 Full_Screen            ( void                                               );
   void                 Hide                   ( void                                               );
   void                 Unhide                 ( void                                               );
   void                 Top                    ( void                                               );
   void                 Bottom                 ( void                                               );
   void                 Select                 ( void                                               );
   void                 Deselect               ( void                                               );
   void Set_Panel_User_Pointer();
   void                 Set_Panel_User_Pointer ( Sheet* Ptr                                         );
   void                 Touch_Win              ( void                                               );
   unsigned short int   Max_Y                  ( void                                               );
   unsigned short int   Max_X                  ( void                                               );
   unsigned short int   Beg_Y                  ( void                                               );
   unsigned short int   Beg_X                  ( void                                               );
   ~Sheet                                      ( void                                               );
private:
   void     Move_Panel        (PANEL* Panel,unsigned short int Y,unsigned short int X);
};

#endif
