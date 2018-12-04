#ifndef SENDER
#define SENDER

#define MAX_LINES       100000

class Sender_Class:public Sheet {
   public:
      Sender_Class ( Sheet* Parent,Dim D );
      void Rti(void);
      uint32_t Exec_Line=0;
      std::string Lines[MAX_LINES];
      uint32_t Actual_Line=0;
      uint32_t Total_Lines=0;
      void File2Win  ( void );
   protected:
   private:
      enum Sender_State {
         STOP=0,
         PLAY,
         ONE_LINE,
         RESTART,
         STOP_NOW,
      };
      Sender_State State      = STOP;
      Sender_State Next_State = STOP;
      char* Get_Line(int32_t Pos);
      void Send_Next_Line(void);
      void Key(int K);
      std::ifstream GFile;
      void Read_File ( void );
      void Reload_File(void);
      void Restart(void);
      void Stop_Now(void);
      struct timespec Rti_Delay= { 0, 50000000};
};

#endif

