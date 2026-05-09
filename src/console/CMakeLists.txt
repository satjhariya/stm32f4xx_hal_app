add_library(console STATIC
    console.cpp
    console_task.cpp
)

target_include_directories(console PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(console PUBLIC
    hardware_uart
    rtos
)