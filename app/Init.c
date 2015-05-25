#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

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

void initUserButton(){
	GPIO_InitTypeDef GpioInfo;

	__GPIOA_CLK_ENABLE();
	GpioInfo.Mode = GPIO_MODE_INPUT;
	GpioInfo.Pin = GPIO_PIN_0;
	GpioInfo.Speed = GPIO_SPEED_HIGH;
	GpioInfo.Pull = GPIO_NOPULL;

	HAL_GPIO_Init(GPIOA, &GpioInfo);

}
