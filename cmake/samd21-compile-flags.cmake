add_compile_flags(LD 
        -L${ARDUINO_CMSIS_PATH}/CMSIS/Lib/GCC
        -Os 
        -Wl,--gc-sections 
        -save-temps 
        -T ${ARDUINO_CORE_PATH}/variants/${ARDUINO_VERIANT}/linker_scripts/gcc/flash_with_bootloader.ld
        -Wl,-Map,${CMAKE_BINARY_DIR}/firmware.map
        )

# C Flags Settings
add_compile_flags(BOTH
            -mcpu=cortex-m0plus 
            -mthumb 
            -c 
            -g 
            -Os 
            -w 
            -ffunction-sections 
            -fdata-sections
            -nostdlib  
            --param max-inline-insns-single=500
            -MMD
        )

add_compile_flags(C -std=gnu11)
add_compile_flags(CXX 
                -std=gnu++11 
                -fno-rtti 
                -fno-exceptions
                -fno-threadsafe-statics
                )

