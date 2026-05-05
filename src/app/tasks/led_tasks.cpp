extern "C" {
#include "FreeRTOS.h"
#include "task.h"
}
// #include "led_tasks.hpp"
#include "hw_config/board.hpp"

namespace app::tasks
{

/* ============================================================
 * Tasks
 * ============================================================ */

static void redTask(void*)
{
    board::Led1::init();

    while (1)
    {
        board::Led1::toggle();
        vTaskDelay(pdMS_TO_TICKS(300));
    }
}

static void greenTask(void*)
{
    board::Led2::init();

    while (1)
    {
        board::Led2::toggle();
        vTaskDelay(pdMS_TO_TICKS(400));
    }
}

static void blueTask(void*)
{
    board::Led3::init();

    while (1)
    {
        board::Led3::toggle();
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

/* ============================================================
 * Task creation API
 * ============================================================ */

void createLedTasks()
{
    xTaskCreate(redTask,   "RED",   128, nullptr, 1, nullptr);
    xTaskCreate(greenTask, "GREEN", 128, nullptr, 1, nullptr);
    xTaskCreate(blueTask,  "BLUE",  128, nullptr, 1, nullptr);
}

} // namespace app::tasks