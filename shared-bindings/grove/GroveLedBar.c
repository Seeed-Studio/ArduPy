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
#include "common-hal/microcontroller/Pin.h"

typedef struct{
    mp_obj_base_t base;
    void *        module;
}led_bar_obj_t;

void common_hal_led_bar_construct(
    void ** self, 
    const mcu_pin_obj_t * pin_clk, 
    const mcu_pin_obj_t * pin_dat);
void common_hal_led_bar_deinit(void *self);
void common_hal_led_bar_get_led_numbers(void *self, uint32_t * value);
void common_hal_led_bar_set_bits(void *self, uint32_t value);
void common_hal_led_bar_get_bits(void *self, uint32_t * value);
void common_hal_led_bar_set_level(void *self, float value);
void common_hal_led_bar_set_brightness(void *self, uint32_t led_no, float value);
void common_hal_led_bar_set_is_reverse_show(void *self, uint32_t value);
void common_hal_led_bar_toggle(void *self, uint32_t led_no);

extern const mp_obj_type_t grove_led_bar_type;

mp_obj_t led_bar_make_new(
    const mp_obj_type_t *type, 
    size_t n_args, 
    size_t n_kw, 
    const mp_obj_t * args) {
    led_bar_obj_t * self = m_new_obj(led_bar_obj_t);
    self->base.type = &grove_led_bar_type;
    assert_pin(args[0], false);
    assert_pin(args[1], false);
    mcu_pin_obj_t * pin_clk = (mcu_pin_obj_t *)(args[0]);
    mcu_pin_obj_t * pin_dat = (mcu_pin_obj_t *)(args[1]);
    assert_pin_free(pin_clk);
    assert_pin_free(pin_dat);
    common_hal_led_bar_construct(&self->module, pin_clk, pin_dat);
    return (mp_obj_t)self;
}

mp_obj_t led_bar_obj_deinit(mp_obj_t self_in) {
    led_bar_obj_t *self = (led_bar_obj_t *)(self_in);
    common_hal_led_bar_deinit(self);
    return mp_const_none;
}

mp_obj_t led_bar_obj___exit__(size_t n_args, const mp_obj_t *args) {
    led_bar_obj_t *self = (led_bar_obj_t *)(args[0]);
    common_hal_led_bar_deinit(self);
    return mp_const_none;
}

mp_obj_t led_bar_get_led_numbers(mp_obj_t self_in){
    led_bar_obj_t *self = (led_bar_obj_t *)(self_in);
    uint32_t value;
    common_hal_led_bar_get_led_numbers(self->module, &value);
    return mp_obj_new_int((mp_int_t)value);
}

mp_obj_t led_bar_set_bits(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args){
    led_bar_obj_t *self = (led_bar_obj_t *)(pos_args[0]);
    uint32_t value = mp_obj_get_int(pos_args[1]);
    common_hal_led_bar_set_bits(self->module, value);
    return mp_const_none;
}
mp_obj_t led_bar_get_bits(mp_obj_t self_in){
    led_bar_obj_t *self = (led_bar_obj_t *)(self_in);
    uint32_t value;
    common_hal_led_bar_get_bits(self->module,  &value);
    return mp_obj_new_int(value);
}
mp_obj_t led_bar_set_level(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args){
    led_bar_obj_t *self = (led_bar_obj_t *)(pos_args[0]);
    float value = mp_obj_get_float(pos_args[1]);
    common_hal_led_bar_set_level(self->module, value);
    return mp_const_none;
}
mp_obj_t led_bar_set_brightness(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args){
    led_bar_obj_t *self = (led_bar_obj_t *)(pos_args[0]);
    uint32_t index = mp_obj_get_int(pos_args[1]);
    float value = mp_obj_get_float(pos_args[2]);
    common_hal_led_bar_set_brightness(self->module, index, value);
    return mp_const_none;
}
mp_obj_t led_bar_set_is_reverse_show(mp_obj_t self_in, mp_obj_t value_obj){
    led_bar_obj_t *self = (led_bar_obj_t *)(self_in);
    uint32_t value = mp_obj_get_int(value_obj);
    common_hal_led_bar_set_is_reverse_show(self->module, value);
    return mp_const_none;
}
mp_obj_t led_bar_toggle(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args){
    led_bar_obj_t *self = (led_bar_obj_t *)(pos_args[0]);
    uint32_t index = mp_obj_get_int(pos_args[1]);
    common_hal_led_bar_toggle(self->module, index);
    return mp_const_none;
}
void led_bar_obj_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest){
    if (dest[0] != MP_OBJ_NULL) {
        switch (attr) {
        case MP_QSTR_is_reverse_show:
            led_bar_set_is_reverse_show(self_in,dest[1]);
            break;
        default:
            generic_method_lookup(self_in, attr, dest);
            break;
        }
        dest[0] = MP_OBJ_NULL; // indicate success
    } else {
        switch (attr) {
        default:
            generic_method_lookup(self_in, attr, dest);
            break;
        }
    }
}

MP_DEFINE_CONST_FUN_OBJ_1(led_bar_deinit_obj, led_bar_obj_deinit);
MP_DEFINE_CONST_FUN_OBJ_KW(led_bar_set_bits_obj, 1, led_bar_set_bits);
MP_DEFINE_CONST_FUN_OBJ_1(led_bar_get_bits_obj, led_bar_get_bits);
MP_DEFINE_CONST_FUN_OBJ_KW(led_bar_set_level_obj, 2, led_bar_set_level);
MP_DEFINE_CONST_FUN_OBJ_KW(led_bar_set_brightness_obj, 2, led_bar_set_brightness);
MP_DEFINE_CONST_FUN_OBJ_KW(led_bar_toggle_obj, 1, led_bar_toggle);

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(led_bar_obj___exit___obj, 4, 4, led_bar_obj___exit__);

const mp_rom_map_elem_t led_bar_locals_dict_table[] = {
    // instance methods
    { MP_ROM_QSTR(MP_QSTR_deinit),          MP_ROM_PTR(&led_bar_deinit_obj) },
    { MP_ROM_QSTR(MP_QSTR___enter__),       MP_ROM_PTR(&default___enter___obj) },
    { MP_ROM_QSTR(MP_QSTR___exit__),        MP_ROM_PTR(&led_bar_obj___exit___obj) },
    { MP_ROM_QSTR(MP_QSTR_set_bits),        MP_ROM_PTR(&led_bar_set_bits_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_bits),        MP_ROM_PTR(&led_bar_get_bits_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_level),       MP_ROM_PTR(&led_bar_set_level_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_brightness),  MP_ROM_PTR(&led_bar_set_brightness_obj) },
    { MP_ROM_QSTR(MP_QSTR_toggle),          MP_ROM_PTR(&led_bar_toggle_obj) },
};

MP_DEFINE_CONST_DICT(led_bar_locals_dict, led_bar_locals_dict_table);
const mp_obj_type_t grove_led_bar_type = {
    {&mp_type_type},
    .name = MP_QSTR_grove_led_bar,
    .make_new = led_bar_make_new,
    .locals_dict = (mp_obj_t)&led_bar_locals_dict,
};