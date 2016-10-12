#include "includes.h"

int32_t num_pit_overflow=0;

void PIT_IRQHandler(void){
    PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;														//Disable PIT Timer
	PIT_TFLG0 |= PIT_TFLG_TIF_MASK;                               /* Clear Timer Interrupt Flag */
	num_pit_overflow++;
    PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;															//Enable PIT Timer
}

void time_Profiler(){
	time_Profiler_Memmove(10);
	time_Profiler_Memset(10);
	time_Profiler_Reverse(10);
}

void time_Profiler_Memmove(int32_t bytes){
	uint8_t n;
	int32_t cycle_avg=0;
	int32_t cycle=0;
	float time=0.0;
	
	uint8_t *source = (uint8_t *)malloc(sizeof(uint8_t)*bytes);
	uint8_t *destination = (uint8_t *)malloc(sizeof(uint8_t)*bytes);
	
	/* Testing my_memmove()&memmove() */
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
	
	free(source);
	free(destination);
}

void time_Profiler_Memset(int32_t bytes){
	uint8_t n;
	int32_t cycle_avg=0;
	int32_t cycle=0;
	float time=0.0;
	
	uint8_t *source = (uint8_t *)malloc(sizeof(uint8_t)*bytes);
	
	/* Testing my_memzero()&memset() */
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
	
	free(source);
}

void time_Profiler_Reverse(int32_t bytes){
	uint8_t n;
	int32_t cycle_avg=0;
	int32_t cycle=0;
	float time=0.0;
	
	uint8_t *source = (uint8_t *)malloc(sizeof(uint8_t)*bytes);
	
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
	/*
	for(n=0;n<3;n++){
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
		strrev(source, 0, bytes);
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
	Log(" ns\r\n",2);
	*/
	free(source);
}

