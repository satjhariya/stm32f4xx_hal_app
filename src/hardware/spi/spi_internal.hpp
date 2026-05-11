#pragma once

#include "spi.hpp"

namespace hardware
{

void register_spi_instance(
    SPI_TypeDef* instance,
    Spi* spi
);

Spi* find_spi_instance(
    SPI_TypeDef* instance
);

} // namespace hardware