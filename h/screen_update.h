#ifndef SCREEN_UPDATE
#define SCREEN_UPDATE

extern pthread_mutex_t	Screen_Update_Mutex; 

extern void* 		Screen_Update_Rti 		(void* Arg1);
extern long 		Read_Screen_Rti_Delay 		(void);	
extern void 		Set_Rti_Delay 			(long Value); 
extern void 		Init_Screen_Update 		(void);
extern long 		Read_Screen_Update_Rti_Delay 	(void);	
extern void 		Set_Screen_Update_Rti_Delay	(long Value);
#endif
//----------------------------------------------------------------------------------------------------
