#include "stm32f4xx_hal.h"
#include "system_stm32f4xx.h"
#include "led.h"
#include "system_clock.h"

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    LED_Init();

    while (1)
    {
        LED_Toggle();
        HAL_Delay(500);
    }
}