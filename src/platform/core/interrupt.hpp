#ifndef PLATFORM_INTERRUPT_HPP
#define PLATFORM_INTERRUPT_HPP

#include "stm32f4xx.h"

namespace platform
{

using IrqHandler = void(*)();

void register_irq_handler(
    IRQn_Type irq,
    IrqHandler handler
);

IrqHandler get_irq_handler(
    IRQn_Type irq
);

} // namespace platform

#endif