#ifndef SENDER
#define SENDER

#define MAX_LINES       100

class Sender_Class {
   public:
      Sender_Class ( Sheet* Parent,Dim D );
      Sheet* S;
      Sheet* Sub;
      void Rti(void);
   protected:
   private:
      std::ifstream GFile;
      std::string Lines[MAX_LINES];
      uint32_t Actual_Line=0;
      uint32_t Total_Lines=0;
      void Read_File ( void );
      void File2Win  ( void );
      struct timespec Rti_Delay= { 0, 200000000};
};

#endif

