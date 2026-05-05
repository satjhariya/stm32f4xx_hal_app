cmake_minimum_required(VERSION 3.20)
project(stm32f411 C ASM)
project(stm32f411 C CXX ASM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXECUTABLE_SUFFIX ".elf")

# -----------------------------
# Output Directory
# -----------------------------
set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/output)
file(MAKE_DIRECTORY ${OUTPUT_DIR})

# -----------------------------
# Modules
# -----------------------------
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

include(cmsis)
include(compiler_flags)
include(mcu)
include(postbuild)

# -----------------------------
# Source tree
# -----------------------------
add_subdirectory(src)

# -----------------------------
# Final firmware target
# -----------------------------
add_executable(${PROJECT_NAME}
    src/app/main.cpp
)

target_sources(${PROJECT_NAME} PRIVATE
    src/platform/core/syscalls.c
    # src/platform/core/stm32f4xx_it.c
)

# -----------------------------
# Link
# -----------------------------
target_link_libraries(${PROJECT_NAME} PRIVATE
    app
    platform
    rtos
    compiler_flags
)

set(CMAKE_BUILD_TYPE Debug)

# -----------------------------
# Linker
# -----------------------------
target_link_options(${PROJECT_NAME} PRIVATE
    -T${CMAKE_SOURCE_DIR}/src/platform/core/stm32f411.ld
    -Wl,-Map=${OUTPUT_DIR}/${PROJECT_NAME}.map
)

# -----------------------------
# Output
# -----------------------------
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)

add_firmware_outputs(${PROJECT_NAME} ${OUTPUT_DIR})