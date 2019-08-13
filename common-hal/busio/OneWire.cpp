/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Scott Shawcroft for Adafruit Industries
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
#include "common-hal/busio/OneWire/OneWire.h"
extern "C"{
#include "py/objtype.h"
#include "shared-bindings/util.h"
}

#define one   (*(OneWire *)self->module)
void * operator new (size_t, void *);

extern "C" {
    void common_hal_busio_onewire_construct(abstract_module_t * self, uint32_t pin) {
        self->module = new (m_new_obj(OneWire))OneWire(pin);
    }

    bool common_hal_busio_onewire_deinited(abstract_module_t * self) {
        return false;
    }

    void common_hal_busio_onewire_deinit(abstract_module_t * self) {}

    bool common_hal_busio_onewire_read_bit(abstract_module_t * self) {
        return one.read_bit() != 0;
    }

    void common_hal_busio_onewire_write_bit(abstract_module_t * self, bool bit) {
        one.write_bit((uint8_t)bit);
    }
    
    result_t common_hal_busio_onewire_reset(abstract_module_t * self) {
        return one.reset() == 0 ? ERROR : SUCCESS;
    }
}// extern "C"