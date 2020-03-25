cmake_minimum_required(VERSION 3.0)

set(micropython_CFLAGS 
        ${micropython_CFLAGS}
        -I${ARDUINO_CMSIS_PATH}/CMSIS/Include
        -I${ARDUINO_CMSIS_ATMEL_PATH}
        -I${ARDUINO_CORE_PATH}/libraries/Adafruit_ZeroDMA
)

include_directories(${ARDUPY_BOARD_PATH}/flash)
include_directories(${ARDUPY_BOARD_PATH}/flash/qspi)
include_directories(${ARDUINO_CORE_PATH}/core/arduino/USB)
include_directories(${ARDUINO_CORE_PATH}/libraries/HID)
include_directories(${ARDUINO_CORE_PATH}/libraries/USBHost/src)
include_directories(${ARDUINO_CORE_PATH}/libraries/SAMD_AnalogCorrection/src)
include_directories(${ARDUINO_CORE_PATH}/libraries/Adafruit_ZeroDMA)
include_directories(${ARDUINO_CMSIS_PATH}/CMSIS/Include)
include_directories(${ARDUINO_CORE_PATH}/cores/arduino/Adafruit_TinyUSB_Core)
include_directories(${ARDUINO_CORE_PATH}/cores/arduino/Adafruit_TinyUSB_Core/tinyusb/src)
include_directories(${ARDUINO_CMSIS_ATMEL_PATH})

add_source_files(
        # ${ARDUPY_SUB_PATH}/Seeed_Arduino_LCD/*.cpp
        # ${ARDUPY_SUB_PATH}/GroveUi/src/*.cpp
        ${ARDUINO_CORE_PATH}/core/arduino/USB/*.cpp
        ${ARDUPY_BOARD_PATH}/flash/*.cpp
        ${ARDUPY_BOARD_PATH}/flash/qspi/*.cpp
        ${ARDUINO_CORE_PATH}/libraries/HID/*.c
        ${ARDUINO_CORE_PATH}/libraries/HID/*.cpp
        ${ARDUINO_CORE_PATH}/libraries/USBHost/src/*.c
        ${ARDUINO_CORE_PATH}/libraries/USBHost/src/*.cpp
        ${ARDUINO_CORE_PATH}/libraries/SAMD_AnalogCorrection/src/*.c
        ${ARDUINO_CORE_PATH}/libraries/SAMD_AnalogCorrection/src/*.cpp
        ${ARDUINO_CORE_PATH}/libraries/Adafruit_ZeroDMA/*.cpp
)

set(BOARD_SRC ${BOARD_SRC}  
        ${ARDUPY_BOARD_PATH}/mphalport.c
)
set(BOARD_DEF   
                # -mcpu=cortex-m4 
                # -mthumb 
                # -c 
                # -Os 
                # -w 
                # -std=gnu++11 
                # -ffunction-sections 
                # -fdata-sections 
                # -fno-threadsafe-statics 
                # -nostdlib 
                # --param max-inline-insns-single=500 
                # -fno-rtti 
                # -fno-exceptions 
                # -w 
                # -x 
                # c++ 
                # -E 
                # -CC 
                # -DUSE_GROVE_UI_LCD
                # -DUSE_GROVE_UI_KEYBOARD

                -DF_CPU=120000000L 
                -DARDUINO=10810 
                -DWIO_TERMINAL
                -DDSEEED_GROVE_UI_WIRELESS
                -DARDUINO_ARCH_SAMD 
                -D__SAMD51P19A__ 
                -D__SAMD51__ 
                -DUSB_VID=0x2886 -DUSB_PID=0x802D 
                -DUSBCON 
                -DUSB_CONFIG_POWER=100 
                "-DUSB_MANUFACTURER=\"Seeed Studio\"" 
                "-DUSB_PRODUCT=\"Seeed Wio Terminal\"" 
                # -I/home/the-cat/.arduino15/packages/adafruit/hardware/samd/1.5.3/cores/arduino/Adafruit_TinyUSB_Core 
                # -I/home/the-cat/.arduino15/packages/adafruit/hardware/samd/1.5.3/cores/arduino/Adafruit_TinyUSB_Core/tinyusb/src 
                -D__FPU_PRESENT 
                -DARM_MATH_CM4 
                # -mfloat-abi=hard 
                # -mfpu=fpv4-sp-d16 
                -DENABLE_CACHE 
                # -Os 
                -DVARIANT_QSPI_BAUD_DEFAULT=50000000 
                # -I/home/the-cat/.arduino15/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/ 
                # -I/home/the-cat/.arduino15/packages/arduino/tools/CMSIS-Atmel/1.2.0/CMSIS/Device/ATMEL/ 
                # -I/home/the-cat/.arduino15/packages/adafruit/hardware/samd/1.5.3/cores/arduino 
                # -I/home/the-cat/.arduino15/packages/adafruit/hardware/samd/1.5.3/variants/grove_ui_wireless 
                # a.cpp -o /tmp/arduino_build_636011/preproc/ctags_target_for_gcc_minus_e.cpp
                )
# definitions in macros
add_definitions(${BOARD_DEF})
