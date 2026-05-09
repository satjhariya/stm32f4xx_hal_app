#include "console.hpp"

namespace console
{

Console::Console(hardware::Uart& uart)
    : uart_(uart)
{
}

bool Console::init()
{
    rx_stream_ = xStreamBufferCreate(
        RX_STREAM_SIZE,
        1
    );

    return (rx_stream_ != nullptr);
}

void Console::on_uart_rx(uint8_t byte)
{
    BaseType_t higher_priority_task_woken = pdFALSE;

    xStreamBufferSendFromISR(
        rx_stream_,
        &byte,
        sizeof(byte),
        &higher_priority_task_woken
    );

    portYIELD_FROM_ISR(higher_priority_task_woken);
}

size_t Console::receive(
    uint8_t* data,
    size_t len,
    TickType_t timeout
)
{
    return xStreamBufferReceive(
        rx_stream_,
        data,
        len,
        timeout
    );
}

hardware::Uart& Console::uart()
{
    return uart_;
}

} // namespace console