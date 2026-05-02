#pragma once

#include "gpio/gpio.hpp"
#include "hw_config/led.hpp"

namespace board
{
    using Led1 = app::LED<hw::GPIO<hw::PortA, GPIO_PIN_1>>;
    using Led2 = app::LED<hw::GPIO<hw::PortB, GPIO_PIN_1>>;
    using Led3 = app::LED<hw::GPIO<hw::PortC, GPIO_PIN_1>>;

    template<typename... Leds>
    struct LEDGroup
    {
        static inline void init()   { (Leds::init(), ...); }
        static inline void toggle() { (Leds::toggle(), ...); }
    };

    using Leds = LEDGroup<Led1, Led2, Led3>;
}