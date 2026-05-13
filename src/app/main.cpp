extern "C"
{
    #include "system_clock.h"
}

#include "i3g4250d.hpp"
#include "gpio.hpp"
#include "spi.hpp"
#include "spi_config.hpp"

using Cs = hw::GPIO<hw::PortA, GPIO_PIN_1>;

int main()
{
    HAL_Init();

    SystemClock_Config();

    Cs::initOutput();

    Cs::set();

    hardware::SpiConfig spi_cfg {
        .instance = SPI1,

        .sck_port = GPIOA,
        .sck_pin  = GPIO_PIN_5,
        .sck_af   = GPIO_AF5_SPI1,

        .miso_port = GPIOA,
        .miso_pin  = GPIO_PIN_6,
        .miso_af   = GPIO_AF5_SPI1,

        .mosi_port = GPIOA,
        .mosi_pin  = GPIO_PIN_7,
        .mosi_af   = GPIO_AF5_SPI1,

        .irq = SPI1_IRQn,

        .role = hardware::SpiRole::MASTER,

        .baudrate_prescaler =
            SPI_BAUDRATEPRESCALER_16,

        .direction    = SPI_DIRECTION_2LINES,
        .datasize     = SPI_DATASIZE_8BIT,
        .clk_polarity = SPI_POLARITY_LOW,
        .clk_phase    = SPI_PHASE_1EDGE,
        .first_bit    = SPI_FIRSTBIT_MSB
    };

    hardware::Spi spi(spi_cfg);

    if (!spi.init())
    {
        while (true)
        {
        }
    }

    application::I3g4250d<Cs> gyro(spi);

    if (!gyro.init())
    {
        while (true)
        {
        }
    }

    application::I3g4250d<Cs>::AngularRate rate {};

    while (true)
    {
        if (gyro.data_ready())
        {
            gyro.read_angular_rate(rate);
        }
    }
}