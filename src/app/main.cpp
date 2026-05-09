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

hardware::Uart uart(USART2);

void rx_callback(uint8_t byte)
{
    uart.write(&byte, 1);
}

int main()
{
    HAL_Init();

    SystemClock_Config();

    uart.init(115200);

    uart.set_rx_callback(rx_callback);

    uart.start_receive_interrupt();

    uart.write("UART IRQ Ready\r\n");

    while (1)
    {
    }
}