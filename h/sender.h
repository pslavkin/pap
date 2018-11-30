#ifndef SENDER
#define SENDER

#define MAX_LINES       10000

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
      void Key(int K);
      std::ifstream GFile;
      void Read_File ( void );
      struct timespec Rti_Delay= { 0, 900000000};
};

#endif

