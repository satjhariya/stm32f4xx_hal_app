#include "debug_uart.hpp"

#include "uart_config.hpp"

namespace
{

constexpr hardware::UartConfig debug_uart_config
{
    .instance = USART2,

    .tx_port = GPIOA,
    .tx_pin  = GPIO_PIN_2,
    .tx_af   = GPIO_AF7_USART2,

    .rx_port = GPIOA,
    .rx_pin  = GPIO_PIN_3,
    .rx_af   = GPIO_AF7_USART2,

    .irq = USART2_IRQn,

    .baudrate = 115200
};

void uart_rx_callback(uint8_t byte)
{
    board::DebugConsole.on_uart_rx(byte);
}

} // namespace

namespace board
{

hardware::Uart DebugUart(
    debug_uart_config
);

console::Console DebugConsole(
    DebugUart
);

void initDebugConsole()
{
    DebugUart.init();

    DebugConsole.init();

    DebugUart.set_rx_callback(
        uart_rx_callback
    );

    DebugUart.start_receive_interrupt();
}

} // namespace board