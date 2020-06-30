/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * Development of the code in this file was sponsored by Seeed Studio
 *
 * Author: Hontai Liu (hontai.liu@seeed.cc)
 *
 * Copyright (C) 2020  Seeed Technology Co.,Ltd.
 * The MIT License (MIT)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef __ARDUINO_UTIL_H
#define __ARDUINO_UTIL_H

#include "Arduino.h"
#include "Wire.h"
#include "SPI.h"
#include "ardupy_util.h"

#ifdef __cplusplus
extern "C"
{
#endif
    #define ARDUPY_GET_WIRE 1
    #define ARDUPY_GET_SPI  1
    #define ARDUPY_GET_UART 1
    TwoWire* ardupy_get_wire(int32_t wire);
    SPIClass* ardupy_get_spi(int32_t spi); 
    Uart *ardupy_get_uart(int32_t uart);
#ifdef __cplusplus
}
#endif


#endif