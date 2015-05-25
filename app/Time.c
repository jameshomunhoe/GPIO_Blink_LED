#include "stm32f4xx_hal.h"
#include "Led.h"


uint32_t getCurrentTime(){
	static uint32_t counter = 0;
	static uint32_t currentTime = 0;

	if(counter++ >= 100){
		counter = 0;
		currentTime++;
	}
	return currentTime;
}

int delay(uint32_t delayCycle, uint32_t previousTime){

	if(((currentTime = getCurrentTime()) - previousTime) < delayCycle)
		return 0;
	else
		return 1;
}
