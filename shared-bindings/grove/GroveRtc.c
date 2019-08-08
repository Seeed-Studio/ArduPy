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

#include "py/mphal.h"
#include "py/nlr.h"
#include "py/objtype.h"
#include "py/runtime.h"
#include "py/obj.h"
#include "shared-bindings/microcontroller/Pin.h"
#include "shared-bindings/util.h"
#include "common-hal/grove/GroveRtc.h"

typedef struct{
    mp_obj_base_t base;
    void *        module;
}rtc_obj_t;

extern const mp_obj_type_t grove_rtc_type;

mp_obj_t rtc_make_new(
    const mp_obj_type_t *type, 
    size_t n_args, 
    size_t n_kw, 
    const mp_obj_t * args) {
    rtc_obj_t     * self = m_new_obj(rtc_obj_t);
    mp_obj_t      * device_type;
    self->base.type = &grove_rtc_type;
    assert_pin_free(&pin_SCL);
    assert_pin_free(&pin_SDA);
    common_hal_rtc_construct(&self->module);
    return (mp_obj_t)self;
}

mp_obj_t rtc_obj_deinit(mp_obj_t self_in) {
    rtc_obj_t * self = (rtc_obj_t *)(self_in);
    common_hal_rtc_deinit(self);
    return mp_const_none;
}

mp_obj_t rtc_obj___exit__(size_t n_args, const mp_obj_t *args) {
    rtc_obj_t * self = (rtc_obj_t *)(args[0]);
    common_hal_rtc_deinit(self);
    return mp_const_none;
}

mp_obj_t rtc_start(mp_obj_t self_in){
    rtc_obj_t * self = (rtc_obj_t *)(self_in);
    common_hal_rtc_start(self->module);
    return mp_const_none;
}

mp_obj_t rtc_stop(mp_obj_t self_in){
    rtc_obj_t * self = (rtc_obj_t *)(self_in);
    common_hal_rtc_stop(self->module);
    return mp_const_none;
}

void rtc_obj_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest){
    extern const mp_obj_type_t grove_datetime_type;
    rtc_obj_t * self = (rtc_obj_t *)self_in;
    datetime_obj_t * time;

    if (dest[0] != MP_OBJ_NULL) {
        switch (attr) {
        case MP_QSTR_datetime:
            time = (datetime_obj_t *)dest[1];
            common_hal_rtc_set_datetime(self->module, & time->data);
            break;
        default:
            generic_method_lookup(self_in, attr, dest);
            break;
        }
        dest[0] = MP_OBJ_NULL;
    } else {
        switch (attr) {
        case MP_QSTR_datetime:
            time = m_new_obj(datetime_obj_t);
            time->base.type = & grove_datetime_type;
            common_hal_rtc_get_datetime(self->module, & time->data);
            dest[0] = (mp_obj_t)time;
            break;
        default:
            generic_method_lookup(self_in, attr, dest);
            break;
        }
    }
}

MP_DEFINE_CONST_FUN_OBJ_1(rtc_deinit_obj, rtc_obj_deinit);
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(rtc_obj___exit___obj, 4, 4, rtc_obj___exit__);
MP_DEFINE_CONST_FUN_OBJ_1(rtc_start_obj, rtc_start);
MP_DEFINE_CONST_FUN_OBJ_1(rtc_stop_obj, rtc_stop);

const mp_rom_map_elem_t rtc_locals_dict_table[] = {
    // instance methods
    { MP_ROM_QSTR(MP_QSTR_deinit),    MP_ROM_PTR(&rtc_deinit_obj) },
    { MP_ROM_QSTR(MP_QSTR___enter__), MP_ROM_PTR(&default___enter___obj) },
    { MP_ROM_QSTR(MP_QSTR___exit__),  MP_ROM_PTR(&rtc_obj___exit___obj) },
    { MP_ROM_QSTR(MP_QSTR_start),     MP_ROM_PTR(&rtc_start_obj) },
    { MP_ROM_QSTR(MP_QSTR_stop),      MP_ROM_PTR(&rtc_stop_obj) },
};

MP_DEFINE_CONST_DICT(rtc_locals_dict, rtc_locals_dict_table);

const mp_obj_type_t grove_rtc_type = {
    {&mp_type_type},
    .name = MP_QSTR_grove_rtc,
    .make_new = rtc_make_new,
    .locals_dict = (mp_obj_t)&rtc_locals_dict,
    .attr = &rtc_obj_attr,
};