extern "C" {
#include "FreeRTOS.h"
#include "task.h"
#include "stm32f4xx_hal.h"
#include "system_clock.h"
}

#include "hw_config/board.hpp"

/* ============================================================
 * Tasks
 * ============================================================ */

void redTask(void*)
{
    board::Led1::init();

    while (1)
    {
        board::Led1::toggle();
        vTaskDelay(pdMS_TO_TICKS(300));
    }
}

void greenTask(void*)
{
    board::Led2::init();

    while (1)
    {
        board::Led2::toggle();
        vTaskDelay(pdMS_TO_TICKS(400));
    }
}

void blueTask(void*)
{
    board::Led3::init();

    while (1)
    {
        board::Led3::toggle();
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

/* ============================================================
 * main
 * ============================================================ */

int main()
{
    HAL_Init();
    SystemClock_Config();

    xTaskCreate(redTask,   "RED",   128, nullptr, 1, nullptr);
    xTaskCreate(greenTask, "GREEN", 128, nullptr, 1, nullptr);
    xTaskCreate(blueTask,  "BLUE",  128, nullptr, 1, nullptr);

    vTaskStartScheduler();

    while (1) {}
}