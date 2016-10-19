#include <cdk/cdk.h>
#include <ncurses.h>
#include <panel.h>
#include <ncurses_pthread.h>
#include <pthread.h>
#include "screen_update.h"
//----------------------------------------------------------------------------------------------------
pthread_t 	PT_Screen_Update_Rti;
pthread_mutex_t	Screen_Update_Mutex = PTHREAD_MUTEX_INITIALIZER;
static struct timespec 		Rti_Delay={1,0}; //100 milis
//----------------------------------------------------------------------------------------------------
long Read_Screen_Update_Rti_Delay 	(void) 		{return Rti_Delay.tv_nsec;}
void Set_Screen_Update_Rti_Delay	(long Value) 	{Rti_Delay.tv_nsec=Value;}

void Init_Screen_Update(void)
{
	pthread_mutex_unlock(&Screen_Update_Mutex); 
	pthread_create 	(&PT_Screen_Update_Rti, NULL, Screen_Update_Rti, NULL);
}
void* Screen_Update_Rti(void* Arg1)
{
	while(1) {
		nanosleep(&Rti_Delay,&Rti_Delay);
		if(pthread_mutex_trylock(&Screen_Update_Mutex)==0) 	{
			update_panels();
			doupdate();
		pthread_mutex_unlock(&Screen_Update_Mutex);
		}
	}
}
void Destroy_Screen_Update(void)
{
	pthread_exit(&PT_Screen_Update_Rti);
}
//----------------------------------------------------------------------------------------------------
