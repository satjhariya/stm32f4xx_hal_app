#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#include "gpio.hpp"
#include "spi_config.hpp"

namespace hardware
{

class Spi
{
public:
    using RxCallback =
        void(*)(const uint8_t* data, size_t len);

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

    bool start_receive_interrupt(
        uint8_t* data,
        size_t len
    );

    void set_rx_callback(
        RxCallback cb
    );

    void irq_handler();

    void handle_rx_complete();

    SPI_HandleTypeDef* handle();

    SPI_TypeDef* instance() const;

private:
    void enable_clock();

    void init_gpio();

    void configure_nvic();

private:
    SpiConfig config_;

    SPI_HandleTypeDef hspi_ {};

    RxCallback rx_callback_ = nullptr;

    uint8_t* rx_buffer_ = nullptr;

    size_t rx_length_ = 0;
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
        "CsPin must be GPIO type"
    );

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