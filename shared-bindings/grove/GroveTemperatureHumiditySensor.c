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

#include "py/runtime.h"
#include "shared-bindings/microcontroller/Pin.h"
#include "shared-bindings/util.h"

void common_hal_dht_construct(
    abstract_module_t * self, 
    uint32_t pin_ctrl,
    mp_obj_t type);
void common_hal_dht_deinit(abstract_module_t * self);
float common_hal_dht_get_humidity(abstract_module_t * self);
float common_hal_dht_get_temperature(abstract_module_t * self);

extern const mp_obj_type_t grove_dht_type;

m_generic_make(dht) {
    abstract_module_t * self = new_abstruct_module(type);
    mcu_pin_obj_t     * pin_ctrl;
    mp_obj_t          * device_type;
    pin_ctrl = (mcu_pin_obj_t *)(args[0]);
    device_type = (mp_obj_t *)(args[1]);
    assert_pin(args[0], false);
    assert_pin_free(pin_ctrl);
    common_hal_dht_construct(self, pin_ctrl->number, device_type);
    return self;
}

void dht_obj_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest){
    abstract_module_t * self = (abstract_module_t *)(self_in);
    if (dest[0] == MP_OBJ_NULL) {
        if (attr == MP_QSTR_humidity){
            dest[0] =  mp_obj_new_float(common_hal_dht_get_humidity(self));
            return;
        }
        else if (attr == MP_QSTR_temperature){
            dest[0] = mp_obj_new_float(common_hal_dht_get_temperature(self));
            return;
        }
    }
    generic_method_lookup(self_in, attr, dest);
}

const mp_rom_map_elem_t dht_locals_dict_table[] = {
    // instance methods
    { MP_ROM_QSTR(MP_QSTR_deinit),          MP_ROM_PTR(&dht_deinit_obj) },
    { MP_ROM_QSTR(MP_QSTR___enter__),       MP_ROM_PTR(&default___enter___obj) },
    { MP_ROM_QSTR(MP_QSTR___exit__),        MP_ROM_PTR(&dht_obj___exit___obj) },
};

MP_DEFINE_CONST_DICT(dht_locals_dict, dht_locals_dict_table);

const mp_obj_type_t grove_dht_type = {
    {&mp_type_type},
    .name = MP_QSTR_grove_temperature_humidity_sensor,
    .make_new = dht_make_new,
    .locals_dict = (mp_obj_t)&dht_locals_dict,
    .attr = &dht_obj_attr,
};