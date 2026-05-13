add_library(application_i3g4250d STATIC
    # i3g4250d.cpp
    i3g4250d_port.cpp
    i3g4250d_reg.c
)

target_include_directories(application_i3g4250d PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(application_i3g4250d PUBLIC
    hardware
)