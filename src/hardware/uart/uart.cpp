#include "uart.hpp"

#include <cstring>

#include "interrupt.hpp"
#include "uart_internal.hpp"

namespace hardware
{

namespace
{

struct UartRegistry
{
    USART_TypeDef* instance;
    Uart* uart;
};

constexpr size_t MAX_UARTS = 8;

UartRegistry registry[MAX_UARTS] {};

void usart1_irq_handler()
{
    auto uart = find_uart_instance(USART1);

    if (uart != nullptr)
    {
        uart->irq_handler();
    }
}

void usart2_irq_handler()
{
    auto uart = find_uart_instance(USART2);

    if (uart != nullptr)
    {
        uart->irq_handler();
    }
}

void usart6_irq_handler()
{
    auto uart = find_uart_instance(USART6);

    if (uart != nullptr)
    {
        uart->irq_handler();
    }
}

} // namespace

void register_uart_instance(
    USART_TypeDef* instance,
    Uart* uart
)
{
    for (auto& entry : registry)
    {
        if (entry.instance == nullptr)
        {
            entry.instance = instance;
            entry.uart     = uart;
            return;
        }
    }
}

Uart* find_uart_instance(
    USART_TypeDef* instance
)
{
    for (auto& entry : registry)
    {
        if (entry.instance == instance)
        {
            return entry.uart;
        }
    }

    return nullptr;
}

Uart::Uart(const UartConfig& config)
    : config_(config)
{
    huart_.Instance = config_.instance;
}

void Uart::enable_clock()
{
    if (config_.instance == USART1)
    {
        __HAL_RCC_USART1_CLK_ENABLE();
    }
    else if (config_.instance == USART2)
    {
        __HAL_RCC_USART2_CLK_ENABLE();
    }
    else if (config_.instance == USART6)
    {
        __HAL_RCC_USART6_CLK_ENABLE();
    }
}

void Uart::init_gpio()
{
    if (config_.tx_port == GPIOA)
    {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    }
    else if (config_.tx_port == GPIOB)
    {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    }
    else if (config_.tx_port == GPIOC)
    {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    }

    if (config_.rx_port == GPIOA)
    {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    }
    else if (config_.rx_port == GPIOB)
    {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    }
    else if (config_.rx_port == GPIOC)
    {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    }

    GPIO_InitTypeDef gpio {};

    gpio.Mode  = GPIO_MODE_AF_PP;
    gpio.Pull  = GPIO_PULLUP;
    gpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

    gpio.Pin       = config_.tx_pin;
    gpio.Alternate = config_.tx_af;

    HAL_GPIO_Init(config_.tx_port, &gpio);

    gpio.Pin       = config_.rx_pin;
    gpio.Alternate = config_.rx_af;

    HAL_GPIO_Init(config_.rx_port, &gpio);
}

void Uart::configure_nvic()
{
    HAL_NVIC_SetPriority(config_.irq, 5, 0);

    HAL_NVIC_EnableIRQ(config_.irq);

    if (config_.instance == USART1)
    {
        platform::register_irq_handler(
            USART1_IRQn,
            usart1_irq_handler
        );
    }
    else if (config_.instance == USART2)
    {
        platform::register_irq_handler(
            USART2_IRQn,
            usart2_irq_handler
        );
    }
    else if (config_.instance == USART6)
    {
        platform::register_irq_handler(
            USART6_IRQn,
            usart6_irq_handler
        );
    }
}

bool Uart::init()
{
    enable_clock();

    init_gpio();

    configure_nvic();

    huart_.Init.BaudRate     = config_.baudrate;
    huart_.Init.WordLength   = UART_WORDLENGTH_8B;
    huart_.Init.StopBits     = UART_STOPBITS_1;
    huart_.Init.Parity       = UART_PARITY_NONE;
    huart_.Init.Mode         = UART_MODE_TX_RX;
    huart_.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
    huart_.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart_) != HAL_OK)
    {
        return false;
    }

    register_uart_instance(
        config_.instance,
        this
    );

    return true;
}

bool Uart::write(
    const uint8_t* data,
    size_t len
)
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

void Uart::handle_rx_complete()
{
    if (rx_callback_ != nullptr)
    {
        rx_callback_(rx_byte_);
    }

    start_receive_interrupt();
}

void Uart::set_rx_callback(
    RxCallback cb
)
{
    rx_callback_ = cb;
}

UART_HandleTypeDef* Uart::handle()
{
    return &huart_;
}

USART_TypeDef* Uart::instance() const
{
    return config_.instance;
}

} // namespace hardware

extern "C"
void HAL_UART_RxCpltCallback(
    UART_HandleTypeDef* huart
)
{
    auto uart =
        hardware::find_uart_instance(

            huart->Instance
        );

    if (uart != nullptr)
    {
        uart->handle_rx_complete();
    }
}