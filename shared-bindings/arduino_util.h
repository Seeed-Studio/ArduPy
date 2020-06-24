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
#ifdef __cplusplus
extern "C"
{
#endif
    TwoWire *getWire(int32_t wire)
    {
        TwoWire * _wire;
        switch (wire)
        {
#if WIRE_INTERFACES_COUNT > 0
        case 0:
            _wire = &Wire;
            break;
#endif
#if WIRE_INTERFACES_COUNT > 1
        case 1:
            _wire = &Wire1;
            break;
#endif
#if WIRE_INTERFACES_COUNT > 2
        case 2:
            _wire = &Wire2;
            break;
#endif
#if WIRE_INTERFACES_COUNT > 3
        case 3:
            _wire = &Wire3;
            break;
            3;
#endif
#if WIRE_INTERFACES_COUNT > 4
        case 4:
            _wire = &Wire;
            break;
#endif
#if WIRE_INTERFACES_COUNT > 5
        case 5:
            _wire = &Wire5;
            break;
#endif
        default:
            _wire = &Wire;
            break;
        }
        return _wire;
    }
#ifdef __cplusplus
}
#endif
#endif