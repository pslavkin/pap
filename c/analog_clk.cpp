#include <cdk/cdk.h>
#include <panel.h>
#include <pthread.h>
#include "ncurses_pthread.h"

#include "sheets.h"
#include "menu.h"

Sheet *Analog_Clk;
void Init_Analog_Clk(void)
{
 Analog_Clk=new Sheet();	
 Analog_Clk->Set_Panel_User_Pointer(Analog_Clk);
 Analog_Clk->Set_Name("Analog Clk");
 Analog_Clk->Set_Size(10,40);
 Analog_Clk->Set_Pos(0,80);
 Analog_Clk->Redraw_Box();
}
void Top_Analog_Clk(void) {Analog_Clk->Top();}

Sheet *Analog_Clk1;
void Init_Analog_Clk1(void)
{
 Analog_Clk1=new Sheet();	
 Analog_Clk1->Set_Panel_User_Pointer(Analog_Clk1);
 Analog_Clk1->Set_Name("Analog Clk1");
 Analog_Clk1->Set_Size(10,40);
 Analog_Clk1->Set_Pos(0,80);
 Analog_Clk1->Redraw_Box();
}
void Top_Analog_Clk1(void) {Analog_Clk1->Top();}
 
