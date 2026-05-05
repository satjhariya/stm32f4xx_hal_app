add_library(app INTERFACE)

target_include_directories(app INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(app INTERFACE
    hardware
    rtos
)