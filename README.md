# ArduPy [![Build Status](https://travis-ci.com/Seeed-Studio/ArduPy.svg?branch=master)](https://travis-ci.com/Seeed-Studio/ArduPy)

## What's Ardupy?  

ArduPy is a combination of Arduino and MicroPython. MicroPython uses the universal Arduino API to control the hardware so that it can be compatible with new platforms quickly. With the help of the aip package manager we provided, you can transform your favorite Arduino library into a MicroPython library. Through ArduPy, you can use Python to verify your ideas, learn python programming as well as micro-controller programming in a more efficient way.

ArduPy consists of two parts, one is the ArduPy Core, and the other part is the Arduino Library Python wrapper.

## What can Ardupy do?
- Ardupy can experience complete python3 on embedded devices with limited resources
- Support for simple file systems
- Support for automatic running of boot.py when reset
- Support serial terminal interaction
- Rich third part library

## Usage
- ### Seeed AruPy plug-in VS Code
    You can get it from the extension store of vs Code.
- ### Guide
    Click [here](http://wiki.seeedstudio.com/Wio-Terminal-ArduPy/) for more information.


## Develop Ardupy
- ### Get all of the source code
    ```
    git clone --recursive https://github.com/Seeed-Studio/ArduPy
    ```
- ### Requirements
    - make and an Unix environment
    - Arduino environment
- ### build
    ```
    cd ArduPy && mkdir build

    COREVER=version
    ```
    ####  version is the version of [ArduinoCore-samd](https://github.com/Seeed-Studio/ArduinoCore-samd)

    - wio terminal
        ```
        cmake ../ -DARDUINO_CORE_PATH=$HOME/.arduino15/packages/Seeeduino/hardware/samd/$COREVER -DTOOLCHAIN=$HOME/.arduino15/packages/Seeeduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin -DBOARD=wio_terminal -DARDUINO_VERIANT=wio_terminal 

        make

        ```
    - arduino zero
        ```
        cmake ../ -DARDUINO_CORE_PATH=$HOME/.arduino15/packages/Seeeduino/hardware/samd/$COREVER -DTOOLCHAIN=$HOME/.arduino15/packages/Seeeduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin -DBOARD=seeeduino_m0 -DARDUINO_VERIANT=arduino_zero 

        make

        ``` 
## Contributing
ArduPy Core is Pyboard-friendly and supports basic hardware operations on the board. We wish to develop the ArduPy into a community-driven software and look forward to your participation. If you want to integrate more useful libraries, please feel free to contact us at Github.