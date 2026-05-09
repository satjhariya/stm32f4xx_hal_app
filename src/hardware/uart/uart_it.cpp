#include "uart.hpp"
#include "uart_internal.hpp"

extern "C"
void USART2_IRQHandler(void)
{
    if (hardware::g_uart_instance != nullptr)
    {
        hardware::g_uart_instance->irq_handler();
    }
}

extern "C"
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
    using namespace hardware;

    if (g_uart_instance == nullptr)
    {
        return;
    }

    if (huart == g_uart_instance->handle())
    {
        g_uart_instance->handle_rx_complete();
    }
}