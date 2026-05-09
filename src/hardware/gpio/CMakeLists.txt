add_library(hardware_gpio INTERFACE)

target_include_directories(hardware_gpio INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(platform PRIVATE
    ${CMAKE_SOURCE_DIR}/external/stm32f4xx_hal_driver/Src/stm32f4xx_hal_gpio.c
)

target_link_libraries(hardware_gpio INTERFACE
    platform
)