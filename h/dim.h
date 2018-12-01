#ifndef DIM
#define DIM

//---------------------------------------------------------------------------------------------------
class Dim
{
   public:
      Dim(uint16_t Y, uint16_t X, uint16_t H, uint16_t W, const char* N);
      Dim();
      uint16_t Y,X,H,W     ;
      char     Name [ 100 ];
   private:
};

#endif
