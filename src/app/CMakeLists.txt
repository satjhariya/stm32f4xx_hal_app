add_library(app STATIC
    tasks/led_tasks.cpp
    tasks/console_tasks.cpp
    hw_config/debug_uart.cpp
)

target_include_directories(app PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
add_subdirectory(i3g4250d)

target_link_libraries(app PUBLIC
    hardware
    freertos_kernel
    console
    application_i3g4250d
)