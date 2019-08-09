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

void common_hal_nixie_tube_construct(
    abstract_module_t * self, 
    uint32_t pin_clk, 
    uint32_t pin_dat);
void common_hal_nixie_tube_deinit(abstract_module_t * self);
void common_hal_nixie_tube_clear(abstract_module_t * self);
void common_hal_nixie_tube_display(abstract_module_t * self, uint32_t value);
void common_hal_nixie_tube_set_show_colon(abstract_module_t * self, bool confirm);
bool common_hal_nixie_tube_get_show_colon(abstract_module_t * self);

extern const mp_obj_type_t grove_nixie_tube_type;

m_generic_make(nixie_tube) {
    enum { ARG_clk, ARG_dat,  };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_clk, MP_ARG_REQUIRED | MP_ARG_OBJ },
        { MP_QSTR_dat, MP_ARG_REQUIRED | MP_ARG_OBJ },
    };

    abstract_module_t * self = new_abstruct_module(type);
    mp_arg_val_t        vals[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_check_num(n_args, n_kw, 2, 2, false);
    mp_arg_parse_all_kw_array(n_args, n_kw, args, MP_ARRAY_SIZE(allowed_args), allowed_args, vals);
    assert_pin(vals[ARG_clk].u_obj, true);
    assert_pin(vals[ARG_dat].u_obj, true);
    assert_pin_free(vals[ARG_clk].u_obj);
    assert_pin_free(vals[ARG_dat].u_obj);
    common_hal_nixie_tube_construct(
        self, 
        m_get_pin(ARG_clk)->number, 
        m_get_pin(ARG_dat)->number
    );
    return self;
}

mp_obj_t nixie_tube_clear(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args){
    common_hal_nixie_tube_clear((abstract_module_t *)pos_args[0]);
    return mp_const_none;
}
mp_obj_t nixie_tube_display(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args){
    common_hal_nixie_tube_display(
        (abstract_module_t *)pos_args[0], 
        (uint32_t)mp_obj_get_int(pos_args[1])
    );
    return mp_const_none;
}

void nixie_tube_obj_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest){
    abstract_module_t * self = (abstract_module_t *)self_in;
    
    if (attr != MP_QSTR_show_colon){
        generic_method_lookup(self_in, attr, dest);
        return;
    }
    if (dest[0] != MP_OBJ_NULL){
        dest[0] =  MP_OBJ_NULL;
        common_hal_nixie_tube_set_show_colon(self, mp_obj_is_true(dest[1]));
    }
    else{
        dest[0] = common_hal_nixie_tube_get_show_colon(self) ? 
            mp_const_true : mp_const_false;
    }
}

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