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

#include "py/mphal.h"
#include "py/nlr.h"
#include "py/objtype.h"
#include "py/runtime.h"
#include "py/obj.h"
#include "shared-bindings/microcontroller/Pin.h"
#include "shared-bindings/util.h"
#include "common-hal/microcontroller/Pin.h"

typedef struct{
    mp_obj_base_t base;
    void *        module;
}dht_obj_t;

void common_hal_dht_construct(
    void ** self, 
    const mcu_pin_obj_t * pin_ctrl,
    mp_obj_t type);
void common_hal_dht_deinit(void *self);
void common_hal_dht_get_humidity(void *self, float * value);
void common_hal_dht_get_temperature(void *self, float * value);

extern const mp_obj_type_t grove_dht_type;

mp_obj_t dht_make_new(
    const mp_obj_type_t *type, 
    size_t n_args, 
    size_t n_kw, 
    const mp_obj_t * args) {
    dht_obj_t     * self = m_new_obj(dht_obj_t);
    mcu_pin_obj_t * pin_ctrl;
    mp_obj_t      * device_type;
    assert_pin(args[0], false);
    self->base.type = &grove_dht_type;
    pin_ctrl = (mcu_pin_obj_t *)(args[0]);
    device_type = (mp_obj_t *)(args[1]);
    assert_pin_free(pin_ctrl);
    common_hal_dht_construct(&self->module, pin_ctrl, device_type);
    return (mp_obj_t)self;
}

mp_obj_t dht_obj_deinit(mp_obj_t self_in) {
    dht_obj_t *self = (dht_obj_t *)(self_in);
    common_hal_dht_deinit(self);
    return mp_const_none;
}

mp_obj_t dht_obj___exit__(size_t n_args, const mp_obj_t *args) {
    dht_obj_t *self = (dht_obj_t *)(args[0]);
    common_hal_dht_deinit(self);
    return mp_const_none;
}

mp_obj_t dht_get_humidity(mp_obj_t self_in){
    dht_obj_t *self = (dht_obj_t *)(self_in);
    float value;
    common_hal_dht_get_humidity(self->module, &value);
    return mp_obj_new_float(value);
}

mp_obj_t dht_get_temperature(mp_obj_t self_in){
    dht_obj_t *self = (dht_obj_t *)(self_in);
    float value;
    common_hal_dht_get_temperature(self->module,  &value);
    return mp_obj_new_float(value);
}
void dht_obj_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest){
    if (dest[0] != MP_OBJ_NULL) {
        generic_method_lookup(self_in, attr, dest);
    } else {
        switch (attr) {
        case MP_QSTR_humidity:
            dest[0] = dht_get_humidity(self_in);
            break;
        case MP_QSTR_temperature:
            dest[0] = dht_get_temperature(self_in);
            break;
        default:
            generic_method_lookup(self_in, attr, dest);
            break;
        }
    }
}

MP_DEFINE_CONST_FUN_OBJ_1(dht_deinit_obj, dht_obj_deinit);
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(dht_obj___exit___obj, 4, 4, dht_obj___exit__);

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