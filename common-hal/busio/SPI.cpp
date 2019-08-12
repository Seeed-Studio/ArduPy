/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Scott Shawcroft
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
#include <SPI.h>
extern "C"{
#include "shared-bindings/util.h"
#include "py/mperrno.h"
#include "py/runtime.h"
}
#define spi  (*(spi_data_t *)self->module)

typedef struct{
    volatile bool has_lock;
    uint8_t       mode;
    uint32_t      freq;
}spi_data_t;

extern "C"{
    void common_hal_busio_spi_construct(
        abstract_module_t * self,
        uint32_t clock,
        uint32_t mosi,
        uint32_t miso) {
        self->module = m_new_obj(spi_data_t);
        spi.has_lock = false;
        spi.mode = SPI_MODE0;
        spi.freq = F_CPU / 2;
        SPI.begin();
        SPI.beginTransaction(SPISettings(spi.freq, MSBFIRST, spi.mode));
    }

    void common_hal_busio_spi_never_reset(abstract_module_t * self) {

    }

    bool common_hal_busio_spi_deinited(abstract_module_t * self) {
        return false;
    }

    void common_hal_busio_spi_deinit(abstract_module_t * self) {

    }

    bool common_hal_busio_spi_configure(
        abstract_module_t * self,
        uint32_t baudrate, 
        uint8_t polarity,
        uint8_t phase, 
        uint8_t bits) {
        spi.freq = (baudrate);
        spi.mode = (polarity << 1) | phase;
        SPI.beginTransaction(SPISettings(spi.freq, MSBFIRST, spi.mode));
        return SUCCESS;
    }

    bool common_hal_busio_spi_try_lock(abstract_module_t * self) {
        return try_lock(&spi.has_lock);
    }

    bool common_hal_busio_spi_has_lock(abstract_module_t * self) {
        return spi.has_lock;
    }

    void common_hal_busio_spi_unlock(abstract_module_t * self) {
        spi.has_lock = false;
    }

    bool common_hal_busio_spi_write(
        abstract_module_t * self,
        const uint8_t * data, 
        size_t len) {
        for (size_t i = 0; i < len; i++){
            SPI.transfer(data[i]);
        }
        return SUCCESS;
    }

    bool common_hal_busio_spi_read(
        abstract_module_t * self,
        uint8_t * data, 
        size_t len, 
        uint8_t write_value) {
        for (size_t i = 0; i < len; i++){
            data[i] = SPI.transfer(write_value);
        }
        return SUCCESS;
    }

    bool common_hal_busio_spi_transfer(
        abstract_module_t * self, 
        uint8_t * data_out,
        uint8_t * data_in,
        size_t len) {
        for (size_t i = 0; i < len; i++){
            data_in[i] = SPI.transfer(data_out[i]);
        }
        return SUCCESS;
    }

    uint32_t common_hal_busio_spi_get_frequency(abstract_module_t * self) {
        return spi.freq;
    }

    uint8_t common_hal_busio_spi_get_phase(abstract_module_t * self) {
        return spi.mode & 1;
    }

    uint8_t common_hal_busio_spi_get_polarity(abstract_module_t * self) {
        return spi.mode >> 1;
    }
}
