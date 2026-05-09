#ifndef CONSOLE_CONSOLE_HPP
#define CONSOLE_CONSOLE_HPP

#include <cstdint>

#include "FreeRTOS.h"
#include "stream_buffer.h"

#include "uart.hpp"

namespace console
{

class Console
{
public:
    explicit Console(hardware::Uart& uart);

    bool init();

    void on_uart_rx(uint8_t byte);

    size_t receive(
        uint8_t* data,
        size_t len,
        TickType_t timeout = portMAX_DELAY
    );

    hardware::Uart& uart();

private:
    static constexpr size_t RX_STREAM_SIZE = 128;

private:
    hardware::Uart& uart_;

    StreamBufferHandle_t rx_stream_ { nullptr };
};

} // namespace console

#endif