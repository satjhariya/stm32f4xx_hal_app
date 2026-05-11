add_library(app STATIC
    tasks/led_tasks.cpp
    tasks/console_tasks.cpp
    hw_config/debug_uart.cpp
)

target_include_directories(app PUBLIC
target_include_directories(app PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(app PUBLIC
target_link_libraries(app PUBLIC
    hardware
    freertos_kernel
    console
)