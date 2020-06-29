/**
 * The MIT License (MIT)
 *
 * Author: Hongtai Liu (lht856@foxmail.com)
 *
 * Copyright (C) 2020  Seeed Technology Co.,Ltd.
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
#include <Arduino.h>
/*wrapper for Serial opration*/
extern "C"
{
#include "py/objtype.h"
#include "shared-bindings/util.h"
}

#define uart (*(Uart *)self->module)
void *operator new(size_t, void *);

extern "C"
{
    void common_hal_uart_construct(abstract_module_t *self)
    {
        //TODO: Get serial  according to parameters.
        self->module = &Serial1;
        //TODO: Set serial port according to parameters.
        uart.begin(115200);
    }
    void common_hal_uart_deinit(abstract_module_t *self)
    {
        //close serial
        uart.end();
    }
    size_t common_hal_uart_read_bytes(abstract_module_t *self, void *buf_in, mp_uint_t size)
    {
        //read Serial Bytes
        return uart.readBytes((uint8_t *)buf_in, size);
    }
    size_t common_hal_uart_write_bytes(abstract_module_t *self, const void *buf_in, mp_uint_t size)
    {
        //write Serial Bytes
        return uart.write((uint8_t *)buf_in, size);
    }
    size_t common_hal_uart_get_buffered_data_len(abstract_module_t *self, size_t * size)
    {
        //retrun available
        *size = uart.available();
        return *size;
    }
}
