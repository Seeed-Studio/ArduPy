/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013, 2014 Damien P. George
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

#include <stdint.h>
#include <string.h>

#include "py/mphal.h"
#include "py/nlr.h"
#include "py/objtype.h"
#include "py/runtime.h"

#include "common-hal/digitalio/DigitalInOut.h"
#include "shared-bindings/util.h"
#include "shared-bindings/digitalio/Pull.h"

//| .. currentmodule:: digitalio
//|
//| :class:`GroveButton` -- digital input
//| =========================================================
//|
//| A GroveButton is used to digitally control Input pins.
//|

//| .. class:: GroveButton(pin)
//|
//|   Create a new GroveButton object associated with the pin. Defaults to input
//|
//|   :param ~microcontroller.Pin pin: The pin to control
//|

extern void common_hal_digitalio_digitalinout_switch_to_input(
    digitalio_digitalinout_obj_t *self, 
    digitalio_pull_t pull
);

mp_obj_t digitalio_digitalinout_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args);
mp_obj_t grove_button_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    digitalio_digitalinout_obj_t* self = (digitalio_digitalinout_obj_t *)
        digitalio_digitalinout_make_new(type, n_args, n_kw, args);
    common_hal_digitalio_digitalinout_switch_to_input(self, PULL_NONE);
    return (mp_obj_t)self;
}

//|   .. attribute:: value
//|
//|     The digital logic level of the pin.
//|
mp_obj_t digitalio_digitalinout_obj_get_value(mp_obj_t self_in);

void grove_button_obj_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest) {
    if (dest[0] != MP_OBJ_NULL) {
        generic_method_lookup(self_in, attr, dest);
        dest[0] = MP_OBJ_NULL; // indicate success
    } else {
        switch (attr) {
        case MP_QSTR_value:
            dest[0] = digitalio_digitalinout_obj_get_value(self_in);
            break;
        default:
            generic_method_lookup(self_in, attr, dest);
            break;
        }
    }
}

extern const mp_obj_dict_t digitalio_digitalinout_locals_dict;
const mp_obj_type_t grove_button_type = {
    {&mp_type_type},
    .name = MP_QSTR_grove_button,
    .make_new = grove_button_make_new,
    .locals_dict = (mp_obj_t)&digitalio_digitalinout_locals_dict,
    .attr = grove_button_obj_attr,
};
