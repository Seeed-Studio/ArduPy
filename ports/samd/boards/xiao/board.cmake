cmake_minimum_required(VERSION 3.0)

set(ARCH "samd21")

set(micropython_CFLAGS 
        ${micropython_CFLAGS}
        -I${ARDUINO_CMSIS_PATH}/CMSIS/Core/Include
        -I${ARDUINO_CMSIS_PATH}/CMSIS/DSP/InClude
        -I${ARDUINO_CMSIS_ATMEL_PATH}
)

include_directories(${ARDUINO_CMSIS_PATH}/CMSIS/Core/Include)
include_directories(${ARDUINO_CMSIS_PATH}/CMSIS/DSP/Include)
include_directories(${ARDUPY_LIB_PATH}/tinyUSB/src)
include_directories(${ARDUPY_LIB_PATH}/asf4/hal/include)
include_directories(${ARDUPY_LIB_PATH}/asf4/hal/utils/include)
include_directories(${ARDUPY_LIB_PATH}/asf4/hpl/nvmctrl)
include_directories(${ARDUPY_LIB_PATH}/asf4/hpl/pm)
include_directories(${ARDUPY_LIB_PATH}/asf4/samd21a/include)
include_directories(${ARDUPY_LIB_PATH}/asf4/hri)
include_directories(${ARDUPY_LIB_PATH}/asf4/config)
include_directories(${ARDUINO_CORE_PATH}/core/arduino/USB)
include_directories(${ARDUINO_CORE_PATH}/cores/arduino/TinyUSB)
include_directories(${ARDUINO_CORE_PATH}/cores/arduino/TinyUSB/Adafruit_TinyUSB_ArduinoCore/)
include_directories(${ARDUINO_CORE_PATH}/cores/arduino/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src)


add_source_files(
        ${ARDUINO_CORE_PATH}/cores/arduino/*.s
        ${ARDUINO_CORE_PATH}/cores/arduino/*.S
        ${ARDUPY_LIB_PATH}/tinyUSB/src/*.cpp
        ${ARDUPY_LIB_PATH}/asf4/hal/src/hal_flash.c
        ${ARDUPY_LIB_PATH}/asf4/hpl/nvmctrl/hpl_nvmctrl.c
        ${ARDUPY_LIB_PATH}/asf4/hal/utils/src/utils_assert.c
)

set(BOARD_SRC ${BOARD_SRC}  
        ${ARDUPY_BOARD_PATH}/mphalport.c
)
set(BOARD_DEF   -DF_CPU=48000000L 
                -DARDUINO=10809 
                -DARDUINO_SEEED_XIAO_M0
                -DARDUINO_ARCH_SAMD 
                -D__SAMD21G18A__ 
                -DUSB_VID=0x2886
		-DUSB_PID=0x802F 
                -DUSBCON 
                -DSEEEDUINO_MO
                -DUSB_CONFIG_POWER=100 
                -DUSB_MANUFACTURER="Seeed"
                -DUSB_PRODUCT="Seeed XIAO M0"
                -DUSE_TINYUSB
                -Os 
                )
# definitions in macros
add_definitions(${BOARD_DEF})


