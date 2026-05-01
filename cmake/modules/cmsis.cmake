# Placeholder for CMSIS / HAL integration

add_library(cmsis INTERFACE)

target_include_directories(cmsis INTERFACE
    ${CMAKE_SOURCE_DIR}/external/cmsis/CMSIS/Core/Include
    ${CMAKE_SOURCE_DIR}/external/cmsis_device_f4/Include
)
# Example for future:
# target_include_directories(cmsis INTERFACE external/cmsis/include)