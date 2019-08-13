/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Damien P. George
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
#include <HardwareSerial.h>
extern "C"{
#include "common-hal/busio/UART.h"
#include "shared-bindings/util.h"
#include "py/runtime.h"
}

#ifndef Console
#define Console  Serial1
#endif
#define module  (*(uart_data_t *)self->module)

typedef struct {
    uint8_t   character_bits;
    uint8_t * buffer;
    uint32_t  baudrate;
    uint32_t  config;
    uint32_t  timeout_ms;
}uart_data_t;

extern "C"{
    // Do-nothing callback needed so that usart_async code will enable rx interrupts.
    // See comment below re usart_async_register_callback()
    static void usart_async_rxc_callback(const struct usart_async_descriptor *const descr) {
        // Nothing needs to be done by us.
    }

    void common_hal_busio_uart_construct(
        abstract_module_t * self,
        uint32_t pin_tx, 
        uint32_t pin_rx, 
        uint32_t baudrate,
        uint32_t bits, 
        uint32_t parity, 
        uint32_t stop, 
        uint32_t timeout,
        uint32_t receiver_buffer_size) {
        uint32_t config;

        #define add_parity(BITS)                        \
        if (parity == PARITY_EVEN){                     \
            add_stop_bit(BITS,E)                        \
        }                                               \
        else if (parity == PARITY_ODD){                 \
            add_stop_bit(BITS,O)                        \
        }                                               \
        else{                                           \
            add_stop_bit(BITS,N)                        \
        }

        #define add_stop_bit(BITS,PARITY)               \
        if (stop == 1){                                 \
            config = SERIAL_ ## BITS ## PARITY ## 1;    \
        }                                               \
        else{                                           \
            config = SERIAL_ ## BITS ## PARITY ## 2;    \
        }

        switch(bits){
        case 7: add_parity(7); break;
        case 8: add_parity(8); break;
        //case 9: add_parity(9); break;
        default: 
            raise_error_because("9 bits per byte is not support.");
            break;
        }
        
        module.baudrate = baudrate;
        module.timeout_ms = timeout * 1000; //second to milisecond
        module.config = config;
        Console.begin(module.baudrate, module.config);
        Console.setTimeout(module.timeout_ms);
    }

    bool common_hal_busio_uart_deinited(abstract_module_t * self) {
        return false;
    }

    void common_hal_busio_uart_deinit(abstract_module_t * self) {
    }

    // Read characters.
    uint32_t common_hal_busio_uart_read(abstract_module_t * self, uint8_t * data, size_t len, int * errcode) {
        return Console.readBytes(data, len);
    }

    // Write characters.
    uint32_t common_hal_busio_uart_write(abstract_module_t * self, const uint8_t * data, size_t len, int * errcode) {
        len = Console.write(data, len);
        errcode[0] = Console.getWriteError();
        Console.clearWriteError();
        return len;
    }

    uint32_t common_hal_busio_uart_get_baudrate(abstract_module_t * self) {
        return module.baudrate;
    }

    uint32_t common_hal_busio_uart_rx_characters_available(abstract_module_t * self) {
        return Console.available();
    }

    void common_hal_busio_uart_set_baudrate(abstract_module_t * self, uint32_t baudrate) {
        Console.begin(
            module.baudrate = baudrate,
            module.config
        );
    }

    void common_hal_busio_uart_clear_rx_buffer(abstract_module_t * self) {
        for (size_t i = Console.available(); i-- > 0;){
            Console.read();
        }
    }

    bool common_hal_busio_uart_ready_to_tx(abstract_module_t * self) {
        return Console.availableForWrite() != 0;
    }
}

