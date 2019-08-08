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
#include "shared-bindings/util.h"
#include "shared-bindings/microcontroller/Pin.h"

typedef struct{
    mp_obj_base_t base;
    void *        module;
}nixie_tube_obj_t;

void common_hal_nixie_tube_construct(
    void ** get, 
    const mcu_pin_obj_t * pin_clk, 
    const mcu_pin_obj_t * pin_dat);
void common_hal_nixie_tube_deinit(void *self);
void common_hal_nixie_tube_clear(void *self);
void common_hal_nixie_tube_display(void *self, uint32_t value);
void common_hal_nixie_tube_set_show_colon(void *self, uint32_t confirm);
void common_hal_nixie_tube_get_show_colon(void *self, uint32_t * confirm);

extern const mp_obj_type_t grove_nixie_tube_type;

mp_obj_t nixie_tube_make_new(
    const mp_obj_type_t *type, 
    size_t n_args, 
    size_t n_kw, 
    const mp_obj_t * args) {
    nixie_tube_obj_t * self = m_new_obj(nixie_tube_obj_t);
    self->base.type = &grove_nixie_tube_type;
    assert_pin(args[0], false);
    assert_pin(args[1], false);
    mcu_pin_obj_t * pin_clk = (mcu_pin_obj_t *)(args[0]);
    mcu_pin_obj_t * pin_dat = (mcu_pin_obj_t *)(args[1]);
    assert_pin_free(pin_clk);
    assert_pin_free(pin_dat);
    common_hal_nixie_tube_construct(&self->module, pin_clk, pin_dat);
    return (mp_obj_t)self;
}

mp_obj_t nixie_tube_obj_deinit(mp_obj_t self_in) {
    nixie_tube_obj_t *self = (nixie_tube_obj_t *)(self_in);
    common_hal_nixie_tube_deinit(self);
    return mp_const_none;
}

mp_obj_t nixie_tube_obj___exit__(size_t n_args, const mp_obj_t *args) {
    nixie_tube_obj_t *self = (nixie_tube_obj_t *)(args[0]);
    common_hal_nixie_tube_deinit(self);
    return mp_const_none;
}

mp_obj_t nixie_tube_clear(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args){
    nixie_tube_obj_t *self = MP_OBJ_TO_PTR(pos_args[0]);
    common_hal_nixie_tube_clear(self->module);
    return mp_const_none;
}
mp_obj_t nixie_tube_display(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args){
    nixie_tube_obj_t *self = MP_OBJ_TO_PTR(pos_args[0]);
    uint32_t value = (uint32_t)mp_obj_get_int(pos_args[1]);
    common_hal_nixie_tube_display(self->module, value);
    return mp_const_none;
}

void nixie_tube_obj_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest){
    nixie_tube_obj_t *self = MP_OBJ_TO_PTR(self_in);
    uint32_t confirm;

    if (dest[0] != MP_OBJ_NULL) {
        switch (attr) {
        case MP_QSTR_show_colon:
            common_hal_nixie_tube_set_show_colon(self->module, (uint32_t)mp_obj_is_true(dest[1]));
            break;
        default:
            generic_method_lookup(self_in, attr, dest);
            break;
        }
        dest[0] = MP_OBJ_NULL; // indicate success
    } else {
        switch (attr) {
        case MP_QSTR_show_colon:
            common_hal_nixie_tube_get_show_colon(self->module, &confirm);
            dest[0] = confirm ? mp_const_true : mp_const_false;
            break;
        default:
            generic_method_lookup(self_in, attr, dest);
            break;
        }
    }
}

MP_DEFINE_CONST_FUN_OBJ_1(nixie_tube_deinit_obj, nixie_tube_obj_deinit);
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(nixie_tube_obj___exit___obj, 4, 4, nixie_tube_obj___exit__);
MP_DEFINE_CONST_FUN_OBJ_1(nixie_tube_clear_obj, nixie_tube_clear);
MP_DEFINE_CONST_FUN_OBJ_KW(nixie_tube_display_obj, 1, nixie_tube_display);

const mp_rom_map_elem_t nixie_tube_locals_dict_table[] = {
    // instance methods
    { MP_ROM_QSTR(MP_QSTR_deinit),    MP_ROM_PTR(&nixie_tube_deinit_obj) },
    { MP_ROM_QSTR(MP_QSTR___enter__), MP_ROM_PTR(&default___enter___obj) },
    { MP_ROM_QSTR(MP_QSTR___exit__),  MP_ROM_PTR(&nixie_tube_obj___exit___obj) },
    { MP_ROM_QSTR(MP_QSTR_clear),     MP_ROM_PTR(&nixie_tube_clear_obj) },
    { MP_ROM_QSTR(MP_QSTR_display),   MP_ROM_PTR(&nixie_tube_display_obj) },
};

MP_DEFINE_CONST_DICT(nixie_tube_locals_dict, nixie_tube_locals_dict_table);
const mp_obj_type_t grove_nixie_tube_type = {
    {&mp_type_type},
    .name = MP_QSTR_grove_nixie_tube,
    .make_new = nixie_tube_make_new,
    .locals_dict = (mp_obj_t)&nixie_tube_locals_dict,
    .attr = &nixie_tube_obj_attr,
};