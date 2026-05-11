#include "spi.hpp"

#include "interrupt.hpp"
#include "spi_internal.hpp"

namespace hardware
{

namespace
{

struct SpiRegistry
{
    SPI_TypeDef* instance;
    Spi* spi;
};

constexpr size_t MAX_SPIS = 6;

SpiRegistry registry[MAX_SPIS] {};

void spi1_irq_handler()
{
    auto spi = find_spi_instance(SPI1);

    if (spi != nullptr)
    {
        spi->irq_handler();
    }
}

void spi2_irq_handler()
{
    auto spi = find_spi_instance(SPI2);

    if (spi != nullptr)
    {
        spi->irq_handler();
    }
}

void spi3_irq_handler()
{
    auto spi = find_spi_instance(SPI3);

    if (spi != nullptr)
    {
        spi->irq_handler();
    }
}

} // namespace

void register_spi_instance(
    SPI_TypeDef* instance,
    Spi* spi
)
{
    for (auto& entry : registry)
    {
        if (entry.instance == nullptr)
        {
            entry.instance = instance;
            entry.spi      = spi;
            return;
        }
    }
}

Spi* find_spi_instance(
    SPI_TypeDef* instance
)
{
    for (auto& entry : registry)
    {
        if (entry.instance == instance)
        {
            return entry.spi;
        }
    }

    return nullptr;
}

Spi::Spi(const SpiConfig& config)
    : config_(config)
{
    hspi_.Instance = config_.instance;
}

void Spi::enable_clock()
{
    if (config_.instance == SPI1)
    {
        __HAL_RCC_SPI1_CLK_ENABLE();
    }
    else if (config_.instance == SPI2)
    {
        __HAL_RCC_SPI2_CLK_ENABLE();
    }
    else if (config_.instance == SPI3)
    {
        __HAL_RCC_SPI3_CLK_ENABLE();
    }
}

void Spi::init_gpio()
{
    if (config_.sck_port == GPIOA)
    {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    }
    else if (config_.sck_port == GPIOB)
    {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    }
    else if (config_.sck_port == GPIOC)
    {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    }

    if (config_.miso_port == GPIOA)
    {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    }
    else if (config_.miso_port == GPIOB)
    {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    }
    else if (config_.miso_port == GPIOC)
    {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    }

    if (config_.mosi_port == GPIOA)
    {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    }
    else if (config_.mosi_port == GPIOB)
    {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    }
    else if (config_.mosi_port == GPIOC)
    {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    }

    GPIO_InitTypeDef gpio {};

    gpio.Mode  = GPIO_MODE_AF_PP;
    gpio.Pull  = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

    gpio.Pin       = config_.sck_pin;
    gpio.Alternate = config_.sck_af;

    HAL_GPIO_Init(config_.sck_port, &gpio);

    gpio.Pin       = config_.miso_pin;
    gpio.Alternate = config_.miso_af;

    HAL_GPIO_Init(config_.miso_port, &gpio);

    gpio.Pin       = config_.mosi_pin;
    gpio.Alternate = config_.mosi_af;

    HAL_GPIO_Init(config_.mosi_port, &gpio);
}

void Spi::configure_nvic()
{
    HAL_NVIC_SetPriority(config_.irq, 5, 0);

    HAL_NVIC_EnableIRQ(config_.irq);

    if (config_.instance == SPI1)
    {
        platform::register_irq_handler(
            SPI1_IRQn,
            spi1_irq_handler
        );
    }
    else if (config_.instance == SPI2)
    {
        platform::register_irq_handler(
            SPI2_IRQn,
            spi2_irq_handler
        );
    }
    else if (config_.instance == SPI3)
    {
        platform::register_irq_handler(
            SPI3_IRQn,
            spi3_irq_handler
        );
    }
}

bool Spi::init()
{
    enable_clock();

    init_gpio();

    configure_nvic();

    hspi_.Init.Mode              = config_.mode;
    hspi_.Init.Direction         = config_.direction;
    hspi_.Init.DataSize          = config_.datasize;
    hspi_.Init.CLKPolarity       = config_.clk_polarity;
    hspi_.Init.CLKPhase          = config_.clk_phase;
    hspi_.Init.NSS               = config_.nss;
    hspi_.Init.BaudRatePrescaler = config_.baudrate_prescaler;
    hspi_.Init.FirstBit          = config_.first_bit;
    hspi_.Init.TIMode            = config_.timode;
    hspi_.Init.CRCCalculation    = config_.crc_calculation;

    if (HAL_SPI_Init(&hspi_) != HAL_OK)
    {
        return false;
    }

    register_spi_instance(
        config_.instance,
        this
    );

    return true;
}

bool Spi::write(
    const uint8_t* data,
    size_t len
)
{
    return (
        HAL_SPI_Transmit(
            &hspi_,
            const_cast<uint8_t*>(data),
            len,
            HAL_MAX_DELAY
        ) == HAL_OK
    );
}

bool Spi::read(
    uint8_t* data,
    size_t len
)
{
    return (
        HAL_SPI_Receive(
            &hspi_,
            data,
            len,
            HAL_MAX_DELAY
        ) == HAL_OK
    );
}

bool Spi::transfer(
    const uint8_t* tx,
    uint8_t* rx,
    size_t len
)
{
    return (
        HAL_SPI_TransmitReceive(
            &hspi_,
            const_cast<uint8_t*>(tx),
            rx,
            len,
            HAL_MAX_DELAY
        ) == HAL_OK
    );
}


void Spi::irq_handler()
{
    HAL_SPI_IRQHandler(&hspi_);
}

SPI_HandleTypeDef* Spi::handle()
{
    return &hspi_;
}

SPI_TypeDef* Spi::instance() const
{
    return config_.instance;
}

} // namespace hardware