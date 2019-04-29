if (WIN32)
    set(EXT ".exe")
else ()
    set(EXT "")
endif ()

message(STATUS "Check for cross compile toolchain ...")
if(NOT TOOLCHAIN)
    find_path(_TOOLCHAIN arm-none-eabi-gcc${EXT})
    global_set(TOOLCHAIN "${_TOOLCHAIN}")
elseif(NOT "${TOOLCHAIN}" MATCHES "/$")
    global_set(TOOLCHAIN "${TOOLCHAIN}")
endif()

if (NOT TOOLCHAIN)
    message(FATAL_ERROR "TOOLCHAIN must be set, to absolute path of cross_compile-toolchain dist/bin folder.")
endif ()

message(STATUS "Using ${TOOLCHAIN} toolchain")

global_set(CMAKE_C_COMPILER "${TOOLCHAIN}/arm-none-eabi-gcc${EXT}")
global_set(CMAKE_CXX_COMPILER "${TOOLCHAIN}/arm-none-eabi-g++${EXT}")
global_set(CMAKE_LINKER "${TOOLCHAIN}/arm-none-eabi-ld${EXT}")
global_set(CMAKE_AR "${TOOLCHAIN}/arm-none-eabi-ar${EXT}")
global_set(CMAKE_OBJCOPY "${TOOLCHAIN}/arm-none-eabi-objcopy${EXT}")
global_set(CMAKE_SIZE "${TOOLCHAIN}/arm-none-eabi-size${EXT}")
global_set(CMAKE_OBJDUMP "${TOOLCHAIN}/arm-none-eabi-objdump${EXT}")
if (WIN32)
    global_set(CMAKE_MAKE_PROGRAM "${TOOLCHAIN}/mingw32-make${EXT}")
endif ()



global_set(CMAKE_C_LINK_EXECUTABLE
        "<CMAKE_C_COMPILER>   <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>")

global_set(CMAKE_CXX_LINK_EXECUTABLE
        "<CMAKE_CXX_COMPILER>  <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS>  <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>")

get_filename_component(_BIN_DIR "${CMAKE_C_COMPILER}" DIRECTORY)
if (NOT "${TOOLCHAIN}" STREQUAL "${_BIN_DIR}")
    message(FATAL_ERROR "CMAKE_C_COMPILER is not in cross_compile-toolchain dist/bin folder.")
endif ()
