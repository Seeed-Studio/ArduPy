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
#include "py/obj.h"
#include "shared-bindings/microcontroller/Pin.h"
#include "shared-bindings/util.h"

void common_hal_led_bar_construct(
    abstract_module_t * self, 
    uint32_t pin_clk, 
    uint32_t pin_dat);
void common_hal_led_bar_deinit(abstract_module_t * self);
void common_hal_led_bar_set_bits(abstract_module_t * self, uint32_t value);
void common_hal_led_bar_set_level(abstract_module_t * self, float value);
void common_hal_led_bar_set_brightness(abstract_module_t * self, uint32_t led_no, float value);
void common_hal_led_bar_set_is_reverse_show(abstract_module_t * self, bool value);
void common_hal_led_bar_toggle(abstract_module_t * self, uint32_t led_no);
uint32_t common_hal_led_bar_get_led_numbers(abstract_module_t * self);
uint32_t common_hal_led_bar_get_bits(abstract_module_t * self);

extern const mp_obj_type_t grove_led_bar_type;

m_generic_make(led_bar) {
    abstract_module_t * self = new_abstruct_module(type);
    mcu_pin_obj_t     * pin_clk = (mcu_pin_obj_t *)(args[0]);
    mcu_pin_obj_t     * pin_dat = (mcu_pin_obj_t *)(args[1]);
    assert_pin(args[0], true);
    assert_pin(args[1], true);
    assert_pin_free(pin_clk);
    assert_pin_free(pin_dat);
    common_hal_led_bar_construct(self, pin_clk->number, pin_dat->number);
    return self;
}

mp_obj_t led_bar_get_led_numbers(mp_obj_t self_in){
    return mp_obj_new_int(
        common_hal_led_bar_get_led_numbers((abstract_module_t *)(self_in))
    );
}

mp_obj_t led_bar_set_bits(size_t n_args, const mp_obj_t * pos_args, mp_map_t * kw_args){
    void print_hex(uint32_t);
    common_hal_led_bar_set_bits(
        (abstract_module_t *)(pos_args[0]), 
        (uint32_t)mp_obj_get_int(pos_args[1])
    );
    return mp_const_none;
}
mp_obj_t led_bar_get_bits(mp_obj_t self_in){
    return mp_obj_new_int(
        common_hal_led_bar_get_bits((abstract_module_t *)(self_in))
    );
}
mp_obj_t led_bar_set_level(size_t n_args, const mp_obj_t * pos_args, mp_map_t * kw_args){
    abstract_module_t * self = (abstract_module_t *)(pos_args[0]);
    float value = mp_obj_get_float(pos_args[1]);
    common_hal_led_bar_set_level(self, value);
    return mp_const_none;
}
mp_obj_t led_bar_set_brightness(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args){
    abstract_module_t * self = (abstract_module_t *)(pos_args[0]);
    uint32_t led_no = mp_obj_get_int(pos_args[1]);
    float value = mp_obj_get_float(pos_args[2]);
    common_hal_led_bar_set_brightness(self, led_no, value);
    return mp_const_none;
}
mp_obj_t led_bar_set_is_reverse_show(mp_obj_t self_in, mp_obj_t value_obj){
    abstract_module_t * self = (abstract_module_t *)(self_in);
    uint32_t value = mp_obj_get_int(value_obj);
    common_hal_led_bar_set_is_reverse_show(self, value);
    return mp_const_none;
}
mp_obj_t led_bar_toggle(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args){
    abstract_module_t * self = (abstract_module_t *)(pos_args[0]);
    uint32_t led_no = mp_obj_get_int(pos_args[1]);
    common_hal_led_bar_toggle(self, led_no);
    return mp_const_none;
}
void led_bar_obj_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest){
    if (dest[0] == MP_OBJ_NULL || attr != MP_QSTR_is_reverse_show){
        generic_method_lookup(self_in, attr, dest);
        return;
    }
    dest[0] = MP_OBJ_NULL; // indicate success
    led_bar_set_is_reverse_show(self_in, dest[1]);
}

MP_DEFINE_CONST_FUN_OBJ_KW(led_bar_set_bits_obj, 1, led_bar_set_bits);
MP_DEFINE_CONST_FUN_OBJ_1(led_bar_get_bits_obj, led_bar_get_bits);
MP_DEFINE_CONST_FUN_OBJ_KW(led_bar_set_level_obj, 2, led_bar_set_level);
MP_DEFINE_CONST_FUN_OBJ_KW(led_bar_set_brightness_obj, 2, led_bar_set_brightness);
MP_DEFINE_CONST_FUN_OBJ_KW(led_bar_toggle_obj, 1, led_bar_toggle);

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
    .attr = &led_bar_obj_attr,
};