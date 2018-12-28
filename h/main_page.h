#ifndef MAIN_PAGE_CLASS
#define MAIN_PAGE_CLASS

class Main_Page_Class {
   public:
      pthread_mutex_t Print_Mutex;
      pthread_mutex_t Serial_Mutex;
      Main_Page_Class(void);
      void Init (WINDOW* W);
      char GCode_File_Name[200];
      void Set_GCode_File(char* F);
      Sheet*                Main         ;
      Gantry_Class*         Gantry_XY    ;
      Histo_Class*          Histo_Z      ;
      Serial_Manager_Class* Serial       ;
      Coords_Class*         Coords       ;
      Sender_Class*         Sender       ;
      Screen_Update_Class*  Screen_Update;
      TresD_Class*          TresD        ;
      Openmv_Class*         Openmv       ;
      Timer_Class T;
   protected:
   private:
};

#endif

