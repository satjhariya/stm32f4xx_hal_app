#include "uart.hpp"
#include "uart_internal.hpp"

#include <cstring>

namespace hardware
{

Uart* g_uart_instance = nullptr;

Uart::Uart(USART_TypeDef* instance)
{
    huart_.Instance = instance;

    g_uart_instance = this;
}

void Uart::init_gpio()
{
    if (huart_.Instance == USART2)
    {
        __HAL_RCC_GPIOA_CLK_ENABLE();

        GPIO_InitTypeDef gpio {};

        gpio.Pin       = GPIO_PIN_2 | GPIO_PIN_3;
        gpio.Mode      = GPIO_MODE_AF_PP;
        gpio.Pull      = GPIO_PULLUP;
        gpio.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
        gpio.Alternate = GPIO_AF7_USART2;

        HAL_GPIO_Init(GPIOA, &gpio);
    }
}

bool Uart::init(uint32_t baudrate)
{
    if (huart_.Instance == USART2)
    {
        __HAL_RCC_USART2_CLK_ENABLE();

        HAL_NVIC_SetPriority(USART2_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ(USART2_IRQn);
    }
    else
    {
        return false;
    }

    init_gpio();

    huart_.Init.BaudRate     = baudrate;
    huart_.Init.WordLength   = UART_WORDLENGTH_8B;
    huart_.Init.StopBits     = UART_STOPBITS_1;
    huart_.Init.Parity       = UART_PARITY_NONE;
    huart_.Init.Mode         = UART_MODE_TX_RX;
    huart_.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
    huart_.Init.OverSampling = UART_OVERSAMPLING_16;

    return (HAL_UART_Init(&huart_) == HAL_OK);
}

bool Uart::write(const uint8_t* data, size_t len)
{
    return (
        HAL_UART_Transmit(
            &huart_,
            const_cast<uint8_t*>(data),
            len,
            HAL_MAX_DELAY
        ) == HAL_OK
    );
}

bool Uart::write(const char* str)
{
    return write(
        reinterpret_cast<const uint8_t*>(str),
        std::strlen(str)
    );
}

bool Uart::read_byte(uint8_t& byte)
{
    return (
        HAL_UART_Receive(
            &huart_,
            &byte,
            1,
            0
        ) == HAL_OK
    );
}

bool Uart::start_receive_interrupt()
{
    return (
        HAL_UART_Receive_IT(
            &huart_,
            &rx_byte_,
            1
        ) == HAL_OK
    );
}

void Uart::irq_handler()
{
    HAL_UART_IRQHandler(&huart_);
}

void Uart::set_rx_callback(RxCallback cb)
{
    rx_callback_ = cb;
}

UART_HandleTypeDef* Uart::handle()
{
    return &huart_;
}

uint8_t Uart::rx_byte() const
{
    return rx_byte_;
}

void Uart::handle_rx_complete()
{
    if (rx_callback_ != nullptr)
    {
        rx_callback_(rx_byte_);
    }

    start_receive_interrupt();
}

} // namespace hardware