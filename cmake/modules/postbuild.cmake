# -----------------------------
# Generate BIN + HEX
# -----------------------------
function(add_firmware_outputs TARGET OUTPUT_DIR)

    add_custom_command(TARGET ${TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIR}

        COMMAND arm-none-eabi-objcopy -O binary
            $<TARGET_FILE:${TARGET}>
            ${OUTPUT_DIR}/${TARGET}.bin

        COMMAND arm-none-eabi-objcopy -O ihex
            $<TARGET_FILE:${TARGET}>
            ${OUTPUT_DIR}/${TARGET}.hex

        COMMAND ${CMAKE_OBJDUMP}
            -h
            -S
            $<TARGET_FILE:${TARGET}>
            > ${OUTPUT_DIR}/${TARGET}.lst

        COMMENT "Generating BIN and HEX in output directory"
    )

endfunction()

# -----------------------------
# Flash Target
# -----------------------------
function(add_run_target TARGET OUTPUT_DIR)

    add_custom_target(run
        COMMAND openocd
            -f interface/stlink.cfg
            -f target/stm32f4x.cfg
            -c "program ${OUTPUT_DIR}/${TARGET}.elf verify reset exit"

        DEPENDS ${TARGET}
        COMMENT "Flashing firmware"
    )

endfunction()

# -----------------------------
# Clean All
# -----------------------------
function(add_clean_all_target OUTPUT_DIR)

    add_custom_target(clean-all
        COMMAND ${CMAKE_COMMAND} -E rm -rf ${OUTPUT_DIR}
        COMMENT "Cleaning output directory"
    )

endfunction()

# -----------------------------
# All-in-One
# -----------------------------
function(add_all_target TARGET)

    add_custom_target(all-run
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target run
        COMMENT "Clean + Build + Run"
    )

endfunction()