extern "C"
{
#include "FreeRTOS.h"
#include "task.h"

#include "system_clock.h"
}

#include "hw_config/board.hpp"

#include "tasks/console_tasks.hpp"

int main()
{
    HAL_Init();

    SystemClock_Config();

    /*
     * ============================================================
     * Board Services
     * ============================================================
     */

    board::initDebugConsole();

    board::DebugUart.write(
        "\r\n[system boot]\r\n"
    );

    /*
     * ============================================================
     * Application Tasks
     * ============================================================
     */

    app::tasks::createConsoleTask(
        board::DebugConsole
    );

    /*
     * ============================================================
     * Start Scheduler
     * ============================================================
     */

    vTaskStartScheduler();

    while (1)
    {
    }
}