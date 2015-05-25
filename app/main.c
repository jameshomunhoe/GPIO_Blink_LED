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

#define yield() state = __LINE__; break; case __LINE__:

int delay120ms = 120;
int delay500ms = 500;

typedef enum{
	INITIAL,
	LEDOFF,
	LEDON
}State;

uint32_t currentTime = 0;

void initUserButton(){
	GPIO_InitTypeDef GpioInfo;

	__GPIOA_CLK_ENABLE();
	GpioInfo.Mode = GPIO_MODE_INPUT;
	GpioInfo.Pin = GPIO_PIN_0;
	GpioInfo.Speed = GPIO_SPEED_HIGH;
	GpioInfo.Pull = GPIO_NOPULL;

	HAL_GPIO_Init(GPIOA, &GpioInfo);

}

void initLED1(){

	GPIO_InitTypeDef GpioInfo;

	__GPIOG_CLK_ENABLE();

	GpioInfo.Mode = GPIO_MODE_OUTPUT_PP;
	GpioInfo.Pin = GPIO_PIN_13;
	GpioInfo.Pull = GPIO_NOPULL;
	GpioInfo.Speed = GPIO_SPEED_HIGH;
	GpioInfo.Alternate = GPIO_MODE_AF_PP;

	//Init LED on PG13
	HAL_GPIO_Init(GPIOG, &GpioInfo);
}

void initLED2(){

	GPIO_InitTypeDef GpioInfo;

	__GPIOG_CLK_ENABLE();

	GpioInfo.Mode = GPIO_MODE_OUTPUT_PP;
	GpioInfo.Pin = GPIO_PIN_14;
	GpioInfo.Pull = GPIO_NOPULL;
	GpioInfo.Speed = GPIO_SPEED_HIGH;
	GpioInfo.Alternate = GPIO_MODE_AF_PP;

	//Init LED on PG14
	HAL_GPIO_Init(GPIOG, &GpioInfo);
}

void initLED3(){

	GPIO_InitTypeDef GpioInfo;

	__GPIOC_CLK_ENABLE();

	GpioInfo.Mode = GPIO_MODE_OUTPUT_PP;
	GpioInfo.Pin = GPIO_PIN_5;
	GpioInfo.Pull = GPIO_NOPULL;
	GpioInfo.Speed = GPIO_SPEED_HIGH;
	GpioInfo.Alternate = GPIO_MODE_AF_PP;

	//Init LED on PC5
	HAL_GPIO_Init(GPIOC, &GpioInfo);
}

void initLED4(){

	GPIO_InitTypeDef GpioInfo;

	__GPIOB_CLK_ENABLE();

	GpioInfo.Mode = GPIO_MODE_OUTPUT_PP;
	GpioInfo.Pin = GPIO_PIN_13;
	GpioInfo.Pull = GPIO_NOPULL;
	GpioInfo.Speed = GPIO_SPEED_HIGH;
	GpioInfo.Alternate = GPIO_MODE_AF_PP;

	//Init LED on PB13
	HAL_GPIO_Init(GPIOB, &GpioInfo);
}

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

int main(void)
{
	initUserButton();
	initLED1();
	initLED2();
	initLED3();
	initLED4();

    while(1)
    {
    	SD();
    	SD2();
    	SD3();
    }
}

