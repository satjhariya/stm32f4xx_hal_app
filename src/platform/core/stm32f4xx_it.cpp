#include "stm32f4xx_hal.h"
#include "interrupt.hpp"

// extern "C"
// void SysTick_Handler(void)
// {
//     HAL_IncTick();
// }

extern "C"
void WWDG_IRQHandler(void)
{
    // ignore for now
}



extern "C"
void USART1_IRQHandler(void)
{
    auto handler =
        platform::get_irq_handler(USART1_IRQn);

    if (handler)
    {
        handler();
    }
}

extern "C"
void USART2_IRQHandler(void)
{
    auto handler =
        platform::get_irq_handler(USART2_IRQn);

    if (handler)
    {
        handler();
    }
}

extern "C"
void USART6_IRQHandler(void)
{
    auto handler =
        platform::get_irq_handler(USART6_IRQn);

    if (handler)
    {
        handler();
    }
}