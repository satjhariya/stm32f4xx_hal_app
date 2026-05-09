extern "C"
{
#include "FreeRTOS.h"
#include "task.h"

#include "system_clock.h"
}

#include "console.hpp"

#include "tasks/console_tasks.hpp"
#include "tasks/led_tasks.hpp"

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

console::Console debug_console(debug_uart);

void uart_rx_callback(uint8_t byte)
{
    debug_console.on_uart_rx(byte);
}

} // namespace

int main()
{
    HAL_Init();

    SystemClock_Config();

    /*
     * ============================================================
     * UART + Console Initialization
     * ============================================================
     */

    debug_uart.init();

    debug_console.init();

    debug_uart.set_rx_callback(
        uart_rx_callback
    );

    debug_uart.start_receive_interrupt();

    debug_uart.write(
        "\r\n[system boot]\r\n"
    );

    /*
     * ============================================================
     * Application Tasks
     * ============================================================
     */

    app::tasks::createLedTasks();

    app::tasks::createConsoleTask(
        debug_console
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
