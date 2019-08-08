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

extern const mp_obj_type_t grove_datetime_type;

//MON = 1
//TUE = 2
//..
//SUN = 7
uint32_t get_day_of_week(uint32_t year, uint32_t month, uint32_t day){
    uint32_t y = year % 100;
    uint32_t c = year / 100;
    uint32_t v = (y + y / 4 + c / 4 - 2 * c + 26 * (month + 1) / 10 + day - 1) % 7;
    return v ? v : 7;
}

mp_obj_t datetime_make_new(
    const mp_obj_type_t *type, 
    size_t n_args, 
    size_t n_kw, 
    const mp_obj_t * all_args) {
    datetime_obj_t * self = m_new_obj(datetime_obj_t);
    enum{
        ARG_year,
        ARG_month,
        ARG_day,
        ARG_hour,
        ARG_minute,
        ARG_second,
    };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_year,   MP_ARG_KW_ONLY | MP_ARG_INT, { .u_int = 2000 } },
        { MP_QSTR_month,  MP_ARG_KW_ONLY | MP_ARG_INT, { .u_int = 1 } },
        { MP_QSTR_day,    MP_ARG_KW_ONLY | MP_ARG_INT, { .u_int = 1 } },
        { MP_QSTR_hour,   MP_ARG_KW_ONLY | MP_ARG_INT, { .u_int = 0 } },
        { MP_QSTR_minute, MP_ARG_KW_ONLY | MP_ARG_INT, { .u_int = 0 } },
        { MP_QSTR_second, MP_ARG_KW_ONLY | MP_ARG_INT, { .u_int = 0 } },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all_kw_array(n_args, n_kw, all_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);
    self->base.type = &grove_datetime_type;
    self->data.year = args[ARG_year].u_int;
    self->data.month = args[ARG_month].u_int;
    self->data.day_of_month = args[ARG_day].u_int;
    self->data.hour = args[ARG_hour].u_int;
    self->data.minute = args[ARG_minute].u_int;
    self->data.second = args[ARG_second].u_int;
    self->data.day_of_week = get_day_of_week(
        self->data.year, 
        self->data.month, 
        self->data.day_of_month
    );
    return (mp_obj_t)self;
}

mp_obj_t datetime_obj_deinit(mp_obj_t self_in) {
    
}

mp_obj_t datetime_obj___exit__(size_t n_args, const mp_obj_t *args) {
    
}

void datetime_obj_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest){
    rtc_datetime_t * time = & ((datetime_obj_t *)self_in)->data;
    if (dest[0] != MP_OBJ_NULL) {
        switch (attr) {
        case MP_QSTR_year: 
            time->year = mp_obj_get_int(dest[1]); 
            break;
        case MP_QSTR_month: 
            time->month = mp_obj_get_int(dest[1]); 
            break;
        case MP_QSTR_day: 
            time->day_of_month = mp_obj_get_int(dest[1]); 
            break;
        case MP_QSTR_hour: 
            time->hour = mp_obj_get_int(dest[1]); 
            break;
        case MP_QSTR_minute: 
            time->minute = mp_obj_get_int(dest[1]); 
            break;
        case MP_QSTR_second:
            time->second = mp_obj_get_int(dest[1]); 
            break;
        default:
            generic_method_lookup(self_in, attr, dest);
            break;
        }
        dest[0] = MP_OBJ_NULL;
    } else {
        switch (attr) {
        case MP_QSTR_year: 
            dest[0] = mp_obj_new_int(time->year); 
            break;
        case MP_QSTR_month: 
            dest[0] = mp_obj_new_int(time->month); 
            break;
        case MP_QSTR_day: 
            dest[0] = mp_obj_new_int(time->day_of_month); 
            break;
        case MP_QSTR_hour: 
            dest[0] = mp_obj_new_int(time->hour); 
            break;
        case MP_QSTR_minute: 
            dest[0] = mp_obj_new_int(time->minute); 
            break;
        case MP_QSTR_second: 
            dest[0] = mp_obj_new_int(time->second); 
            break;
        case MP_QSTR_day_of_week: 
            dest[0] = mp_obj_new_int(time->day_of_week);
            break;
        default:
            generic_method_lookup(self_in, attr, dest);
            break;
        }
    }
}

MP_DEFINE_CONST_FUN_OBJ_1(datetime_deinit_obj, datetime_obj_deinit);
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(datetime_obj___exit___obj, 4, 4, datetime_obj___exit__);

const mp_rom_map_elem_t datetime_locals_dict_table[] = {
    // instance methods
    { MP_ROM_QSTR(MP_QSTR_deinit),          MP_ROM_PTR(&datetime_deinit_obj) },
    { MP_ROM_QSTR(MP_QSTR___enter__),       MP_ROM_PTR(&default___enter___obj) },
    { MP_ROM_QSTR(MP_QSTR___exit__),        MP_ROM_PTR(&datetime_obj___exit___obj) },
};

MP_DEFINE_CONST_DICT(datetime_locals_dict, datetime_locals_dict_table);

const mp_obj_type_t grove_datetime_type = {
    {&mp_type_type},
    .name = MP_QSTR_datetime,
    .make_new = datetime_make_new,
    .locals_dict = (mp_obj_t)&datetime_locals_dict,
    .attr = &datetime_obj_attr,
};