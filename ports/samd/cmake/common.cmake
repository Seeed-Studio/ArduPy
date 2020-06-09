cmake_minimum_required(VERSION 3.0)

include(${CMAKE_CURRENT_LIST_DIR}/macros.cmake)

global_set(CMAKE_C_COMPILER_WORKS 1)
global_set(CMAKE_CXX_COMPILER_WORKS 1)

global_set(CMAKE_SYSTEM_NAME "Generic")
if (NOT CMAKE_BUILD_TYPE)
    global_set(CMAKE_BUILD_TYPE Debug)
else ()
    if ((NOT CMAKE_BUILD_TYPE STREQUAL "Debug") AND (NOT CMAKE_BUILD_TYPE STREQUAL "Release"))
        message(FATAL_ERROR "CMAKE_BUILD_TYPE must either be Debug or Release instead of ${CMAKE_BUILD_TYPE}")
    endif ()
endif ()

# - Debug & Release
IF (CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions(-DDEBUG=1)
ENDIF ()


if (NOT SDK_ROOT)
    get_filename_component(_SDK_ROOT ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)
    global_set(SDK_ROOT ${_SDK_ROOT})
endif ()

if(${ARM})
    include(${CMAKE_CURRENT_LIST_DIR}/arm-none-toolchain.cmake)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/fix-9985.cmake)
