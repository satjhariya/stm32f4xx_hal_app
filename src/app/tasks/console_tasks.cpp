extern "C"
{
#include "FreeRTOS.h"
#include "task.h"
}

#include "console_tasks.hpp"

#include "console.hpp"
#include "tasks/led_tasks.hpp"
#include "hw_config/board.hpp"

namespace app::tasks
{

namespace
{

void consoleTask(void* arg)
{
    auto* console =
        static_cast<console::Console*>(arg);

    uint8_t byte {};

    console->uart().write(
        "\r\n[console task started]\r\n"
    );

    for (;;)
    {
        if (console->receive(
                &byte,
                sizeof(byte)
            ) > 0)
        {
            switch (byte)
            {
                case 'a':
                {
                    app::tasks::startRedTask();

                    console->uart().write(
                        "RED TASK START\r\n"
                    );

                    break;
                }

                case 'A':
                {
                    app::tasks::stopRedTask();

                    console->uart().write(
                        "RED TASK STOP\r\n"
                    );

                    break;
                }

                case 'b':
                {
                    app::tasks::startGreenTask();

                    console->uart().write(
                        "GREEN TASK START\r\n"
                    );

                    break;
                }

                case 'B':
                {
                    app::tasks::stopGreenTask();

                    console->uart().write(
                        "GREEN TASK STOP\r\n"
                    );

                    break;
                }

                case 'c':
                {
                    app::tasks::startBlueTask();

                    console->uart().write(
                        "BLUE TASK START\r\n"
                    );

                    break;
                }

                case 'C':
                {
                    app::tasks::stopBlueTask();

                    console->uart().write(
                        "BLUE TASK STOP\r\n"
                    );

                    break;
                }

                default:
                {
                    console->uart().write(
                        "UNKNOWN\r\n"
                    );

                    break;
                }
            }
    }
}

} // namespace
}
void createConsoleTask(
    console::Console& console
)
{
    xTaskCreate(
        consoleTask,
        "console",
        512,
        &console,
        2,
        nullptr
    );
}
} // namespace app::tasks