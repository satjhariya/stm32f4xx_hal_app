# ============================================================
# FreeRTOS Kernel Configuration
# ============================================================

set(FREERTOS_PORT GCC_ARM_CM4F CACHE STRING "")

set(FREERTOS_HEAP 4 CACHE STRING "")


# ============================================================
# FreeRTOS Kernel
# ============================================================

add_subdirectory(
    ${CMAKE_SOURCE_DIR}/external/freertos_kernel
)

# ============================================================
# MCU Compile Options
# ============================================================

target_link_libraries(freertos_kernel PUBLIC
    mcu
)

target_link_libraries(freertos_kernel_port PUBLIC
    mcu
)