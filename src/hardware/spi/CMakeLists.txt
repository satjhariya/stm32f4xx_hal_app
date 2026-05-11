add_library(hardware_spi STATIC
    spi.cpp
)

target_include_directories(hardware_spi PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(platform PRIVATE
    ${CMAKE_SOURCE_DIR}/external/stm32f4xx_hal_driver/Src/stm32f4xx_hal_spi.c
)

target_link_libraries(hardware_spi PUBLIC
    platform
    hardware_gpio
)