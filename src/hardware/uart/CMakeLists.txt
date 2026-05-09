add_library(hardware_uart STATIC
    uart.cpp
    # uart_it.cpp
)

target_include_directories(hardware_uart PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(platform PRIVATE
    ${CMAKE_SOURCE_DIR}/external/stm32f4xx_hal_driver/Src/stm32f4xx_hal_uart.c
)

target_link_libraries(hardware_uart PUBLIC
    platform
)