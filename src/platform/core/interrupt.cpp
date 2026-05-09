#include "interrupt.hpp"

namespace platform
{

static IrqHandler handlers[240] = {};

void register_irq_handler(
    IRQn_Type irq,
    IrqHandler handler
)
{
    handlers[static_cast<int>(irq)] = handler;
}

IrqHandler get_irq_handler(
    IRQn_Type irq
)
{
    return handlers[static_cast<int>(irq)];
}

} // namespace platform