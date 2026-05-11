#pragma once

#include "stm32f4xx_hal.h"

namespace hardware
{

enum class SpiRole
{
    MASTER,
    SLAVE
};

struct SpiConfig
{
    SPI_TypeDef* instance;

    GPIO_TypeDef* sck_port;
    uint16_t sck_pin;
    uint8_t sck_af;

    GPIO_TypeDef* miso_port;
    uint16_t miso_pin;
    uint8_t miso_af;

    GPIO_TypeDef* mosi_port;
    uint16_t mosi_pin;
    uint8_t mosi_af;

    GPIO_TypeDef* nss_port = nullptr;
    uint16_t nss_pin       = 0;
    uint8_t nss_af         = 0;

    IRQn_Type irq;

    SpiRole role = SpiRole::MASTER;

    uint32_t baudrate_prescaler =
        SPI_BAUDRATEPRESCALER_16;

    uint32_t direction    = SPI_DIRECTION_2LINES;
    uint32_t datasize     = SPI_DATASIZE_8BIT;
    uint32_t clk_polarity = SPI_POLARITY_LOW;
    uint32_t clk_phase    = SPI_PHASE_1EDGE;
    uint32_t first_bit    = SPI_FIRSTBIT_MSB;

    uint32_t timode =
        SPI_TIMODE_DISABLE;

    uint32_t crc_calculation =
        SPI_CRCCALCULATION_DISABLE;
};

} // namespace hardware