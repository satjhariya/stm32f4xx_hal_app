#ifndef HARDWARE_UART_UART_HPP
#define HARDWARE_UART_UART_HPP

#include <cstddef>
#include <cstdint>

#include "stm32f4xx_hal.h"

namespace hardware
{

class Uart
{
public:
    using RxCallback = void(*)(uint8_t byte);

public:
    explicit Uart(USART_TypeDef* instance);

    bool init(uint32_t baudrate);

    bool write(const uint8_t* data, size_t len);

    bool write(const char* str);

    bool read_byte(uint8_t& byte);

    bool start_receive_interrupt();

    void irq_handler();

    void set_rx_callback(RxCallback cb);

    UART_HandleTypeDef* handle();

    uint8_t rx_byte() const;

    void handle_rx_complete();

private:
    void init_gpio();

private:
    UART_HandleTypeDef huart_ {};

    uint8_t rx_byte_ {};

    RxCallback rx_callback_ { nullptr };
};

} // namespace hardware

#endif