extern "C"
{
#include "FreeRTOS.h"
#include "task.h"
}

#include "console_tasks.hpp"

#include "console.hpp"

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
            console->uart().write(
                &byte,
                1
            );
        }
    }
}

} // namespace

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