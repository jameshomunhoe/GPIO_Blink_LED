#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

#define turnOnLED1() HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
#define turnOffLED1() HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
#define turnOnLED2() HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);
#define turnOffLED2() HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
#define turnOnLED3() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
#define turnOffLED3() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
#define turnOnLED4() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
#define turnOffLED4() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);

#define pushButton() HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)

int delay120ms = 120;
int delay500ms = 500;
extern uint32_t currentTime;

typedef enum{
	INITIAL,
	LEDOFF,
	LEDON
}State;


void SD(){
	static State state = INITIAL;
	static uint32_t previousTime = 0;
	switch(state){

	case INITIAL:
		turnOffLED1();
		if(delay(delay120ms, previousTime)){
			state = LEDON;
			previousTime = currentTime;
		}
		break;

	case LEDON:
		turnOnLED1();
		if(delay(delay120ms, previousTime)){
			state = LEDOFF;
			previousTime = currentTime;
		}
		break;

	case LEDOFF:
		turnOffLED1();
		if(delay(delay120ms, previousTime)){
			state = LEDON;
			previousTime = currentTime;
		}
		break;
	}
}

void SD2(){
	static State state = INITIAL;
	static uint32_t previousTime = 0;

	if(pushButton() == 1)
		delay500ms = 100;
	else
		delay500ms = 500;

	switch(state){
	case INITIAL:
		turnOnLED2();
		if(delay(delay500ms, previousTime)){
			state = LEDON;
			previousTime = currentTime;
		}
		break;

	case LEDON:
		turnOnLED2();
		if(delay(delay500ms, previousTime)){
			state = LEDOFF;
			previousTime = currentTime;
		}
		break;

	case LEDOFF:
		turnOffLED2();
		if(delay(delay500ms, previousTime)){
			state = LEDON;
			previousTime = currentTime;
		}
		break;
	}
}

void SD3(){
	static State state = INITIAL;
	static uint32_t previousTime = 0;
	static int counter = 0;

	switch(state){
	case INITIAL:
		counter = 0;
		turnOffLED3();
		turnOffLED4();
		if(pushButton() == 1){
			state = LEDON;
			previousTime = currentTime;
		}
		break;

	case LEDON:
		turnOnLED3();
		turnOnLED4();
		if(delay(100, previousTime)){
			state = LEDOFF;
			previousTime = currentTime;
			counter++;
		}

		break;

	case LEDOFF:
		turnOffLED3();
		turnOffLED4();
		if(delay(100, previousTime)){
			state = LEDON;
			previousTime = currentTime;
		}
		if(counter > 5)
			state = INITIAL;
		break;
	}
}
