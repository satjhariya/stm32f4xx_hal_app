# ============================
# FreeRTOS Kernel Library
# ============================

add_library(rtos STATIC
    kernel/tasks.c
    kernel/queue.c
    kernel/list.c
    kernel/timers.c

    kernel/portable/GCC/ARM_CM4F/port.c
    kernel/portable/MemMang/heap_4.c
)

# ============================
# Include directories
# ============================

target_include_directories(rtos PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include                       # FreeRTOSConfig.h
    ${CMAKE_CURRENT_SOURCE_DIR}/kernel/include                # FreeRTOS headers
    ${CMAKE_CURRENT_SOURCE_DIR}/kernel/portable/GCC/ARM_CM4F  # portmacro.h
)

# ============================
# Compile definitions
# ============================

target_compile_definitions(rtos PUBLIC
    USE_FREERTOS
)

# ============================
# Language settings
# ============================

target_compile_features(rtos PUBLIC c_std_11)

# ============================
# (Optional but recommended)
# ============================

# Ensure correct CPU flags propagate if needed
# (Usually already handled by your compiler_flags module)
target_compile_options(rtos PRIVATE
    -Wall
    -Wextra
)

target_link_libraries(rtos PUBLIC
                        mcu
                        cmsis)