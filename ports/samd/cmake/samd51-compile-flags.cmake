add_compile_flags(LD 
        -L${ARDUINO_CMSIS_PATH}/CMSIS/Lib/GCC
        -Os
        -Wl,--gc-sections 
        -save-temps 
        -T ${ARDUPY_BOARD_PATH}/flash_with_bootloader.ld
        -Wl,-Map,${CMAKE_BINARY_DIR}/firmware.map
        )

# C Flags Settings
add_compile_flags(BOTH
        -mcpu=cortex-m4 -mthumb 
        -c 
        -g 
        -w 
        -std=gnu11 
        -ffunction-sections 
        -fdata-sections 
        -nostdlib 
        # --param max-inline-insns-single=500 
        -mfloat-abi=hard 
        -mfpu=fpv4-sp-d16 
        -MMD
        )

add_compile_flags(C -g -std=gnu11)
add_compile_flags(CXX 
                -g
                -std=gnu++11 
                -fno-rtti 
                -fno-exceptions
                -fno-threadsafe-statics
                )

