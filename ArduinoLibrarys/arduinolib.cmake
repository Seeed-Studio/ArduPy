cmake_minimum_required(VERSION 3.0)
include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR}/NeoPixel)
include_directories(${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_1602LCD)
include_directories(${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_DHT)
include_directories(${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_DS1307)
include_directories(${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_P9813LED)
include_directories(${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_LCD)
include_directories(${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_LCD/Extensions)
include_directories(${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_LCD/Extensions/Touch_Drivers/4WiresTouch)
include_directories(${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_LCD/Fonts)
include_directories(${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_LCD/Fonts/GFXFF)
include_directories(${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_LCD/Fonts/TrueType)
include_directories(${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_LCD/Fonts/Custom)
include_directories(${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_LCD/TFT_Drivers)
include_directories(${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_LCD/User_Setups)
include_directories(${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_MMA7660)
include_directories(${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_MY9221)
# include_directories(${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_Terminal/src/)
include_directories(${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_TM1637)
include_directories(${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_UltrasonicSensor)

add_source_files(
    ${CMAKE_CURRENT_LIST_DIR}/NeoPixel/esp8266.c
    ${CMAKE_CURRENT_LIST_DIR}/NeoPixel/Adafruit_NeoPixel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_1602LCD/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_DHT/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_DS1307/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_P9813LED/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_MMA7660/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_MY9221/*.cpp
    # ${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_Terminal/src/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_TM1637/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_UltrasonicSensor/*.cpp
)

if ("${BOARD}" STREQUAL "grove_ui_m4")
    add_source_files(
        ${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_LCD/*.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Seeed_Arduino_LCD/Extensions/*.cpp
    )
endif()