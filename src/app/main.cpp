extern "C" {
#include "stm32f4xx_hal.h"
#include "system_clock.h"
}

#include "hw_config/board.hpp"

int main()
{
    HAL_Init();
    SystemClock_Config();

    board::Leds::init();

    while (1)
    {
        board::Leds::toggle();
        HAL_Delay(500);
    }
}