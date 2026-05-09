#ifndef HARDWARE_UART_UART_HPP
#define HARDWARE_UART_UART_HPP

#include <cstddef>
#include <cstdint>

#include "stm32f4xx_hal.h"

#include "uart_config.hpp"

namespace hardware
{

class Uart
{
public:
    using RxCallback = void(*)(uint8_t byte);

public:
    explicit Uart(const UartConfig& config);

    bool init();

    bool write(const uint8_t* data, size_t len);

    bool write(const char* str);

    bool read_byte(uint8_t& byte);

    bool start_receive_interrupt();

    void irq_handler();

    void handle_rx_complete();

    void set_rx_callback(RxCallback cb);

    UART_HandleTypeDef* handle();

    USART_TypeDef* instance() const;

private:
    void init_gpio();

    void enable_clock();

    void configure_nvic();

private:
    UartConfig config_;

    UART_HandleTypeDef huart_ {};

    uint8_t rx_byte_ {};

    RxCallback rx_callback_ { nullptr };
};

} // namespace hardware

#endif