add_subdirectory(gpio)
add_subdirectory(uart)

add_library(hardware INTERFACE)

target_link_libraries(hardware INTERFACE
    hardware_gpio
    hardware_uart
)