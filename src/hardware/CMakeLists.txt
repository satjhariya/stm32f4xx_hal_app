add_library(hardware INTERFACE)

target_include_directories(hardware INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(hardware INTERFACE
    cmsis
    platform
)