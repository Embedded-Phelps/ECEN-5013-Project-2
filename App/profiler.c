#include "includes.h"

int32_t num_pit_overflow=0;

void PIT_IRQHandler(void){
    PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;														//Disable PIT Timer
	PIT_TFLG0 |= PIT_TFLG_TIF_MASK;                               /* Clear Timer Interrupt Flag */
	num_pit_overflow++;
    PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;															//Enable PIT Timer
}


void time_Profiler_Memmove(int32_t bytes){

	uint8_t n;

#ifdef _BBB
	struct timeval start, finish;
	int32_t nsec=0;;
#else
	int32_t cycle_avg=0;
	int32_t cycle=0;
	float time=0.0;
#endif
	
	uint8_t *source = (uint8_t *)malloc(sizeof(uint8_t)*bytes);
	uint8_t *destination = (uint8_t *)malloc(sizeof(uint8_t)*bytes);
	
	/* Testing my_memmove()&memmove() */
#ifdef _BBB
	for(n=0;n<2;n++){
	gettimeofday(&start, NULL);
	my_memmove(source, destination, bytes);
	gettimeofday(&finish, NULL);
	nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	Log_Uint32("Number of bytes: ", 17, &bytes);
	Log("\r\n",2);
	Log_Uint32("Time of my_memmove(): ",21, &nsec);
	Log(" microsec\r\n",11);
	nsec=0;
	
	for(n=0;n<2;n++){
	gettimeofday(&start, NULL);
	memmove(source, destination, bytes);
	gettimeofday(&finish, NULL);
	nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	Log_Uint32("Time of memmove(): ",18, &nsec);
	Log(" microsec\r\n",11);
	
#else 
	for(n=0;n<3;n++){
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
		my_memmove(source, destination, bytes);
		cycle += PIT_CVAL0;
		PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
	
		cycle += (num_pit_overflow*240);
		cycle_avg += cycle;
			
		num_pit_overflow=0;
		cycle=0;
	}
	cycle_avg /= 3;
	time = cycle_avg * TIME_PER_CYCLE;
	//LOGGING
	Log_Uint32("Number of bytes: ", 17, &bytes);
	Log("\r\n",2);
	Log_Uint32("CPU cycles of my_memmove(): ",28, &cycle_avg);
	Log("\r\n",2);
	Log_float("Time of my_memmove(): ",22, &time);
	Log(" ns\r\n",5);
	cycle_avg = 0;
	time=0.0;
	
	for(n=0;n<3;n++){
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
		memmove(source, destination, bytes);
		cycle += PIT_CVAL0;
		PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
	
		cycle += (num_pit_overflow*240);
		cycle_avg += cycle;
			
		num_pit_overflow=0;
		cycle=0;
	}
	cycle_avg /= 3;
	time = cycle_avg * TIME_PER_CYCLE;
	//LOGGING
	Log_Uint32("CPU cycles of memmove(): ",25, &cycle_avg);
	Log("\r\n",2);
	Log_float("Time of memmove(): ",19, &time);
	Log(" ns\r\n",5);
#endif
	free(source);
	free(destination);
}

void time_Profiler_Memset(int32_t bytes){
	uint8_t n;
#ifdef _BBB
	struct timeval start, finish;
	int32_t nsec=0;;
#else
	int32_t cycle_avg=0;
	int32_t cycle=0;
	float time=0.0;
#endif
	
	uint8_t *source = (uint8_t *)malloc(sizeof(uint8_t)*bytes);
	
	/* Testing my_memzero()&memset() */
#ifdef _BBB
	for(n=0;n<2;n++){
	gettimeofday(&start, NULL);
	my_memzero(source, bytes);
	gettimeofday(&finish, NULL);
	nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	Log_Uint32("Number of bytes: ", 17, &bytes);
	Log("\r\n",2);
	Log_Uint32("Time of my_memzero(): ",21, &nsec);
	Log(" microsec\r\n",11);
	nsec=0;
	
	for(n=0;n<2;n++){
	gettimeofday(&start, NULL);
	memset(source, 0, bytes);
	gettimeofday(&finish, NULL);
	nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	Log_Uint32("Time of memset(): ",17, &nsec);
	Log(" microsec\r\n",11);
	
#else 
	for(n=0;n<3;n++){
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
		my_memzero(source, bytes);
		cycle += PIT_CVAL0;
		PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
	
		cycle += (num_pit_overflow*240);
		cycle_avg += cycle;
			
		num_pit_overflow=0;
		cycle=0;
	}
	cycle_avg /= 3;
	time = cycle_avg * TIME_PER_CYCLE;
	//LOGGING
	Log_Uint32("Number of bytes: ", 17, &bytes);
	Log("\r\n",2);
	Log_Uint32("CPU cycles of my_memzero(): ",28, &cycle_avg);
	Log("\r\n",2);
	Log_float("Time of my_memzero(): ",22, &time);
	Log(" ns\r\n",5);
	cycle_avg = 0;
	time=0.0;
	
	for(n=0;n<3;n++){
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
		memset(source, 0, bytes);
		cycle += PIT_CVAL0;
		PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
	
		cycle += (num_pit_overflow*240);
		cycle_avg += cycle;
			
		num_pit_overflow=0;
		cycle=0;
	}
	cycle_avg /= 3;
	time = cycle_avg * TIME_PER_CYCLE;
	//LOGGING
	Log_Uint32("CPU cycles of memset(): ",24, &cycle_avg);
	Log("\r\n",2);
	Log_float("Time of memset(): ",18, &time);
	Log(" ns\r\n",5);
#endif
	free(source);
}

void time_Profiler_Reverse(int32_t bytes){
	uint8_t n;
#ifdef _BBB
	struct timeval start, finish;
	int32_t nsec=0;;
#else
	int32_t cycle_avg=0;
	int32_t cycle=0;
	float time=0.0;
#endif
	
	uint8_t *source = (uint8_t *)malloc(sizeof(uint8_t)*bytes);
	
	/* Testing my_reverse()*/
#ifdef _BBB
	for(n=0;n<2;n++){
	gettimeofday(&start, NULL);
	my_reverse(source, bytes);
	gettimeofday(&finish, NULL);
	nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	Log_Uint32("Number of bytes: ", 17, &bytes);
	Log("\r\n",2);
	Log_Uint32("Time of my_reverse(): ",22, &nsec);
	Log(" microsec\r\n",11);
	
#else 
	/* Testing my_reverse()& reverse() */
	for(n=0;n<3;n++){
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
		my_reverse(source, bytes);
		cycle += PIT_CVAL0;
		PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
	
		cycle += (num_pit_overflow*240);
		cycle_avg += cycle;
			
		num_pit_overflow=0;
		cycle=0;
	}
	cycle_avg /= 3;
	time = cycle_avg * TIME_PER_CYCLE;
	//LOGGING
	Log_Uint32("Number of bytes: ", 17, &bytes);
	Log("\r\n",2);
	Log_Uint32("CPU cycles of my_reverse(): ",28, &cycle_avg);
	Log("\r\n",2);
	Log_float("Time of my_reverse(): ",22, &time);
	Log(" ns\r\n",5);
	cycle_avg = 0;
	time=0.0;
#endif
	free(source);
}

void time_Profiler_itoa(int32_t data){
	uint8_t n;
#ifdef _BBB
	struct timeval start, finish;
	int32_t nsec=0;;
#else
	int32_t cycle_avg=0;
	int32_t cycle=0;
	float time=0.0;
#endif
	
	uint8_t *str = (uint8_t *)malloc(sizeof(uint8_t)*20);
	
	/* Testing my_itoa()& itoa() */
#ifdef _BBB
	for(n=0;n<2;n++){
	gettimeofday(&start, NULL);
	my_itoa(source, data, 10);
	gettimeofday(&finish, NULL);
	nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	Log_Uint32("Number of bytes: ", 17, &bytes);
	Log("\r\n",2);
	Log_Uint32("Time of my_itoa(): ",18, &nsec);
	Log(" microsec\r\n",11);
	nsec=0;
	
	for(n=0;n<2;n++){
	gettimeofday(&start, NULL);
	itoa(source, data, 10);
	gettimeofday(&finish, NULL);
	nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	Log_Uint32("Time of itoa(): ",15, &nsec);
	Log(" microsec\r\n",11);
	
#else 
	for(n=0;n<3;n++){
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
		my_itoa(str, data, 10);
		cycle += PIT_CVAL0;
		PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
	
		cycle += (num_pit_overflow*240);
		cycle_avg += cycle;
			
		num_pit_overflow=0;
		cycle=0;
	}
	cycle_avg /= 3;
	time = cycle_avg * TIME_PER_CYCLE;
	//LOGGING
	Log_Uint32("CPU cycles of my_itoa(): ",25, &cycle_avg);
	Log("\r\n",2);
	Log_float("Time of my_itoa(): ",19, &time);
	Log(" ns\r\n",5);
	cycle_avg = 0;
	time=0.0;
#endif
	free(str);
}

void time_Profiler_ftoa(float data){
	uint8_t n;
#ifdef _BBB
	struct timeval start, finish;
	int32_t nsec=0;;
#else
	int32_t cycle_avg=0;
	int32_t cycle=0;
	float time=0.0;
#endif
	
	uint8_t *str = (uint8_t *)malloc(sizeof(uint8_t)*32);
	
	/* Testing my_ftoa()& sprintf() */
#ifdef _BBB
	for(n=0;n<2;n++){
	gettimeofday(&start, NULL);
	my_ftoa(source, data);
	gettimeofday(&finish, NULL);
	nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	Log_Uint32("Number of bytes: ", 17, &bytes);
	Log("\r\n",2);
	Log_Uint32("Time of my_ftoa(): ",18, &nsec);
	Log(" microsec\r\n",11);
	nsec=0;
	
	for(n=0;n<2;n++){
	gettimeofday(&start, NULL);
	sprintf(source,"%f", data);
	gettimeofday(&finish, NULL);
	nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	Log_Uint32("Time of sprintf(): ",18, &nsec);
	Log(" microsec\r\n",11);
	
#else 

	for(n=0;n<3;n++){
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
		my_ftoa(str, data);
		cycle += PIT_CVAL0;
		PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
	
		cycle += (num_pit_overflow*240);
		cycle_avg += cycle;
			
		num_pit_overflow=0;
		cycle=0;
	}
	cycle_avg /= 3;
	time = cycle_avg * TIME_PER_CYCLE;
	//LOGGING
	Log_Uint32("CPU cycles of my_ftoa(): ",25, &cycle_avg);
	Log("\r\n",2);
	Log_float("Time of my_ftoa(): ",19, &time);
	Log(" ns\r\n",5);
	cycle_avg = 0;
	time=0.0;
#endif	
	free(str);
}

void time_Profiler_atoi(int8_t * str){
	uint8_t n;
#ifdef _BBB
	struct timeval start, finish;
	int32_t nsec=0;;
#else
	int32_t cycle_avg=0;
	int32_t cycle=0;
	float time=0.0;
#endif
	
	/* Testing my_atoi()& atoi() */
#ifdef _BBB
	for(n=0;n<2;n++){
	gettimeofday(&start, NULL);
	my_atoi(str);
	gettimeofday(&finish, NULL);
	nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	Log_Uint32("Time of my_atoi(): ",18, &nsec);
	Log(" microsec\r\n",11);
	nsec=0;
	
	for(n=0;n<2;n++){
	gettimeofday(&start, NULL);
	atoi(str);
	gettimeofday(&finish, NULL);
	nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	Log_Uint32("Time of atoi(): ",15, &nsec);
	Log(" microsec\r\n",11);
	
#else 
	for(n=0;n<3;n++){
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
		my_atoi(str);
		cycle += PIT_CVAL0;
		PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
	
		cycle += (num_pit_overflow*240);
		cycle_avg += cycle;
			
		num_pit_overflow=0;
		cycle=0;
	}
	cycle_avg /= 3;
	time = cycle_avg * TIME_PER_CYCLE;
	//LOGGING
	Log_Uint32("CPU cycles of my_atoi(): ",25, &cycle_avg);
	Log("\r\n",2);
	Log_float("Time of my_atoi(): ",19, &time);
	Log(" ns\r\n",5);
	cycle_avg = 0;
	time=0.0;
#endif
}
/*
void time_Profiler_Printf(){
	uint8_t n;
	struct timeval start, finish;
	int32_t nsec=0;;


	for(n=0;n<2;n++){
	gettimeofday(&start, NULL);
	printf("20 character string!\n");
	gettimeofday(&finish, NULL);
	nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	Log_Uint32("Time of printf(str): ",21, &nsec);
	Log(" microsec\r\n",11);
	nsec=0;
	


	for(n=0;n<2;n++){
	gettimeofday(&start, NULL);
	printf("%d\n",30);
	gettimeofday(&finish, NULL);
	nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	Log_Uint32("Time of printf(%d,x): ",22, &nsec);
	Log(" microsec\r\n",11);
	nsec=0;
	
	

	for(n=0;n<2;n++){
	gettimeofday(&start, NULL);
	printf("%d %d\n",30,40);
	gettimeofday(&finish, NULL);
	nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	Log_Uint32("Time of printf(%d %d,x,y): ",27, &nsec);
	Log(" microsec\r\n",11);
	nsec=0;
	


	for(n=0;n<2;n++){
	gettimeofday(&start, NULL);
	printf("%d %d %d\n",30,40,50);
	gettimeofday(&finish, NULL);
	nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	Log_Uint32("Time of printf(%d %d %d,x,y,z): ",32, &nsec);
	Log(" microsec\r\n",11);
	nsec=0;
}
*/
void time_Profiler(){
	time_Profiler_Memmove(10);			
	time_Profiler_Memmove(100);
	time_Profiler_Memmove(500);
	time_Profiler_Memmove(1000);
	time_Profiler_Memset(10);
	time_Profiler_Memset(100);
	time_Profiler_Memset(500);
	time_Profiler_Memset(1000);
	time_Profiler_Reverse(10);
	time_Profiler_Reverse(100);
	time_Profiler_Reverse(500);
	time_Profiler_Reverse(1000);
	time_Profiler_itoa(100);
	time_Profiler_ftoa(100.123);
	time_Profiler_atoi("12345");
#ifdef _BBB
	time_Profiler_Printf();
#endif
}
