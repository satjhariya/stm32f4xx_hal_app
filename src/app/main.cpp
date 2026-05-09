extern "C" {
// #include "FreeRTOS.h"
// #include "task.h"
#include "stm32f4xx_hal.h"
#include "system_clock.h"
}

// #include "tasks/led_tasks.hpp"

// int main()
// {
//     HAL_Init();
//     SystemClock_Config();

//     app::tasks::createLedTasks();

//     vTaskStartScheduler();

//     while (1) {}
// }

#include "uart.hpp"
#include "uart_config.hpp"

using namespace hardware;

namespace
{

constexpr UartConfig debug_uart_config
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

Uart debug_uart(debug_uart_config);

void rx_callback(uint8_t byte)
{
    debug_uart.write(&byte, 1);
}

} // namespace

int main()
{
    HAL_Init();

    SystemClock_Config();

    debug_uart.init();

    debug_uart.set_rx_callback(rx_callback);

    debug_uart.start_receive_interrupt();

    debug_uart.write("\r\n");
    debug_uart.write("=================================\r\n");
    debug_uart.write(" STM32 UART IRQ Driver Ready\r\n");
    debug_uart.write(" USART2 @ 115200 baud\r\n");
    debug_uart.write(" Interrupt-driven RX enabled\r\n");
    debug_uart.write("=================================\r\n");

    while (1)
    {
    }
}