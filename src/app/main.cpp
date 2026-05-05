extern "C" {
#include "FreeRTOS.h"
#include "task.h"
#include "stm32f4xx_hal.h"
#include "system_clock.h"
}

#include "tasks/led_tasks.hpp"

int main()
{
    HAL_Init();
    SystemClock_Config();

    app::tasks::createLedTasks();

    vTaskStartScheduler();

    while (1) {}
}