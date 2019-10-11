cmake_minimum_required(VERSION 3.0)

set(micropython_CFLAGS 
        ${micropython_CFLAGS}
        -I${ARDUINO_CMSIS_PATH}/CMSIS/Include
        -I${ARDUINO_CMSIS_ATMEL_PATH}
        -I${ARDUINO_CORE_PATH}/libraries/Adafruit_ZeroDMA
)

include_directories(${ARDUINO_CORE_PATH}/libraries/HID)
include_directories(${ARDUINO_CORE_PATH}/libraries/SAMD_AnalogCorrection/src)
include_directories(${ARDUINO_CORE_PATH}/libraries/USBHost/src)
include_directories(${ARDUINO_CORE_PATH}/libraries/Adafruit_ZeroDMA)
include_directories(${ARDUINO_CMSIS_PATH}/CMSIS/Include)
include_directories(${ARDUINO_CORE_PATH}/cores/arduino/Adafruit_TinyUSB_Core)
include_directories(${ARDUINO_CORE_PATH}/cores/arduino/Adafruit_TinyUSB_Core/tinyusb/src)
include_directories(${ARDUINO_CMSIS_ATMEL_PATH})


add_source_files(
        ${ARDUINO_CORE_PATH}/libraries/HID/*.c
        ${ARDUINO_CORE_PATH}/libraries/HID/*.cpp
        ${ARDUINO_CORE_PATH}/libraries/SAMD_AnalogCorrection/src/*.c
        ${ARDUINO_CORE_PATH}/libraries/SAMD_AnalogCorrection/src/*.cpp
        ${ARDUINO_CORE_PATH}/libraries/USBHost/src/*.c
        ${ARDUINO_CORE_PATH}/libraries/USBHost/src/*.cpp
        ${ARDUINO_CORE_PATH}/libraries/Adafruit_ZeroDMA/*.cpp
)

set(BOARD_SRC ${BOARD_SRC}  
        ${ARDUPY_BOARD_PATH}/mphalport.c
)
set(BOARD_DEF   -DF_CPU=120000000L 
                -DARDUINO=10809 
                -DARDUINO_GROVE_UI_WIRELESS 
                -DARDUINO_ARCH_SAMD 
                -D__SAMD51P19A__ 
                -D__SAMD51__
                -DSEEED_GROVE_UI_WIRELESS
                -DUSB_VID=0x2341 
                -DUSB_PID=0x804d 
                -DUSBCON 
                -DUSB_CONFIG_POWER=100
                -D__FPU_PRESENT 
                -DARM_MATH_CM4 
                -DENABLE_CACHE
                -DVARIANT_QSPI_BAUD_DEFAULT=5000000
                -DUSB_MANUFACTURER="Seeed Studio" 
                -DUSB_PRODUCT="Seeed Grove UI Wireles")
# definitions in macros
add_definitions(${BOARD_DEF})
