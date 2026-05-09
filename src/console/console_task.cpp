#include "console_task.hpp"

#include "FreeRTOS.h"
#include "task.h"

#include "console.hpp"

namespace console
{

namespace
{

constexpr uint16_t CONSOLE_TASK_STACK_SIZE = 512;

constexpr UBaseType_t CONSOLE_TASK_PRIORITY = 2;

void console_task(void* arg)
{
    auto* console =
        static_cast<Console*>(arg);

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

void start_console_task(Console& console)
{
    xTaskCreate(
        console_task,
        "console",
        CONSOLE_TASK_STACK_SIZE,
        &console,
        CONSOLE_TASK_PRIORITY,
        nullptr
    );
}

} // namespace console