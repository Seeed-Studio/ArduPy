### This file is used for build example projects.

# basic config
if (NOT ARDUINO_CORE_PATH)
    message(STATUS "ARDUINO_CORE_PATH not set, you can set it manually. e.g. -DARDUINO_CORE_PATH=/tmp/work/ArduinoCore-samd")
else()
    message("ARDUINO = ${ARDUINO_CORE_PATH}")
    set(ARDUINO_CMSIS_PATH  ${ARDUINO_CORE_PATH}/../../../tools/CMSIS/4.5.0)
    set(ARDUINO_CMSIS_ATMEL_PATH  ${ARDUINO_CORE_PATH}/../../../tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL)
endif ()

if (NOT BOARD)
    message(STATUS "BOARD not set, you can set it manually. e.g. -DBOARD=arduino_zero")
else()
    message("BOARD = ${BOARD}")
endif ()



cmake_minimum_required(VERSION 3.0)
include(./cmake/common.cmake)
if (MICROPYTHON)
    project(Grovepy C CXX ASM)
else()
    project(Arduino C CXX ASM)
endif()
# config self use headers
include(./cmake/macros.internal.cmake)




header_directories(${ARDUINO_CORE_PATH}/cores/arduino)
header_directories(${ARDUINO_CORE_PATH}/libraries/HID)
header_directories(${ARDUINO_CORE_PATH}/libraries/I2S/src)
header_directories(${ARDUINO_CORE_PATH}/libraries/SAMD_AnalogCorrection/src)
header_directories(${ARDUINO_CORE_PATH}/libraries/USBHost/src)
header_directories(${ARDUINO_CORE_PATH}/libraries/Wire)
header_directories(${ARDUINO_CORE_PATH}/variants/${BOARD})
header_directories(${ARDUINO_CMSIS_PATH}/CMSIS/Include)
header_directories(${ARDUINO_CMSIS_ATMEL_PATH})

# compile project
add_source_files(${ARDUINO_CORE_PATH}/cores/arduino/*.c 
                    ${ARDUINO_CORE_PATH}/cores/arduino/*.cpp
                    ${ARDUINO_CORE_PATH}/cores/arduino/*.s
                    ${ARDUINO_CORE_PATH}/cores/arduino/*.S
                    ${ARDUINO_CORE_PATH}/libraries/HID/*.c
                    ${ARDUINO_CORE_PATH}/libraries/HID/*.cpp
                    ${ARDUINO_CORE_PATH}/libraries/I2S/src/*.c
                    ${ARDUINO_CORE_PATH}/libraries/I2S/src/*.cpp
                    ${ARDUINO_CORE_PATH}/libraries/SAMD_AnalogCorrection/src/*.c
                    ${ARDUINO_CORE_PATH}/libraries/SAMD_AnalogCorrection/src/*.cpp
                    ${ARDUINO_CORE_PATH}/libraries/USBHost/src/*.c
                    ${ARDUINO_CORE_PATH}/libraries/USBHost/src/*.cpp
                    ${ARDUINO_CORE_PATH}/libraries/Wire/*.c
                    ${ARDUINO_CORE_PATH}/libraries/Wire/*.cpp
                    ${ARDUINO_CORE_PATH}/variants/${BOARD}/*.c
                    ${ARDUINO_CORE_PATH}/variants/${BOARD}/*.cpp
                    )
FILE(GLOB_RECURSE ASSEMBLY_FILES
    "${ARDUINO_CORE_PATH}/cores/arduino/*.s"
    "${ARDUINO_CORE_PATH}/cores/arduino/*.S"
    )
            
SET_PROPERTY(SOURCE ${ASSEMBLY_FILES} PROPERTY LANGUAGE C)
SET_SOURCE_FILES_PROPERTIES(${ASSEMBLY_FILES} PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp")


if (MICROPYTHON)
    include(${CMAKE_CURRENT_LIST_DIR}/micropython.cmake)
    header_directories(${CMAKE_CURRENT_LIST_DIR})
    add_source_files(examples/Grovepy/*.ino)
    FILE(GLOB_RECURSE PROJ_LIB_SRC_INO
        "examples/Grovepy/*.ino"
    )
else()
    add_source_files(examples/Blink/*.ino)
    FILE(GLOB_RECURSE PROJ_LIB_SRC_INO
        "examples/Blink/*.ino"
    )
endif()





SET_PROPERTY(SOURCE ${PROJ_LIB_SRC_INO} PROPERTY LANGUAGE CXX)
SET_SOURCE_FILES_PROPERTIES(${PROJ_LIB_SRC_INO} PROPERTIES COMPILE_FLAGS "-x c++")
      

include(./cmake/executable.cmake)

if (MICROPYTHON)
    target_sources(${PROJECT_NAME} PUBLIC ${MICROPYTHON_SRC}  ${GENHDR}/qstrdefs.generated.h) 
endif()
