#pragma once

#include <cstddef>
#include <cstdint>

#include "gpio.hpp"
#include "spi_config.hpp"

namespace hardware
{

class Spi
{
public:
    explicit Spi(const SpiConfig& config);

    bool init();

    bool write(
        const uint8_t* data,
        size_t len
    );

    bool read(
        uint8_t* data,
        size_t len
    );

    bool transfer(
        const uint8_t* tx,
        uint8_t* rx,
        size_t len
    );

    template<typename CsPin>
    bool transfer(
        const uint8_t* tx,
        uint8_t* rx,
        size_t len
    );
    
    void irq_handler();

    SPI_HandleTypeDef* handle();

    SPI_TypeDef* instance() const;

private:
    void enable_clock();

    void init_gpio();

    void configure_nvic();

private:
    SpiConfig config_;

    SPI_HandleTypeDef hspi_ {};
};


template<typename CsPin>
bool Spi::transfer(
    const uint8_t* tx,
    uint8_t* rx,
    size_t len
)
{
    static_assert(
        std::is_class_v<CsPin>,
        "CsPin must be GPIO type");
    CsPin::reset();

    auto result = transfer(
        tx,
        rx,
        len
    );

    CsPin::set();

    return result;
}

} // namespace hardware