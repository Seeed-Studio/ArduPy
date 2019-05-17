cmake_minimum_required(VERSION 3.0)

include(${CMAKE_SOURCE_DIR}/cmake/macros.cmake)


set(micropython_CFLAGS 
        ${micropython_CFLAGS}
        -I${ARDUINO_CMSIS_PATH}/CMSIS/Include
        -I${ARDUINO_CMSIS_ATMEL_PATH}
)

header_directories(${ARDUINO_CORE_PATH}/libraries/HID)
header_directories(${ARDUINO_CORE_PATH}/libraries/I2S/src)
header_directories(${ARDUINO_CORE_PATH}/libraries/SAMD_AnalogCorrection/src)
header_directories(${ARDUINO_CORE_PATH}/libraries/USBHost/src)
header_directories(${ARDUINO_CMSIS_PATH}/CMSIS/Include)
header_directories(${ARDUINO_CMSIS_ATMEL_PATH})

add_source_files(
        ${ARDUINO_CORE_PATH}/libraries/HID/*.c
        ${ARDUINO_CORE_PATH}/libraries/HID/*.cpp
        ${ARDUINO_CORE_PATH}/libraries/I2S/src/*.c
        ${ARDUINO_CORE_PATH}/libraries/I2S/src/*.cpp
        ${ARDUINO_CORE_PATH}/libraries/SAMD_AnalogCorrection/src/*.c
        ${ARDUINO_CORE_PATH}/libraries/SAMD_AnalogCorrection/src/*.cpp
        ${ARDUINO_CORE_PATH}/libraries/USBHost/src/*.c
        ${ARDUINO_CORE_PATH}/libraries/USBHost/src/*.cpp
)
# definitions in macros
add_definitions(-DF_CPU=48000000L 
                -DARDUINO=10809 
                -DARDUINO_SAMD_ZERO 
                -DARDUINO_ARCH_SAMD 
                -D__SAMD21G18A__ 
                -DUSB_VID=0x2341 
                -DUSB_PID=0x804d 
                -DUSBCON 
                -DSEEEDUINO_MO
                -DUSB_MANUFACTURER="Arduino LLC" 
                -DUSB_PRODUCT="Arduino Zero")
