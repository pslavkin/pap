#include <cdk/cdk.h>
#include <ncurses.h>
#include <panel.h>
#include <ncurses_pthread.h>
#include <pthread.h>
#include "screen_update.h"
//----------------------------------------------------------------------------------------------------
pthread_t 	PT_Screen_Update_Rti;
static struct timespec 		Rti_Delay={0,10000000}; //100 milis
//----------------------------------------------------------------------------------------------------
void Init_Screen_Update(void)
{
	pthread_create 	(&PT_Screen_Update_Rti, NULL, Screen_Update_Rti, NULL);
}
void* Screen_Update_Rti(void* Arg1)
{
	while(1) {
		nanosleep(&Rti_Delay,&Rti_Delay);
			doupdate();
	}
}
void Destroy_Screen_Update(void)
{
	pthread_exit(&PT_Screen_Update_Rti);
}
//----------------------------------------------------------------------------------------------------
