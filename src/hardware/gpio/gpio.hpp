#pragma once

/**
 * @file gpio.hpp
 * @brief Zero-cost GPIO abstraction for STM32F4 (HAL-assisted initialization)
 *
 * Design goals:
 * - Compile-time pin binding (no runtime overhead)
 * - HAL used only for initialization (debug-friendly)
 * - Direct register access for fast I/O operations
 * - No dynamic allocation, no runtime objects
 *
 * Usage example:
 *
 * using Led = hw::GPIO<hw::PortA, GPIO_PIN_5>;
 * Led::initOutput();
 * Led::set();
 */

#include <cstdint>
#include <type_traits>

extern "C" {
#include "stm32f4xx_hal.h"
}

namespace hw
{

/* ============================================================
 * Port definitions (compile-time tags)
 * ============================================================ */
struct PortA { static constexpr uintptr_t base = GPIOA_BASE; };
struct PortB { static constexpr uintptr_t base = GPIOB_BASE; };
struct PortC { static constexpr uintptr_t base = GPIOC_BASE; };
struct PortD { static constexpr uintptr_t base = GPIOD_BASE; };
struct PortE { static constexpr uintptr_t base = GPIOE_BASE; };
struct PortH { static constexpr uintptr_t base = GPIOH_BASE; };


/* ============================================================
 * Clock enable mapping (compile-time specialization)
 * ============================================================ */
template<typename Port>
struct Clock;

template<> struct Clock<PortA> { static inline void enable() { __HAL_RCC_GPIOA_CLK_ENABLE(); } };
template<> struct Clock<PortB> { static inline void enable() { __HAL_RCC_GPIOB_CLK_ENABLE(); } };
template<> struct Clock<PortC> { static inline void enable() { __HAL_RCC_GPIOC_CLK_ENABLE(); } };
template<> struct Clock<PortD> { static inline void enable() { __HAL_RCC_GPIOD_CLK_ENABLE(); } };
template<> struct Clock<PortE> { static inline void enable() { __HAL_RCC_GPIOE_CLK_ENABLE(); } };
template<> struct Clock<PortH> { static inline void enable() { __HAL_RCC_GPIOH_CLK_ENABLE(); } };


/* ============================================================
 * GPIO abstraction
 * ============================================================ */
/**
 * @tparam Port  Port type (PortA, PortB, ...)
 * @tparam Pin   HAL pin mask (e.g., GPIO_PIN_5)
 *
 * Provides:
 * - Output configuration
 * - Input configuration
 * - Fast register-level operations
 */
template<typename Port, uint16_t Pin>
struct GPIO
{
    /* ------------------------------------------------------------
     * Register access
     * ------------------------------------------------------------ */
    static inline volatile GPIO_TypeDef* reg()
    {
        return reinterpret_cast<volatile GPIO_TypeDef*>(Port::base);
    }

    /* ------------------------------------------------------------
     * Clock control
     * ------------------------------------------------------------ */
    static inline void enableClock()
    {
        Clock<Port>::enable();
    }

    /* ============================================================
     * Initialization
     * ============================================================ */

    /**
     * @brief Configure pin as push-pull output
     */
    static void initOutput()
    {
        enableClock();

        GPIO_InitTypeDef gpio{};
        gpio.Pin   = Pin;
        gpio.Mode  = GPIO_MODE_OUTPUT_PP;
        gpio.Pull  = GPIO_NOPULL;
        gpio.Speed = GPIO_SPEED_FREQ_LOW;

        HAL_GPIO_Init(const_cast<GPIO_TypeDef*>(reg()), &gpio);
    }

    /**
     * @brief Configure pin as input
     * @param pull Pull configuration (GPIO_NOPULL, GPIO_PULLUP, GPIO_PULLDOWN)
     */
    static void initInput(uint32_t pull = GPIO_NOPULL)
    {
        enableClock();

        GPIO_InitTypeDef gpio{};
        gpio.Pin  = Pin;
        gpio.Mode = GPIO_MODE_INPUT;
        gpio.Pull = pull;

        HAL_GPIO_Init(const_cast<GPIO_TypeDef*>(reg()), &gpio);
    }

    /**
     * @brief Configure pin as alternate function
     */
    static void initAlternate(uint32_t alternate,
                              uint32_t pull  = GPIO_NOPULL,
                              uint32_t speed = GPIO_SPEED_FREQ_LOW)
    {
        enableClock();

        GPIO_InitTypeDef gpio{};
        gpio.Pin       = Pin;
        gpio.Mode      = GPIO_MODE_AF_PP;
        gpio.Pull      = pull;
        gpio.Speed     = speed;
        gpio.Alternate = alternate;

        HAL_GPIO_Init(reg(), &gpio);
    }

    /* ============================================================
     * Fast I/O operations (zero-cost)
     * ============================================================ */

    /**
     * @brief Set pin high
     */
    static inline void set()
    {
        reg()->BSRR = Pin;
    }

    /**
     * @brief Set pin low
     */
    static inline void reset()
    {
        reg()->BSRR = (Pin << 16);
    }

    /**
     * @brief Toggle pin state (atomic using BSRR)
     */
    static inline void toggle()
    {
        auto* g = reg();
        if (g->ODR & Pin)
            g->BSRR = (Pin << 16);
        else
            g->BSRR = Pin;
    }

    /**
     * @brief Read input pin state
     * @return true if high, false if low
     */
    static inline bool read()
    {
        return (reg()->IDR & Pin) != 0;
    }
};

} // namespace hw