add_library(compiler_flags INTERFACE)

target_compile_options(compiler_flags INTERFACE
    -ffreestanding
    -fdata-sections
    -ffunction-sections
    -g3
    -Og
    -fno-omit-frame-pointer
)

target_link_options(compiler_flags INTERFACE
    -Wl,--gc-sections
    -specs=nano.specs
    -specs=nosys.specs
    -Wl,-Map=${CMAKE_BINARY_DIR}/output/firmware.map
    -nostartfiles
)

# target_link_options(firmware PRIVATE -nostartfiles) 