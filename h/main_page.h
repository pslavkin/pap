#ifndef MAIN_PAGE_CLASS
#define MAIN_PAGE_CLASS

class Main_Page_Class {
   public:
      Main_Page_Class(WINDOW* w);
   protected:
   private:
         Sheet*                Main         ;
         Gantry_Class*         Gantry_XY    ;
         Histo_Class*          Histo_Z      ;
         Serial_Manager_Class* Serial       ;
         Coords_Class*         Coords       ;
         Screen_Update_Class*  Screen_Update;
         Timer_Class T;
};

#endif

