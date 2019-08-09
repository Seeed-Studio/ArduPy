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

#include "Arduino.h"
#include <Wire.h>
extern "C"{
#include "py/mperrno.h"
#include "py/obj.h"
#include "shared-bindings/microcontroller/__init__.h"
#include "shared-bindings/util.h"
}
#define has_lock  (*(bool *)self->module)

extern "C" {
    void common_hal_busio_i2c_construct(
        abstract_module_t * self,
        uint32_t pin_scl,
        uint32_t pin_sda,
        uint32_t frequency,
        uint32_t timeout) {
        self->module = m_new_obj(bool);
        has_lock = false;
        Wire.begin();
    }

    bool common_hal_busio_i2c_deinited(abstract_module_t * self) { 
        return false;
    }

    void common_hal_busio_i2c_deinit(abstract_module_t * self) {}

    bool common_hal_busio_i2c_probe(abstract_module_t * self, uint8_t addr) {
        Wire.beginTransmission(addr);
        return Wire.endTransmission() == 0;
    }

    bool common_hal_busio_i2c_try_lock(abstract_module_t * self) {
        bool grabbed_lock = false;
        uint32_t state = MICROPY_BEGIN_ATOMIC_SECTION();
        if (!has_lock) {
            grabbed_lock = true;
            has_lock = true;
        }
        MICROPY_END_ATOMIC_SECTION(state);
        return grabbed_lock;
    }

    bool common_hal_busio_i2c_has_lock(abstract_module_t * self) { return has_lock; }

    void common_hal_busio_i2c_unlock(abstract_module_t * self) { has_lock = false; }

    uint8_t common_hal_busio_i2c_write(
        abstract_module_t * self, 
        uint16_t addr, 
        const uint8_t * data, 
        size_t len, 
        bool transmit_stop_bit) {
        Wire.beginTransmission(addr);
        for (int i = 0; i < len; i++)
            Wire.write(data[i]);
        transmit_stop_bit ? Wire.endTransmission(true) : Wire.endTransmission(false);
        return 0;
    }

    uint8_t common_hal_busio_i2c_read(
        abstract_module_t * self, 
        uint16_t addr, 
        uint8_t * data, 
        size_t len) {
        int time_out_count;
        Wire.beginTransmission(addr);
        Wire.requestFrom(addr, len);
        while (len != Wire.available()) {
            time_out_count++;
            if (time_out_count > 10)
                return MP_ENODEV;
            delay(1);
        }
        for (int i = 0; i < len; i++) {
            data[i] = Wire.read();
        }
        return 0;
    }
} // extern "C"