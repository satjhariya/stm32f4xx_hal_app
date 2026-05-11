#include <cstdint>

#include "gpio.hpp"
#include "spi.hpp"
#include "spi_config.hpp"

using namespace hardware;

int main()
{
    // -------------------------------------------------
    // Chip Select GPIO
    // -------------------------------------------------
    using cs = hw::GPIO<hw::PortA,GPIO_PIN_1>;
    cs::initOutput();

    cs::set();

    // -------------------------------------------------
    // SPI Configuration
    // -------------------------------------------------

    SpiConfig spi_cfg {
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

        .baudrate_prescaler =
            SPI_BAUDRATEPRESCALER_16,

        .mode         = SPI_MODE_MASTER,
        .direction    = SPI_DIRECTION_2LINES,
        .datasize     = SPI_DATASIZE_8BIT,
        .clk_polarity = SPI_POLARITY_LOW,
        .clk_phase    = SPI_PHASE_1EDGE,
        .nss          = SPI_NSS_SOFT,
        .first_bit    = SPI_FIRSTBIT_MSB
    };

    Spi spi(spi_cfg);

    if (!spi.init())
    {
        while (true)
        {
        }
    }

    // -------------------------------------------------
    // Example: Read JEDEC ID
    // -------------------------------------------------

    constexpr uint8_t CMD_JEDEC_ID = 0x9F;

    uint8_t tx[4] = {
        CMD_JEDEC_ID,
        0x00,
        0x00,
        0x00
    };

    uint8_t rx[4] {};

    if (!spi.transfer<cs>(
            tx,
            rx,
            sizeof(tx)
        ))
    {
        while (true)
        {
        }
    }

    // rx[1] -> Manufacturer ID
    // rx[2] -> Memory Type
    // rx[3] -> Capacity

    volatile uint8_t manufacturer = rx[1];
    volatile uint8_t memory_type  = rx[2];
    volatile uint8_t capacity     = rx[3];

    (void)manufacturer;
    (void)memory_type;
    (void)capacity;

    while (true)
    {
    }
}