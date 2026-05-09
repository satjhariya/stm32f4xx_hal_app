#ifndef HARDWARE_UART_UART_CONFIG_HPP
#define HARDWARE_UART_UART_CONFIG_HPP

#include "stm32f4xx_hal.h"

namespace hardware
{

struct UartConfig
{
    USART_TypeDef* instance;

    GPIO_TypeDef* tx_port;
    uint16_t tx_pin;
    uint32_t tx_af;

    GPIO_TypeDef* rx_port;
    uint16_t rx_pin;
    uint32_t rx_af;

    IRQn_Type irq;

    uint32_t baudrate;
};

} // namespace hardware

#endif