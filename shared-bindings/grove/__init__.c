/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Scott Shawcroft for Adafruit Industries
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

#include "__init__.h"
#include "py/obj.h"
#include "py/runtime.h"

#include "shared-bindings/microcontroller/Pin.h"

extern const mp_obj_type_t grove_led_type;
extern const mp_obj_type_t grove_button_type;
extern const mp_obj_type_t analogio_analogin_type;
extern const mp_obj_type_t analogio_analogout_type;
extern const mp_obj_type_t chainable_led_type;
extern const mp_obj_type_t grove_led_bar_type;

STATIC const mp_rom_map_elem_t grove_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__),                 MP_ROM_QSTR(MP_QSTR_grove) },
    { MP_ROM_QSTR(MP_QSTR_grove_led),                MP_ROM_PTR(&grove_led_type) },
    { MP_ROM_QSTR(MP_QSTR_grove_buzzer),             MP_ROM_PTR(&grove_led_type) },
    { MP_ROM_QSTR(MP_QSTR_grove_relay),              MP_ROM_PTR(&grove_led_type) },
    { MP_ROM_QSTR(MP_QSTR_grove_chainable_led),      MP_ROM_PTR(&chainable_led_type) },
    { MP_ROM_QSTR(MP_QSTR_grove_switch),             MP_ROM_PTR(&grove_button_type) },,
    { MP_ROM_QSTR(MP_QSTR_grove_tilt_switch),        MP_ROM_PTR(&grove_button_type) },
    { MP_ROM_QSTR(MP_QSTR_grove_button),             MP_ROM_PTR(&grove_button_type) },
    { MP_ROM_QSTR(MP_QSTR_grove_flame),              MP_ROM_PTR(&grove_button_type) },
    { MP_ROM_QSTR(MP_QSTR_grove_touch_sensor),       MP_ROM_PTR(&grove_button_type) },
    { MP_ROM_QSTR(MP_QSTR_grove_line_finder),        MP_ROM_PTR(&grove_button_type) },
    { MP_ROM_QSTR(MP_QSTR_grove_hall_sensor),        MP_ROM_PTR(&grove_button_type) },
    { MP_ROM_QSTR(MP_QSTR_grove_temperature_sensor), MP_ROM_PTR(&analogio_analogin_type) },
    { MP_ROM_QSTR(MP_QSTR_grove_water_sensor),       MP_ROM_PTR(&analogio_analogin_type) },
    { MP_ROM_QSTR(MP_QSTR_grove_light_sensor),       MP_ROM_PTR(&analogio_analogin_type) },
    { MP_ROM_QSTR(MP_QSTR_grove_sound_sensor),       MP_ROM_PTR(&analogio_analogin_type) },
    { MP_ROM_QSTR(MP_QSTR_grove_moisture_sensor),    MP_ROM_PTR(&analogio_analogin_type) },
    { MP_ROM_QSTR(MP_QSTR_grove_loudness_sensor),    MP_ROM_PTR(&analogio_analogin_type) },
    { MP_ROM_QSTR(MP_QSTR_grove_led_bar),            MP_ROM_PTR(&grove_led_bar_type) }, 
};

STATIC MP_DEFINE_CONST_DICT(grove_module_globals, grove_module_globals_table);

const mp_obj_module_t grove_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&grove_module_globals,
};
