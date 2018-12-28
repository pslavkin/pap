#ifndef OPENMV
#define OPENMV

class Openmv_Class : public Sheet{
   public:
      Openmv_Class(Sheet* Parent,Dim D);
      void Rti     ( void );
      void Key(int K);
   private:
      uint8_t Camera_X=OPENMV_CAMERA_MAX_X/2;
      uint8_t Camera_Y=OPENMV_CAMERA_MAX_Y/2;
      uint8_t Camera_Max_X=OPENMV_CAMERA_MAX_X;
      uint8_t Camera_Max_Y=OPENMV_CAMERA_MAX_Y;
      float Next_Move_X,Next_Move_Y;
      int8_t Diff_X,Diff_Y;
      float Rotation;
      uint8_t Id;
      uint32_t Port_Number=OPENMV_PORT;
      struct timespec Rti_Delay       = { 0, OPENMV_RTI};
      struct timespec Open_Port_Delay = { 0 ,SERIAL_OPEN_PORT_DELAY};
      void Serial_Bloked_Get_Line(char* Buf,uint8_t Size);
      uint32_t Absolute_Y2Gantry(uint8_t Y);
      uint32_t Absolute_X2Gantry(uint8_t X);
      void Print_Camera_Pixel(void);
      void Move2Center(void);
};


#endif

