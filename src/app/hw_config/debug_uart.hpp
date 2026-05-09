#pragma once

#include "console.hpp"

#include "uart.hpp"

namespace board
{

extern hardware::Uart DebugUart;

extern console::Console DebugConsole;

void initDebugConsole();

} // namespace board