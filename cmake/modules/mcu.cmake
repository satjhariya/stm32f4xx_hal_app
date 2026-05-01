add_library(mcu INTERFACE)

target_compile_options(mcu INTERFACE
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
)

target_link_options(mcu INTERFACE
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
)