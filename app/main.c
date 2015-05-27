#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "Init.h"
#include "Time.h"

typedef enum{
	INITIAL,
	LEDOFF,
	LEDON
}State;

typedef struct{
	State state;
}TaskBlock;

#define initTaskBlock(x)	((x)->state = 0)

#define yield(x)	((x)->state = __LINE__); break; case __LINE__:

#define startTask(x)	switch((x)->state){ case 0:

#define endTask(x)	(x)->state = 0; }




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


