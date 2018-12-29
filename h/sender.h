#ifndef SENDER
#define SENDER


class Sender_Class:public Sheet {
   public:
      Sender_Class ( Sheet* Parent,Dim D);
      void Rti(void);
      uint32_t Exec_Line=0;
      std::string Lines[MAX_GCODE_LINES];
      uint32_t Actual_Line=0;
      uint32_t Total_Lines=0;
      void File2Win    ( void );
      bool  Is_Running ( void );
      void Reload_File ( void );
      void Send_Next_Line(void);
      void Play(void);
   protected:
   private:
      enum Sender_State {
         STOPED=0,
         STOP,
         PLAY,
         ONE_LINE,
         RESTART,
      };
      Sender_State State      = STOP;
      Sender_State Next_State = STOP;
      char* Get_Line(int32_t Pos);
      void Key(int K);
      std::ifstream GFile;
      void Read_File   ( void );
      void Restart     ( void );
      void Pause       ( void );
      void Resume       ( void );
      void Hiz_Now     ( void );
      void Print_Queue_State_Histo(void);
      void Print_Play(void);
      void Print_Pause(void);
      void Print_Stop(void);
      struct timespec Rti_Delay= { 0, SENDER_RTI};
};

#endif

