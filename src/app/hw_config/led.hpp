#pragma once

/**
 * @file led.hpp
 * @brief Compile-time LED abstraction built on top of GPIO
 *
 * Features:
 * - Zero-cost abstraction (fully inlined)
 * - Supports active-high and active-low LEDs
 * - Simple and expressive API
 *
 * Usage:
 *
 * using Led = app::LED<hw::GPIO<hw::PortA, GPIO_PIN_5>>;
 * Led::init();
 * Led::on();
 */

namespace app
{

/**
 * @tparam Gpio        GPIO type (hw::GPIO<...>)
 * @tparam ActiveHigh  true = LED turns ON when pin is HIGH
 *                     false = LED turns ON when pin is LOW
 */
template<typename Gpio, bool ActiveHigh = true>
struct LED
{
    /* ------------------------------------------------------------
     * Initialization
     * ------------------------------------------------------------ */
    static inline void init()
    {
        Gpio::initOutput();
        off();  // ensure known default state
    }

    /* ------------------------------------------------------------
     * Control
     * ------------------------------------------------------------ */

    /**
     * @brief Turn LED ON
     */
    static inline void on()
    {
        if constexpr (ActiveHigh)
            Gpio::set();
        else
            Gpio::reset();
    }

    /**
     * @brief Turn LED OFF
     */
    static inline void off()
    {
        if constexpr (ActiveHigh)
            Gpio::reset();
        else
            Gpio::set();
    }

    /**
     * @brief Toggle LED state
     */
    static inline void toggle()
    {
        Gpio::toggle();
    }

    /* ------------------------------------------------------------
     * Optional helpers
     * ------------------------------------------------------------ */

    /**
     * @brief Set LED state explicitly
     */
    static inline void write(bool state)
    {
        state ? on() : off();
    }

    /**
     * @brief Read LED state (logical state, not raw pin)
     */
    static inline bool isOn()
    {
        if constexpr (ActiveHigh)
            return Gpio::read();
        else
            return !Gpio::read();
    }
};

} // namespace app