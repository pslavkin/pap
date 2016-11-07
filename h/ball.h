#ifndef BALL
#define BALL


class 	Ball:Sheet
{
	Ball();
	~Ball(void);
public:
	static Ball* 		Ball_Inst;
	static struct 		timespec 		Ball_Delay;
	static void 		Init			(void);

	pthread_t 		Pt_Ball_Rti;
	signed short int 	Vel;
	static void* 		Move			(void* Arg1);
 
	void 			Ball_Rti		(void* Arg1);
	void 			Destroy_Ball_Thread	(void);
};

#endif
