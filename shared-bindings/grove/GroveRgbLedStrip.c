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
#include "common-hal/grove/GroveRtc.h"

typedef struct{
    mp_obj_base_t base;
    void *        module;
}rgb_led_strip_obj_t;

void common_hal_rgb_led_strip_construct(
    void ** get, 
    const mcu_pin_obj_t * pin_ctrl,
    uint32_t count_of_led);
void common_hal_rgb_led_strip_deinit(void * self);
void common_hal_rgb_led_strip_clear(void * self);
void common_hal_rgb_led_strip_update(void * self);
void common_hal_rgb_led_strip_set_pix_color(void * self, uint32_t led_no, uint32_t color);
void common_hal_rgb_led_strip_set_brightness(void * self, uint32_t value);

extern const mp_obj_type_t grove_rgb_led_strip_type;

mp_obj_t rgb_led_strip_make_new(
    const mp_obj_type_t *type, 
    size_t n_args, 
    size_t n_kw, 
    const mp_obj_t * args) {
    rgb_led_strip_obj_t * self = m_new_obj(rgb_led_strip_obj_t);
    mp_obj_t            * device_type;
    mcu_pin_obj_t       * pin = (mcu_pin_obj_t *)args[0];
    uint32_t              count_of_led = mp_obj_get_int(args[1]);
    self->base.type = &grove_rgb_led_strip_type;
    assert_pin_free(&pin);
    common_hal_rgb_led_strip_construct(&self->module, pin, count_of_led);
    return (mp_obj_t)self;
}

mp_obj_t rgb_led_strip_obj_deinit(mp_obj_t self_in) {
    rgb_led_strip_obj_t * self = (rgb_led_strip_obj_t *)(self_in);
    common_hal_rgb_led_strip_deinit(self);
    return mp_const_none;
}

mp_obj_t rgb_led_strip_obj___exit__(size_t n_args, const mp_obj_t *args) {
    rgb_led_strip_obj_t * self = (rgb_led_strip_obj_t *)(args[0]);
    common_hal_rgb_led_strip_deinit(self);
    return mp_const_none;
}

mp_obj_t rgb_led_strip_clear(mp_obj_t self_in){
    rgb_led_strip_obj_t * self = (rgb_led_strip_obj_t *)(self_in);
    common_hal_rgb_led_strip_clear(self->module);
    return mp_const_none;
}

mp_obj_t rgb_led_strip_update(mp_obj_t self_in){
    rgb_led_strip_obj_t * self = (rgb_led_strip_obj_t *)(self_in);
    common_hal_rgb_led_strip_update(self->module);
    return mp_const_none;
}

mp_obj_t rgb_led_strip_set_pix_color(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args){
    rgb_led_strip_obj_t * self = (rgb_led_strip_obj_t *)(pos_args[0]);
    uint32_t led_no = mp_obj_get_int(pos_args[1]);
    uint32_t color = mp_obj_get_int(pos_args[2]);
    common_hal_rgb_led_strip_set_pix_color(self->module, led_no, color);
    return mp_const_none;
}

mp_obj_t rgb_led_strip_set_brightness(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args){
    rgb_led_strip_obj_t * self = (rgb_led_strip_obj_t *)(pos_args[0]);
    uint32_t value = mp_obj_get_int(pos_args[1]);
    common_hal_rgb_led_strip_set_brightness(self->module, value);
    return mp_const_none;
}

MP_DEFINE_CONST_FUN_OBJ_1(rgb_led_strip_deinit_obj, rgb_led_strip_obj_deinit);
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(rgb_led_strip_obj___exit___obj, 4, 4, rgb_led_strip_obj___exit__);
MP_DEFINE_CONST_FUN_OBJ_1(rgb_led_strip_clear_obj, rgb_led_strip_clear);
MP_DEFINE_CONST_FUN_OBJ_1(rgb_led_strip_update_obj, rgb_led_strip_update);
MP_DEFINE_CONST_FUN_OBJ_KW(rgb_led_strip_set_pix_color_obj, 2, rgb_led_strip_set_pix_color);
MP_DEFINE_CONST_FUN_OBJ_KW(rgb_led_strip_set_brightness_obj, 1, rgb_led_strip_set_brightness);

const mp_rom_map_elem_t rgb_led_strip_locals_dict_table[] = {
    // instance methods
    { MP_ROM_QSTR(MP_QSTR_deinit),          MP_ROM_PTR(&rgb_led_strip_deinit_obj) },
    { MP_ROM_QSTR(MP_QSTR___enter__),       MP_ROM_PTR(&default___enter___obj) },
    { MP_ROM_QSTR(MP_QSTR___exit__),        MP_ROM_PTR(&rgb_led_strip_obj___exit___obj) },
    { MP_ROM_QSTR(MP_QSTR_clear),           MP_ROM_PTR(&rgb_led_strip_clear_obj) },
    { MP_ROM_QSTR(MP_QSTR_update),          MP_ROM_PTR(&rgb_led_strip_update_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pix_color),   MP_ROM_PTR(&rgb_led_strip_set_pix_color_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_brightness),  MP_ROM_PTR(&rgb_led_strip_set_brightness_obj) },
};

MP_DEFINE_CONST_DICT(rgb_led_strip_locals_dict, rgb_led_strip_locals_dict_table);

const mp_obj_type_t grove_rgb_led_strip_type = {
    {&mp_type_type},
    .name = MP_QSTR_grove_rgb_led_strip,
    .make_new = rgb_led_strip_make_new,
    .locals_dict = (mp_obj_t)&rgb_led_strip_locals_dict,
};