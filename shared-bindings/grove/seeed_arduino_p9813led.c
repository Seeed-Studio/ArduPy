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

void common_hal_chainable_led_construct(
    abstract_module_t * self, 
    uint32_t pin_clk, 
    uint32_t pin_dat,
    uint32_t count_of_led);

void common_hal_chainable_led_deinit(abstract_module_t * self);
uint32_t common_hal_chainable_led_get_led_numbers(abstract_module_t * self);
void common_hal_chainable_led_set_rgb(abstract_module_t * self, uint32_t led_no, uint8_t r, uint8_t g, uint8_t b);
void common_hal_chainable_led_set_hsb(abstract_module_t * self, uint32_t led_no, uint8_t h, uint8_t s, uint8_t b);

m_generic_make(chainable_led) {
    enum { ARG_clk, ARG_dat, ARG_led_numbers };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_clk,         MP_ARG_REQUIRED | MP_ARG_OBJ },
        { MP_QSTR_dat,         MP_ARG_REQUIRED | MP_ARG_OBJ },
        { MP_QSTR_led_numbers, MP_ARG_INT, { .u_int = 1 } },
    };
    
    abstract_module_t * self = new_abstruct_module(type);
    mp_arg_val_t        vals[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_check_num(n_args, n_kw, 2, 3, false);
    mp_arg_parse_all_kw_array(n_args, n_kw, args, MP_ARRAY_SIZE(allowed_args), allowed_args, vals);
    assert_pin(vals[ARG_clk].u_obj, true);
    assert_pin(vals[ARG_dat].u_obj, true);
    assert_pin_free(vals[ARG_clk].u_obj);
    assert_pin_free(vals[ARG_dat].u_obj);
    common_hal_chainable_led_construct(
        self, 
        m_get_pin(ARG_clk)->number, 
        m_get_pin(ARG_dat)->number,
        vals[ARG_led_numbers].u_int
    );
    return self;
}

mp_obj_t chainable_led_set_rgb(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args){
    abstract_module_t * self = (abstract_module_t *)pos_args[0];
    uint32_t            led_numbers = common_hal_chainable_led_get_led_numbers(self);
    uint32_t            no = mp_obj_get_int(pos_args[1]);
    uint32_t            r  = mp_obj_get_int(pos_args[2]);
    uint32_t            g  = mp_obj_get_int(pos_args[3]);
    uint32_t            b  = mp_obj_get_int(pos_args[4]);
    
    raise_error_if(no >= led_numbers || no < 1, "The 1st argument 'led_no' can't larger than total count of led.");
    raise_error_if(r  >= 256         || r  < 0, "The 2nd argument 'r' can't larger equal than 256 or less than 0.");
    raise_error_if(g  >= 256         || g  < 0, "The 3rd argument 'g' can't larger equal than 256 or less than 0.");
    raise_error_if(b  >= 256         || b  < 0, "The 4th argument 'b' can't larger equal than 256 or less than 0.");
    common_hal_chainable_led_set_rgb(self, no, r, g, b);
    return mp_const_none;
}

mp_obj_t chainable_led_set_hsb(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args){
    abstract_module_t * self = (abstract_module_t *)pos_args[0];
    uint32_t            led_numbers = common_hal_chainable_led_get_led_numbers(self);
    uint32_t            no = mp_obj_get_int(pos_args[1]);
    float               h  = mp_obj_get_float(pos_args[2]);
    float               s  = mp_obj_get_float(pos_args[3]);
    float               b  = mp_obj_get_float(pos_args[4]);
    
    raise_error_if(no >= led_numbers, "The 1st argument 'led_no' can't larger equal than total count of led.");
    raise_error_if(h > 1 || h < 0,    "The 2nd argument 'h' can't larger than 1.0f or less than 0.0f.");
    raise_error_if(s > 1 || s < 0,    "The 3rd argument 's' can't larger than 1.0f or less than 0.0f.");
    raise_error_if(b > 1 || b < 0,    "The 4th argument 'b' can't larger than 1.0f or less than 0.0f.");
    common_hal_chainable_led_set_hsb(self, no, h, s, b);
    return mp_const_none;
}

MP_DEFINE_CONST_FUN_OBJ_KW(chainable_led_set_rgb_obj, 4, chainable_led_set_rgb);
MP_DEFINE_CONST_FUN_OBJ_KW(chainable_led_set_hsb_obj, 4, chainable_led_set_hsb);

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