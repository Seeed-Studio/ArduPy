
set(MICROPYTHON "1")
set(ARM "1")


if (NOT BOARD)
    message(STATUS "BOARD not set!")
endif ()
if (NOT ARDUINO_VERIANT)
    message(STATUS "ARDUINO_VERIANT not set!")
endif ()
# basic config
if (NOT ARDUINO_CORE_PATH)
    message(STATUS "ARDUINO_CORE_PATH not set, you can set it manually. e.g. -DARDUINO_CORE_PATH=/tmp/work/ArduinoCore-samd")
else()
        set(ARDUINO_CMSIS_PATH  ${ARDUINO_CORE_PATH}/../../../tools/CMSIS/4.5.0)
        set(ARDUINO_CMSIS_ATMEL_PATH  ${ARDUINO_CORE_PATH}/../../../tools/CMSIS-Atmel/1.2.1/CMSIS-Atmel/CMSIS/Device/ATMEL)
endif ()

set(ARDUPY_ROOT_PATH ${CMAKE_CURRENT_LIST_DIR}/../..)
set(ARDUPY_LIB_PATH ${CMAKE_CURRENT_LIST_DIR}/lib)
set(ARDUPY_BOARD_PATH  ${CMAKE_CURRENT_LIST_DIR}/boards/${BOARD})
cmake_minimum_required(VERSION 3.0)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/common.cmake)
project(Ardupy C CXX ASM)

# config self use headers
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/macros.internal.cmake)

message("MICROPYTHON = ${MICROPYTHON}")
message("BOARD = ${BOARD}")
message("ARCH = ${ARCH}")
message("ARDUINO_VERIANT = ${ARDUINO_VERIANT}")
message("ARM = ${ARM}")


include_directories(${ARDUPY_ROOT_PATH}/)
include_directories(${ARDUINO_CORE_PATH}/cores/arduino)
include_directories(${ARDUINO_CORE_PATH}/libraries/Wire)
include_directories(${ARDUINO_CORE_PATH}/libraries/SPI)
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
                    ${CMAKE_CURRENT_LIST_DIR}/ardupy_usb.cpp
                    ${CMAKE_CURRENT_LIST_DIR}/ardupy_irq.c
                    )

include(${ARDUPY_BOARD_PATH}/board.cmake)

FILE(GLOB_RECURSE ASSEMBLY_FILES
    "${ARDUINO_CORE_PATH}/cores/arduino/*.s"
    "${ARDUINO_CORE_PATH}/cores/arduino/*.S"
    )
            
SET_PROPERTY(SOURCE ${ASSEMBLY_FILES} PROPERTY LANGUAGE C)
SET_SOURCE_FILES_PROPERTIES(${ASSEMBLY_FILES} PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp")

include(${CMAKE_CURRENT_LIST_DIR}/micropython.cmake)
include_directories(${CMAKE_CURRENT_LIST_DIR})

if("${ARCH}" STREQUAL "samd21")
    include(${CMAKE_CURRENT_LIST_DIR}/cmake/samd21-compile-flags.cmake)
    include(${CMAKE_CURRENT_LIST_DIR}/cmake/samd21-executable.cmake)
elseif("${ARCH}" STREQUAL "samd51")
    include(${CMAKE_CURRENT_LIST_DIR}/cmake/samd51-compile-flags.cmake)
    include(${CMAKE_CURRENT_LIST_DIR}/cmake/samd51-executable.cmake)
else()
    message(FATAL_ERROR, "ARCH not set!")
endif()


message("MICROPYTHON = ${MICROPYTHON}")
message("BOARD = ${BOARD}")
message("ARCH = ${ARCH}")
message("ARDUINO_VERIANT = ${ARDUINO_VERIANT}")
message("ARM = ${ARM}")

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
        set(lib_MICROPYTHON_SRC ${lib_MICROPYTHON_SRC} ${X}) 
endforeach()

message(STATUS  ${lib_MICROPYTHON_SRC})
message(STATUS  ${MICROPYTHON_SRC})


#add_library(micropython STATIC ${SOURCE_FILES} ${BOARD_SRC}  ${lib_MICROPYTHON_SRC}  ${GENHDR}/qstrdefs.generated.h)


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
    DESTINATION Arduino
    FILES_MATCHING PATTERN "*.h*")
    
INSTALL (
    DIRECTORY ${ARDUINO_CORE_PATH}/../../../tools/CMSIS-Atmel
    DIRECTORY ${ARDUINO_CORE_PATH}/../../../tools/CMSIS
    DIRECTORY ${CMAKE_BINARY_DIR}/genhdr
    DESTINATION Arduino/tools
    FILES_MATCHING PATTERN "*.[h|a]*")

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
                        DESTINATION ArduPy/boards/${board})


install(FILES   ${CMAKE_CURRENT_LIST_DIR}/MicroPython/mpy-cross/mpy-cross
                ${CMAKE_CURRENT_LIST_DIR}/MicroPython/tools/mpy-tool.py
                DESTINATION Seeeduino/tools PERMISSIONS OWNER_EXECUTE OWNER_READ
        )

        
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib
              DESTINATION ArduPy
              FILES_MATCHING PATTERN "*.h*"
)

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
