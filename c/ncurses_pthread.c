#include <ncurses.h>
#include <pthread.h>
#include <panel.h>
#include <ncurses_pthread.h>
#include <screen_update.h>
#include <sheets.h>
#include <time.h>

void Init_Ncurses_Pthread(void)
{
}
void Rien(void)
{
}
unsigned short int Get_Actual_Time(void)
{
	timespec Time;
 	clock_gettime(CLOCK_MONOTONIC_RAW,&Time);
	return (Time.tv_sec*10)+(Time.tv_nsec/100000000);
//	return (Time.tv_sec&0x0FFF)<<4 | (Time.tv_nsec/100000000)&0x000F;
}


