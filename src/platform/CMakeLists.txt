add_library(platform STATIC
    core/startup_stm32f411xe.s
    core/system_stm32f4xx.c
    core/system_clock.c
    # core/stm32f4xx_it.c
)

# HAL as part of platform
target_sources(platform PRIVATE
    ${CMAKE_SOURCE_DIR}/external/stm32f4xx_hal_driver/Src/stm32f4xx_hal.c
    ${CMAKE_SOURCE_DIR}/external/stm32f4xx_hal_driver/Src/stm32f4xx_hal_gpio.c
    ${CMAKE_SOURCE_DIR}/external/stm32f4xx_hal_driver/Src/stm32f4xx_hal_rcc.c
    ${CMAKE_SOURCE_DIR}/external/stm32f4xx_hal_driver/Src/stm32f4xx_hal_cortex.c
)

target_include_directories(platform PUBLIC
    ${CMAKE_SOURCE_DIR}/external/stm32f4xx_hal_driver/Inc
    ${CMAKE_SOURCE_DIR}/external/cmsis/CMSIS/Core/Include
    ${CMAKE_SOURCE_DIR}/external/cmsis_device_f4/Include
    ${CMAKE_SOURCE_DIR}/src/platform/core
    ${CMAKE_SOURCE_DIR}/src/platform/hal
)

target_compile_definitions(platform PUBLIC
    STM32F411xE
    USE_HAL_DRIVER
)

target_link_libraries(platform PUBLIC
    cmsis
    mcu
)