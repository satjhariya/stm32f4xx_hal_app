#ifndef HARDWARE_UART_UART_INTERNAL_HPP
#define HARDWARE_UART_UART_INTERNAL_HPP

#include "stm32f4xx_hal.h"

namespace hardware
{

class Uart;

Uart* find_uart_instance(USART_TypeDef* instance);

void register_uart_instance(
    USART_TypeDef* instance,
    Uart* uart
);

} // namespace hardware

#endif