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

#include "py/mphal.h"
#include "py/nlr.h"
#include "py/objtype.h"
#include "py/runtime.h"

#include "shared-bindings/microcontroller/Pin.h"
#include "shared-bindings/util.h"
#include "common-hal/grove/GroveChainableLed.h"

mp_obj_t chainable_led_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *all_args) {
    chainable_led_obj_t *self = m_new_obj(chainable_led_obj_t);
    self->base.type = &chainable_led_type;
    enum { ARG_scl, ARG_sda, ARG_led_numbers };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_scl,         MP_ARG_REQUIRED | MP_ARG_OBJ },
        { MP_QSTR_sda,         MP_ARG_REQUIRED | MP_ARG_OBJ },
        { MP_QSTR_led_numbers, MP_ARG_INT },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all_kw_array(n_args, n_kw, all_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);
    assert_pin(args[ARG_scl].u_obj, false);
    assert_pin(args[ARG_sda].u_obj, false);
    mcu_pin_obj_t* scl = MP_OBJ_TO_PTR(args[ARG_scl].u_obj);
    mcu_pin_obj_t* sda = MP_OBJ_TO_PTR(args[ARG_sda].u_obj);
    assert_pin_free(scl);
    assert_pin_free(sda);
    common_hal_chainable_led_construct(self, scl, sda);
    self->number_of_leds = args[ARG_led_numbers].u_int;
    self->led = m_new(chainable_led_rgb_t, self->number_of_leds);
    return (mp_obj_t)self;
}

mp_obj_t chainable_led_obj_deinit(mp_obj_t self_in) {
    chainable_led_obj_t *self = MP_OBJ_TO_PTR(self_in);
    common_hal_chainable_led_deinit(self);
    return mp_const_none;
}

mp_obj_t chainable_led_obj___exit__(size_t n_args, const mp_obj_t *args) {
    common_hal_chainable_led_deinit(args[0]);
    return mp_const_none;
}

mp_obj_t chainable_led_set_rgb(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args){
    chainable_led_obj_t *self = MP_OBJ_TO_PTR(pos_args[0]);
    enum { ARG_index, ARG_r, ARG_g, ARG_b,  };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_index, MP_ARG_INT, { .u_int = 0 } },
        { MP_QSTR_r,     MP_ARG_INT, { .u_int = 0 } },
        { MP_QSTR_g,     MP_ARG_INT, { .u_int = 0 } },
        { MP_QSTR_b,     MP_ARG_INT, { .u_int = 0 } },
    };

    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    chainable_led_rgb_t value;
    mp_arg_parse_all(n_args - 1, pos_args + 1, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);
    raise_error_if(args[ARG_index].u_int >= self->number_of_leds || args[ARG_index].u_int < 0, "The 1st argument 'index' can't larger equal than total count of led.");
    raise_error_if(args[ARG_r].u_int >= 256 || args[ARG_r].u_int < 0, "The 2nd argument 'r' can't larger equal than 256 or less than 0.");
    raise_error_if(args[ARG_g].u_int >= 256 || args[ARG_r].u_int < 0, "The 3rd argument 'g' can't larger equal than 256 or less than 0.");
    raise_error_if(args[ARG_b].u_int >= 256 || args[ARG_r].u_int < 0, "The 4th argument 'b' can't larger equal than 256 or less than 0.");
    value.r = args[ARG_r].u_int;
    value.g = args[ARG_g].u_int;
    value.b = args[ARG_b].u_int;
    common_hal_chainable_led_set_rgb(self, args[ARG_index].u_int, value);
    return mp_const_none;
}

mp_obj_t chainable_led_set_hsb(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args){
    chainable_led_obj_t *self = MP_OBJ_TO_PTR(pos_args[0]);
    chainable_led_hsb_t value;
    mp_int_t index;
    index   = mp_obj_get_int(pos_args[1]);
    value.h = mp_obj_get_float(pos_args[2]);
    value.s = mp_obj_get_float(pos_args[3]);
    value.b = mp_obj_get_float(pos_args[4]);
    raise_error_if(index >= self->number_of_leds, "The 1st argument 'index' can't larger equal than total count of led.");
    raise_error_if(value.h > 1 || value.h < 0,    "The 2nd argument 'h' can't larger than 1.0f or less than 0.0f.");
    raise_error_if(value.s > 1 || value.s < 0,    "The 3rd argument 's' can't larger than 1.0f or less than 0.0f.");
    raise_error_if(value.b > 1 || value.b < 0,    "The 4th argument 'b' can't larger than 1.0f or less than 0.0f.");
    common_hal_chainable_led_set_hsb(self, index, value);
    return mp_const_none;
}

MP_DEFINE_CONST_FUN_OBJ_1(chainable_led_deinit_obj, chainable_led_obj_deinit);
MP_DEFINE_CONST_FUN_OBJ_KW(chainable_led_set_rgb_obj, 4, chainable_led_set_rgb);
MP_DEFINE_CONST_FUN_OBJ_KW(chainable_led_set_hsb_obj, 4, chainable_led_set_hsb);
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(chainable_led_obj___exit___obj, 4, 4, chainable_led_obj___exit__);

const mp_rom_map_elem_t chainable_led_locals_dict_table[] = {
    // instance methods
    { MP_ROM_QSTR(MP_QSTR_deinit),    MP_ROM_PTR(&chainable_led_deinit_obj) },
    { MP_ROM_QSTR(MP_QSTR___enter__), MP_ROM_PTR(&default___enter___obj) },
    { MP_ROM_QSTR(MP_QSTR___exit__),  MP_ROM_PTR(&chainable_led_obj___exit___obj) },
    { MP_ROM_QSTR(MP_QSTR_set_rgb),   MP_ROM_PTR(&chainable_led_set_rgb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hsb),   MP_ROM_PTR(&chainable_led_set_hsb_obj) },
};

MP_DEFINE_CONST_DICT(chainable_led_locals_dict, chainable_led_locals_dict_table);

const mp_obj_type_t chainable_led_type = {
    {&mp_type_type},
    .name = MP_QSTR_grove_chainable_Led,
    .make_new = chainable_led_make_new,
    .locals_dict = (mp_obj_t)&chainable_led_locals_dict,
};