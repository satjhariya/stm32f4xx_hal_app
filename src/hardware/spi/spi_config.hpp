#pragma once

#include "stm32f4xx_hal.h"

namespace hardware
{

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

    IRQn_Type irq;

    uint32_t baudrate_prescaler;

    uint32_t mode           = SPI_MODE_MASTER;
    uint32_t direction      = SPI_DIRECTION_2LINES;
    uint32_t datasize       = SPI_DATASIZE_8BIT;
    uint32_t clk_polarity   = SPI_POLARITY_LOW;
    uint32_t clk_phase      = SPI_PHASE_1EDGE;
    uint32_t nss            = SPI_NSS_SOFT;
    uint32_t first_bit      = SPI_FIRSTBIT_MSB;
    uint32_t timode         = SPI_TIMODE_DISABLE;
    uint32_t crc_calculation = SPI_CRCCALCULATION_DISABLE;
};

} // namespace hardware