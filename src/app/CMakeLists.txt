add_library(app STATIC
    tasks/led_tasks.cpp
    tasks/console_tasks.cpp
)

target_include_directories(app PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(app PUBLIC
    hardware
    rtos
    console
)