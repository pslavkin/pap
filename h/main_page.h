#ifndef MAIN_PAGE_CLASS
#define MAIN_PAGE_CLASS

class Main_Page_Class {
   public:
      pthread_mutex_t Print_Mutex;
      Main_Page_Class(WINDOW* w);
      Sheet*                Main         ;
      Gantry_Class*         Gantry_XY    ;
      Histo_Class*          Histo_Z      ;
      Serial_Manager_Class* Serial       ;
      Coords_Class*         Coords       ;
      Parser_Class*         Parser       ;
      Screen_Update_Class*  Screen_Update;
      TresD_Class*          TresD        ;
      Timer_Class T;
   protected:
   private:
};

#endif

