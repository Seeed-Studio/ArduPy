
set(MICROPYTHON "1")
set(ARM "1")


if (NOT BOARD)
    set(BOARD "seeeduino_m0")
endif ()

if (NOT ARDUINO_VERIANT)
    set(ARDUINO_VERIANT "arduino_zero")
endif ()
# basic config
if (NOT ARDUINO_CORE_PATH)
    message(STATUS "ARDUINO_CORE_PATH not set, you can set it manually. e.g. -DARDUINO_CORE_PATH=/tmp/work/ArduinoCore-samd")
else()
    message("ARDUINO = ${ARDUINO_CORE_PATH}")
    if ("${BOARD}" STREQUAL "seeeduino_m0")     
        set(ARDUINO_CMSIS_PATH  ${ARDUINO_CORE_PATH}/../../../tools/CMSIS/4.5.0)
        set(ARDUINO_CMSIS_ATMEL_PATH  ${ARDUINO_CORE_PATH}/../../../tools/CMSIS-Atmel/1.2.0/CMSIS/Device/ATMEL)
    endif()

    if ("${BOARD}" STREQUAL "grove_ui_m4")     
        set(ARDUINO_CMSIS_PATH  ${ARDUINO_CORE_PATH}/../../../../arduino/tools/CMSIS/4.5.0)
        set(ARDUINO_CMSIS_ATMEL_PATH  ${ARDUINO_CORE_PATH}/../../../../arduino/tools/CMSIS-Atmel/1.2.0/CMSIS/Device/ATMEL)
    endif()
endif ()


message("MICROPYTHON = ${MICROPYTHON}")
message("BOARD = ${BOARD}")
message("ARDUINO_VERIANT = ${ARDUINO_VERIANT}")
message("ARM = ${ARM}")


set(ARDUPY_BOARD_PATH  ${CMAKE_CURRENT_LIST_DIR}/boards/${BOARD})
cmake_minimum_required(VERSION 3.0)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/common.cmake)
project(Ardupy C CXX ASM)

# config self use headers
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/macros.internal.cmake)


include_directories(${ARDUINO_CORE_PATH}/cores/arduino)
include_directories(${ARDUINO_CORE_PATH}/libraries/Wire)
include_directories(${ARDUINO_CORE_PATH}/libraries/SPI)
include_directories(${ARDUINO_CORE_PATH}/variants/${ARDUINO_VERIANT})

# compile project
add_source_files(${ARDUINO_CORE_PATH}/cores/arduino/*.c 
                    ${ARDUINO_CORE_PATH}/cores/arduino/*.cpp
                    ${ARDUINO_CORE_PATH}/libraries/Wire/*.c
                    ${ARDUINO_CORE_PATH}/libraries/Wire/*.cpp
                    ${ARDUINO_CORE_PATH}/libraries/SPI/*.c
                    ${ARDUINO_CORE_PATH}/libraries/SPI/*.cpp
                    ${ARDUINO_CORE_PATH}/variants/${ARDUINO_VERIANT}/*.c
                    ${ARDUINO_CORE_PATH}/variants/${ARDUINO_VERIANT}/*.cpp
                    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
                    )


include(${ARDUPY_BOARD_PATH}/board.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/ArduinoLibrarys/arduinolib.cmake)


FILE(GLOB_RECURSE ASSEMBLY_FILES
    "${ARDUINO_CORE_PATH}/cores/arduino/*.s"
    "${ARDUINO_CORE_PATH}/cores/arduino/*.S"
    )
            
SET_PROPERTY(SOURCE ${ASSEMBLY_FILES} PROPERTY LANGUAGE C)
SET_SOURCE_FILES_PROPERTIES(${ASSEMBLY_FILES} PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp")

include(${CMAKE_CURRENT_LIST_DIR}/micropython.cmake)
include_directories(${CMAKE_CURRENT_LIST_DIR})

if ("${BOARD}" STREQUAL "seeeduino_m0")      
    include(./cmake/samd21-executable.cmake)
endif()

if ("${BOARD}" STREQUAL "grove_ui_m4")      
    include(./cmake/samd51-executable.cmake)
endif()

target_sources(${PROJECT_NAME} PUBLIC ${BOARD_SRC}  ${GENHDR}/qstrdefs.generated.h) 
target_sources(${PROJECT_NAME} PUBLIC ${MICROPYTHON_SRC}  ${GENHDR}/qstrdefs.generated.h) 
