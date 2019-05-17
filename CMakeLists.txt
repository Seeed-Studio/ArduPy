##TODO Is it better to do this with a macro
set(MICROPYTHON_REGEX "#define MICROPYTHON[ \t]+(.+)")
set(BOARD_REGEX "#define BOARD[ \t]+(.+)")
set(ARDUINO_VERIANT_REGEX "#define ARDUINO_VERIANT[ \t]+(.+)")
set(ARM_REGEX "#define ARM[ \t]+(.+)")

# Read in the line containing the version
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/buildconfig.h" MICROPYTHON REGEX ${MICROPYTHON_REGEX})
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/buildconfig.h" BOARD REGEX ${BOARD_REGEX})
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/buildconfig.h" ARDUINO_VERIANT REGEX ${ARDUINO_VERIANT_REGEX})
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/buildconfig.h" ARM REGEX ${ARM_REGEX})

# Pick out just the version
string(REGEX REPLACE ${MICROPYTHON_REGEX} "\\1" MICROPYTHON "${MICROPYTHON}")
string(REGEX REPLACE ${BOARD_REGEX} "\\1" BOARD "${BOARD}")
string(REGEX REPLACE ${ARDUINO_VERIANT_REGEX} "\\1" ARDUINO_VERIANT "${ARDUINO_VERIANT}")
string(REGEX REPLACE ${ARM_REGEX} "\\1" ARM "${ARM}")

message("MICROPYTHON = ${MICROPYTHON}")
message("BOARD = ${BOARD}")
message("ARDUINO_VERIANT = ${ARDUINO_VERIANT}")
message("ARM = ${ARM}")

# basic config
if (NOT ARDUINO_CORE_PATH)
    message(STATUS "ARDUINO_CORE_PATH not set, you can set it manually. e.g. -DARDUINO_CORE_PATH=/tmp/work/ArduinoCore-samd")
else()
    message("ARDUINO = ${ARDUINO_CORE_PATH}")
    if ("${BOARD}" STREQUAL "seeeduino_m0")     
        set(ARDUINO_CMSIS_PATH  ${ARDUINO_CORE_PATH}/../../../tools/CMSIS/4.5.0)
        set(ARDUINO_CMSIS_ATMEL_PATH  ${ARDUINO_CORE_PATH}/../../../tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL)
    endif()
endif ()

cmake_minimum_required(VERSION 3.0)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/common.cmake)
project(Ardupy C CXX ASM)

# config self use headers
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/macros.internal.cmake)

include(${CMAKE_CURRENT_SOURCE_DIR}/boards/${BOARD}/board.cmake)

header_directories(${ARDUINO_CORE_PATH}/cores/arduino)
header_directories(${ARDUINO_CORE_PATH}/libraries/Wire)
header_directories(${ARDUINO_CORE_PATH}/libraries/SPI)
header_directories(${ARDUINO_CORE_PATH}/variants/${ARDUINO_VERIANT})


# compile project
add_source_files(${ARDUINO_CORE_PATH}/cores/arduino/*.c 
                    ${ARDUINO_CORE_PATH}/cores/arduino/*.cpp
                    ${ARDUINO_CORE_PATH}/cores/arduino/*.s
                    ${ARDUINO_CORE_PATH}/cores/arduino/*.S
                    ${ARDUINO_CORE_PATH}/libraries/Wire/*.c
                    ${ARDUINO_CORE_PATH}/libraries/Wire/*.cpp
                    ${ARDUINO_CORE_PATH}/libraries/SPI/*.c
                    ${ARDUINO_CORE_PATH}/libraries/SPI/*.cpp
                    ${ARDUINO_CORE_PATH}/variants/${ARDUINO_VERIANT}/*.c
                    ${ARDUINO_CORE_PATH}/variants/${ARDUINO_VERIANT}/*.cpp
                    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
                    )

FILE(GLOB_RECURSE ASSEMBLY_FILES
    "${ARDUINO_CORE_PATH}/cores/arduino/*.s"
    "${ARDUINO_CORE_PATH}/cores/arduino/*.S"
    )
            
SET_PROPERTY(SOURCE ${ASSEMBLY_FILES} PROPERTY LANGUAGE C)
SET_SOURCE_FILES_PROPERTIES(${ASSEMBLY_FILES} PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp")


include(${CMAKE_CURRENT_LIST_DIR}/micropython.cmake)
header_directories(${CMAKE_CURRENT_LIST_DIR})

if ("${BOARD}" STREQUAL "seeeduino_m0")      
    include(./cmake/samd21-executable.cmake)
endif()

target_sources(${PROJECT_NAME} PUBLIC ${MICROPYTHON_SRC}  ${GENHDR}/qstrdefs.generated.h) 
