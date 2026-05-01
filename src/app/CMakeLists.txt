add_library(app STATIC
    main.c
    led/led.c
)

target_include_directories(app PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/led
)

target_link_libraries(app PUBLIC
    platform
)