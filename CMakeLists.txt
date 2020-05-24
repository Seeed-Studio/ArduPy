
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
        set(ARDUINO_CMSIS_PATH  ${ARDUINO_CORE_PATH}/../../../tools/CMSIS/4.5.0)
        set(ARDUINO_CMSIS_ATMEL_PATH  ${ARDUINO_CORE_PATH}/../../../tools/CMSIS-Atmel/1.2.0/CMSIS/Device/ATMEL)
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
# include_directories(${ARDUINO_CORE_PATH}/cores/arduino/TinyUSB/Adafruit_TinyUSB_Core/tinyusb/src/)
# include_directories(${ARDUINO_CORE_PATH}/cores/arduino/TinyUSB/Adafruit_TinyUSB_Core/)
include_directories(${ARDUINO_CORE_PATH}/libraries/Wire)
include_directories(${ARDUINO_CORE_PATH}/libraries/SPI)
# include_directories(${ARDUINO_CORE_PATH}/libraries/Seeed_Arduino_LCD)
include_directories(${ARDUINO_CORE_PATH}/libraries/Adafruit_ZeroDMA)
include_directories(${ARDUINO_CORE_PATH}/variants/${ARDUINO_VERIANT})

# compile project
add_source_files(${ARDUINO_CORE_PATH}/cores/arduino/*.c 
                    ${ARDUINO_CORE_PATH}/cores/arduino/*.cpp
                    ${ARDUINO_CORE_PATH}/libraries/Wire/*.c
                    ${ARDUINO_CORE_PATH}/libraries/Wire/*.cpp
                    ${ARDUINO_CORE_PATH}/libraries/SPI/*.c
                    ${ARDUINO_CORE_PATH}/libraries/SPI/*.cpp
                    ${ARDUINO_CORE_PATH}/libraries/Adafruit_ZeroDMA/*.cpp
                    ${ARDUINO_CORE_PATH}/variants/${ARDUINO_VERIANT}/*.c
                    ${ARDUINO_CORE_PATH}/variants/${ARDUINO_VERIANT}/*.cpp
                    ${CMAKE_CURRENT_LIST_DIR}/ardupy_loop.cpp
                    )

include(${ARDUPY_BOARD_PATH}/board.cmake)
#include(${CMAKE_CURRENT_LIST_DIR}/ArduinoLibrarys/arduinolib.cmake)

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

if ("${BOARD}" STREQUAL "wio_terminal")      
    include(./cmake/samd51-executable.cmake)
endif()

target_sources(${PROJECT_NAME} PUBLIC ${BOARD_SRC}  ${GENHDR}/qstrdefs.generated.h) 
target_sources(${PROJECT_NAME} PUBLIC ${MICROPYTHON_SRC}  ${GENHDR}/qstrdefs.generated.h) 


find_library (arm_cortexM4lf_math NAMES libarm_cortexM4lf_math.a PATHS ${ARDUINO_CMSIS_PATH}/CMSIS/Lib/GCC)
if(NOT arm_cortexM4lf_math)
  message(FATAL_ERROR "arm_cortexM4lf_math library not found   ${ARDUINO_CMSIS_PATH}/CMSIS/Lib/GCC/libarm_cortexM4lf_math")
endif()


foreach(X ${MICROPYTHON_SRC})
        if ( "${X}" STREQUAL "${CMAKE_CURRENT_LIST_DIR}/MicroPython/py/qstr.c" )
            continue()
        endif ()
        if ( "${X}" STREQUAL "${CMAKE_CURRENT_LIST_DIR}/MicroPython/py/parse.c" )
            continue()
        endif ()
        if ( "${X}" STREQUAL "${CMAKE_CURRENT_LIST_DIR}/MicroPython/py/objmodule.c" )
            continue()
        endif ()      
        # if ( "${X}" STREQUAL "${CMAKE_CURRENT_LIST_DIR}/frozen/_frozen_mpy.c" )
        #     continue()
        # endif ()   
        set(lib_MICROPYTHON_SRC ${lib_MICROPYTHON_SRC} ${X}) 
endforeach()

message(STATUS  ${lib_MICROPYTHON_SRC})
message(STATUS  ${MICROPYTHON_SRC})


add_library(micropython STATIC ${SOURCE_FILES} ${BOARD_SRC}  ${lib_MICROPYTHON_SRC}  ${GENHDR}/qstrdefs.generated.h)
# target_link_libraries(micropython  PRIVATE  arm_cortexM4lf_math)

# set(C_LIB ${CMAKE_BINARY_DIR}/libmicropython_m4.a)

# add_custom_command(TARGET micropython POST_BUILD
#         COMMAND  ${CMAKE_AR}  -x $<TARGET_FILE:micropython>
#         COMMAND  ${CMAKE_AR}  -x ${ARDUINO_CMSIS_PATH}/CMSIS/Lib/GCC/libarm_cortexM4lf_math.a
#         COMMAND  ${CMAKE_AR} -rcs ${C_LIB} *.o  *.obj
#         COMMAND  echo "............................."
#         COMMAND  rm  *.o  *.obj
#         WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#         DEPENDS micropython 
#         )

INSTALL (
    DIRECTORY ${ARDUINO_CORE_PATH}/../../../hardware
    DESTINATION Seeeduino
    FILES_MATCHING PATTERN "*.h*")
    
INSTALL (
    DIRECTORY ${ARDUINO_CORE_PATH}/../../../tools/CMSIS-Atmel
    DIRECTORY ${ARDUINO_CORE_PATH}/../../../tools/CMSIS
    DIRECTORY ${CMAKE_BINARY_DIR}/genhdr
    DESTINATION Seeeduino/tools
    FILES_MATCHING PATTERN "*.h*")

INSTALL (
    DIRECTORY ${MP}/py
    DIRECTORY ${MP}/drivers
    DIRECTORY ${MP}/extmod
    DIRECTORY ${MP}/lib
    DESTINATION ArduPy/MicroPython
    FILES_MATCHING PATTERN "*.h*")


INSTALL (
        DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/shared-bindings
        DESTINATION ArduPy/
        FILES_MATCHING PATTERN "*.h*")
    

install(FILES ${CMAKE_BINARY_DIR}/libmicropython.a  
                ${ARDUINO_CMSIS_PATH}/CMSIS/Lib/GCC/libarm_cortexM4lf_math.a
                ${ARDUINO_CMSIS_PATH}/CMSIS/Lib/GCC/libarm_cortexM0l_math.a
                        DESTINATION ArduPy/lib)


install(FILES   ${CMAKE_CURRENT_LIST_DIR}/MicroPython/mpy-cross/mpy-cross
                ${CMAKE_CURRENT_LIST_DIR}/MicroPython/tools/mpy-tool.py
                DESTINATION Seeeduino/tools PERMISSIONS OWNER_EXECUTE OWNER_READ
        )

# install(DIRECTORY  ${ARDUINO_CORE_PATH}/../../../tools/arm-none-eabi-gcc
#             USE_SOURCE_PERMISSIONS
#             DESTINATION  Seeeduino/tools
#             )

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/boards
              DESTINATION ArduPy
              FILES_MATCHING PATTERN "*.h*"
              )

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/boards
                DESTINATION ArduPy
                FILES_MATCHING PATTERN "*.ld*"
        )


install(FILES ${CMAKE_CURRENT_LIST_DIR}/mpconfigport.h
              ${CMAKE_CURRENT_LIST_DIR}/mpconfigboard_common.h
              ${CMAKE_CURRENT_LIST_DIR}/portmodules.h
            DESTINATION ArduPy)

install(FILES   ${CMAKE_CURRENT_LIST_DIR}/MicroPython/py/qstr.c
                ${CMAKE_CURRENT_LIST_DIR}/MicroPython/py/parse.c
                ${CMAKE_CURRENT_LIST_DIR}/MicroPython/py/objmodule.c
                ${CMAKE_CURRENT_LIST_DIR}/MicroPython/py/makeqstrdata.py
                ${CMAKE_CURRENT_LIST_DIR}/MicroPython/py/makeqstrdefs.py
                ${CMAKE_CURRENT_LIST_DIR}/MicroPython/py/makemoduledefs.py
                ${CMAKE_CURRENT_LIST_DIR}/MicroPython/py/makeversionhdr.py
                DESTINATION ArduPy/MicroPython/py
                PERMISSIONS OWNER_READ)
