extern "C"
{
#include "FreeRTOS.h"
#include "task.h"
}

#include "tasks/led_tasks.hpp"

#include "hw_config/board.hpp"

namespace app::tasks
{

namespace
{

/* ============================================================
 * Task Handles
 * ============================================================ */

TaskHandle_t red_task_handle   { nullptr };

TaskHandle_t green_task_handle { nullptr };

TaskHandle_t blue_task_handle  { nullptr };

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

} // namespace

/* ============================================================
 * Red LED Task Control
 * ============================================================ */

void startRedTask()
{
    if (red_task_handle != nullptr)
    {
        return;
    }

    xTaskCreate(
        redTask,
        "RED",
        128,
        nullptr,
        1,
        &red_task_handle
    );
}

void stopRedTask()
{
    if (red_task_handle == nullptr)
    {
        return;
    }

    vTaskDelete(red_task_handle);

    red_task_handle = nullptr;

    board::Led1::off();
}

/* ============================================================
 * Green LED Task Control
 * ============================================================ */

void startGreenTask()
{
    if (green_task_handle != nullptr)
    {
        return;
    }

    xTaskCreate(
        greenTask,
        "GREEN",
        128,
        nullptr,
        1,
        &green_task_handle
    );
}

void stopGreenTask()
{
    if (green_task_handle == nullptr)
    {
        return;
    }

    vTaskDelete(green_task_handle);

    green_task_handle = nullptr;

    board::Led2::off();
}

/* ============================================================
 * Blue LED Task Control
 * ============================================================ */

void startBlueTask()
{
    if (blue_task_handle != nullptr)
    {
        return;
    }

    xTaskCreate(
        blueTask,
        "BLUE",
        128,
        nullptr,
        1,
        &blue_task_handle
    );
}

void stopBlueTask()
{
    if (blue_task_handle == nullptr)
    {
        return;
    }

    vTaskDelete(blue_task_handle);

    blue_task_handle = nullptr;

    board::Led3::off();
}

/* ============================================================
 * Helper APIs
 * ============================================================ */

void startLedTasks()
{
    startRedTask();

    startGreenTask();

    startBlueTask();
}

void stopLedTasks()
{
    stopRedTask();

    stopGreenTask();

    stopBlueTask();
}

} // namespace app::tasks