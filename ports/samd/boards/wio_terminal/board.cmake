cmake_minimum_required(VERSION 3.0)

set(ARCH "samd51")
set(MACHINE_LCD 1)

set(micropython_CFLAGS 
        ${micropython_CFLAGS}
        -I${ARDUINO_CMSIS_PATH}/CMSIS/Core/Include
        -I${ARDUINO_CMSIS_PATH}/CMSIS/DSP/InClude
        -I${ARDUINO_CMSIS_ATMEL_PATH}
        -I${ARDUINO_CORE_PATH}/libraries/Adafruit_ZeroDMA
)

include_directories(${ARDUPY_LIB_PATH}/flash)
include_directories(${ARDUPY_LIB_PATH}/flash/qspi)
include_directories(${ARDUPY_LIB_PATH}/tinyUSB/src)
include_directories(${ARDUINO_CORE_PATH}/core/arduino/USB)
include_directories(${ARDUINO_CORE_PATH}/libraries/Adafruit_ZeroDMA)
include_directories(${ARDUINO_CMSIS_PATH}/CMSIS/Core/Include)
include_directories(${ARDUINO_CMSIS_PATH}/CMSIS/DSP/Include)
include_directories(${ARDUINO_CORE_PATH}/cores/arduino/TinyUSB)
include_directories(${ARDUINO_CORE_PATH}/cores/arduino/TinyUSB/Adafruit_TinyUSB_ArduinoCore/)
include_directories(${ARDUINO_CORE_PATH}/cores/arduino/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src)
include_directories(${ARDUINO_CMSIS_ATMEL_PATH})
include_directories(${ARDUINO_CORE_PATH}/libraries/Seeed_Arduino_LCD)
include_directories(${ARDUINO_CORE_PATH}/libraries/Seeed_Arduino_LCD/Extensions)
include_directories(${ARDUINO_CORE_PATH}/libraries/Seeed_Arduino_LCD/Extensions/Touch_Drivers/4WiresTouch)
include_directories(${ARDUINO_CORE_PATH}/libraries/Seeed_Arduino_LCD/Fonts)
include_directories(${ARDUINO_CORE_PATH}/libraries/Seeed_Arduino_LCD/Fonts/GFXFF)
include_directories(${ARDUINO_CORE_PATH}/libraries/Seeed_Arduino_LCD/Fonts/TrueType)
include_directories(${ARDUINO_CORE_PATH}/libraries/Seeed_Arduino_LCD/Fonts/Custom)
include_directories(${ARDUINO_CORE_PATH}/libraries/Seeed_Arduino_LCD/TFT_Drivers)
include_directories(${ARDUINO_CORE_PATH}/libraries/Seeed_Arduino_LCD/User_Setups)

add_source_files(
        ${ARDUINO_CORE_PATH}/core/arduino/USB/*.cpp
        ${ARDUINO_CORE_PATH}/libraries/Adafruit_ZeroDMA/*.cpp
        ${ARDUINO_CORE_PATH}/libraries/Seeed_Arduino_LCD/TFT_eSPI.cpp
        ${ARDUINO_CORE_PATH}/libraries/Seeed_Arduino_LCD/TFT_Interface.cpp
        ${ARDUPY_LIB_PATH}/flash/*.cpp
        ${ARDUPY_LIB_PATH}/flash/qspi/*.cpp
        ${ARDUPY_LIB_PATH}/tinyUSB/src/*.cpp
)


set(BOARD_SRC ${BOARD_SRC}  
        ${ARDUPY_BOARD_PATH}/mphalport.c
        ${CMAKE_CURRENT_LIST_DIR}/spi_flash.cpp
)
set(BOARD_DEF   
        -DF_CPU=200000000L 
        -DARDUINO=10810 
        -DWIO_TERMINAL
        -DARDUINO_ARCH_SAMD
        -DLCD_SUPPORT
        -DSEEED_GROVE_UI_WIRELESS
        -DARDUINO_ARCH_SAMD 
        -D__SAMD51P19A__ 
        -D__SAMD51__ 
        -DUSB_VID=0x2886 -DUSB_PID=0x802D 
        -DUSBCON 
        -DUSB_CONFIG_POWER=100 
        -DUSB_MANUFACTURER="Seeed Studio"
        -DUSB_PRODUCT="Seeed Wio Terminal"
        -DUSE_TINYUSB
        -D__FPU_PRESENT 
        -DARM_MATH_CM4 
        -DENABLE_CACHE 
        -Os 
        -DVARIANT_QSPI_BAUD_DEFAULT=50000000 
        )
# definitions in macros
add_definitions(${BOARD_DEF})
