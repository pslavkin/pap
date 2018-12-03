#ifndef CURSES_COLOR
#define CURSES_COLOR

class Curses_Color_Class {
   public:
      Curses_Color_Class ( );
      void Init_Curses          ( void                                                      );
      void init_Basic_Colors    ( void                                                      );
      void Init_Gradient_Colors ( uint8_t R,uint8_t G,uint8_t B,uint8_t From, uint8_t Count );
      void Init_Full_Colors (void);
   protected:
   private:
};

#endif

