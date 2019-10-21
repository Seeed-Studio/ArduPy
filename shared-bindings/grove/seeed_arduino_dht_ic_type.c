/**
 * The MIT License (MIT)
 *
 * Author: PowerfulCat (x4495@outlook.com)
 *
 * Copyright (C) 2019  Seeed Technology Co.,Ltd.
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

#include "py/nlr.h"
#include "py/objtype.h"
#include "py/runtime.h"
#include "py/mphal.h"

extern const mp_obj_type_t grove_ic_device_type;

const mp_obj_base_t ic_dht11_obj = { &grove_ic_device_type };
const mp_obj_base_t ic_dht21_obj = { &grove_ic_device_type };
const mp_obj_base_t ic_dht22_obj = { &grove_ic_device_type };

STATIC const mp_rom_map_elem_t ic_device_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_DHT11), MP_ROM_PTR(&ic_dht11_obj) },
    { MP_ROM_QSTR(MP_QSTR_DHT21), MP_ROM_PTR(&ic_dht21_obj) },
    { MP_ROM_QSTR(MP_QSTR_DHT22), MP_ROM_PTR(&ic_dht22_obj) },
};
STATIC MP_DEFINE_CONST_DICT(ic_device_locals_dict, ic_device_locals_dict_table);

STATIC void ic_device_print(const mp_print_t * print, mp_obj_t self_in, mp_print_kind_t kind) {
    if (MP_OBJ_TO_PTR(self_in) == MP_ROM_PTR(&ic_dht11_obj)) {
        mp_printf(print, "%q.%q.%q", MP_QSTR_grove, MP_QSTR_ic, MP_QSTR_DHT11);
    } 
    else if (MP_OBJ_TO_PTR(self_in) == MP_ROM_PTR(&ic_dht21_obj)){
        mp_printf(print, "%q.%q.%q", MP_QSTR_grove, MP_QSTR_ic, MP_QSTR_DHT21);
    }
    else{
        mp_printf(print, "%q.%q.%q", MP_QSTR_grove, MP_QSTR_ic, MP_QSTR_DHT22);
    }
}

const mp_obj_type_t grove_ic_device_type = {
    { &mp_type_type },
    .name = MP_QSTR_ic,
    .print = ic_device_print,
    .locals_dict = (mp_obj_t)&ic_device_locals_dict,
};
