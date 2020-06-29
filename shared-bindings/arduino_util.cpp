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
#include "Arduino.h"
#include "Wire.h"
#include "SPI.h"
#ifdef __cplusplus
extern "C"
{
#endif
    // get wire object by number define by map
    TwoWire *ardupy_get_wire(int32_t wire)
    {
        TwoWire *_wire;
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
            _wire = &Wire4;
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
    // get spi object by number define by map
    SPIClass *ardupy_get_spi(int32_t spi)
    {
        SPIClass *_spi;
        switch (spi)
        {
#if SPI_INTERFACES_COUNT  > 0
        case 0:
            _spi = &SPI;
            break;
#endif
#if SPI_INTERFACES_COUNT  > 1
        case 1:
            _spi = &SPI1;
            break;
#endif
#if SPI_INTERFACES_COUNT  > 2
        case 2:
            _spi = &SPI2;
            break;
#endif
#if SPI_INTERFACES_COUNT  > 3
        case 3:
            _spi = &SPI3;
            break;
            3;
#endif
#if SPI_INTERFACES_COUNT  > 4
        case 4:
            _spi = &SPI4;
            break;
#endif
#if SPI_INTERFACES_COUNT  > 5
        case 5:
            _spi = &SPI5;
            break;
#endif
        default:
            _spi = &SPI;
            break;
        }
        return _spi;
    }

    Uart *ardupy_get_uart(int32_t uart)
    {
        Uart *_uart;
        switch ((uart-1))
        {
#if UART_INTERFACES_COUNT > 0
        case 0:
            _uart = &Serial1;
            break;
#endif
#if UART_INTERFACES_COUNT > 1
        case 1:
            _uart = &Serial2;
            break;
#endif
#if UART_INTERFACES_COUNT > 2
        case 2:
            _uart = &Serial3;
            break;
#endif
#if UART_INTERFACES_COUNT > 3
        case 3:
            _uart = &Serial4;
            break;
            3;
#endif
#if UART_INTERFACES_COUNT > 4
        case 4:
            _uart = &Serial5;
            break;
#endif
        default:
            _uart = &Serial1;
            break;
        }
        return _uart;
    }
#ifdef __cplusplus
}
#endif
