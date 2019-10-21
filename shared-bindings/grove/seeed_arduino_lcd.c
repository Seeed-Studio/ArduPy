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

void common_hal_lcd_construct(abstract_module_t * self);
void common_hal_lcd_deinit(abstract_module_t * self);
void common_hal_lcd_clear(abstract_module_t * self);
void common_hal_lcd_set_cursor(abstract_module_t * self, uint32_t column, uint32_t row);
void common_hal_lcd_print_int(abstract_module_t * self, int32_t value);
void common_hal_lcd_print_float(abstract_module_t * self, float value);
void common_hal_lcd_print_string(abstract_module_t * self, const char * value);
void common_hal_lcd_set_is_blink_cursor(abstract_module_t * self, bool value);
bool common_hal_lcd_get_is_blink_cursor(abstract_module_t * self);

extern const mp_obj_type_t grove_lcd_type;

m_generic_make(lcd){
    abstract_module_t * self = new_abstruct_module(type);
    mp_arg_check_num(n_args, n_kw, 0, 0, false);
    assert_pin_free(&pin_SCL);
    assert_pin_free(&pin_SDA);
    common_hal_lcd_construct(self);
    return self;
}

mp_obj_t lcd_clear(mp_obj_t self_in){
    common_hal_lcd_clear((abstract_module_t *)self_in);
    return mp_const_none;
}

mp_obj_t lcd_set_cursor(size_t n_args, const mp_obj_t * pos_args, mp_map_t * kw_args){
    abstract_module_t * self = (abstract_module_t *)pos_args[0];
    uint32_t column = mp_obj_get_int(pos_args[1]);
    uint32_t row    = mp_obj_get_int(pos_args[2]);
    raise_error_if(column > 16 || column < 1, "1st parameter 'column' need greater equal than 1 and less equal than 16.");
    raise_error_if(row    > 2  || row    < 1, "2st parameter 'row' need greater equal than 1 and less equal than 2.");
    common_hal_lcd_set_cursor(self, column - 1, row - 1);
    return mp_const_none;
}

mp_obj_t lcd_print(size_t n_args, const mp_obj_t * pos_args, mp_map_t * kw_args){
    abstract_module_t * self = (abstract_module_t *)pos_args[0];

    if (mp_obj_is_int(pos_args[1])){
        common_hal_lcd_print_int(self, mp_obj_get_int(pos_args[1]));
    }
    else if (mp_obj_is_float(pos_args[1])){
        common_hal_lcd_print_float(self, mp_obj_get_float(pos_args[1]));
    }
    else if (mp_obj_is_str(pos_args[1])){
        common_hal_lcd_print_string(self, mp_obj_str_get_str(pos_args[1]));
    }
    else{
        mp_raise_TypeError("The allowed parameter type are int, float and string.");
    }
    return mp_const_none;
}

void lcd_obj_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest){
    abstract_module_t * self = (abstract_module_t *)self_in;

    if (attr != MP_QSTR_is_blink_cursor){
        generic_method_lookup(self_in, attr, dest);
    }
    else if (dest[0] != MP_OBJ_NULL) {
        dest[0] = MP_OBJ_NULL;
        common_hal_lcd_set_is_blink_cursor(self, mp_obj_is_true(dest[1]));
    } 
    else {
        dest[0] = common_hal_lcd_get_is_blink_cursor(self) ? 
            mp_const_true : mp_const_false;
    }
}    

MP_DEFINE_CONST_FUN_OBJ_1(lcd_clear_obj, lcd_clear);
MP_DEFINE_CONST_FUN_OBJ_KW(lcd_set_cursor_obj, 2, lcd_set_cursor);
MP_DEFINE_CONST_FUN_OBJ_KW(lcd_print_obj, 1, lcd_print);

const mp_rom_map_elem_t lcd_locals_dict_table[] = {
    // instance methods
    { MP_ROM_QSTR(MP_QSTR_deinit),     MP_ROM_PTR(&lcd_deinit_obj) },
    { MP_ROM_QSTR(MP_QSTR___enter__),  MP_ROM_PTR(&default___enter___obj) },
    { MP_ROM_QSTR(MP_QSTR___exit__),   MP_ROM_PTR(&lcd_obj___exit___obj) },
    { MP_ROM_QSTR(MP_QSTR_clear),      MP_ROM_PTR(&lcd_clear_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_cursor), MP_ROM_PTR(&lcd_set_cursor_obj) },
    { MP_ROM_QSTR(MP_QSTR_print),      MP_ROM_PTR(&lcd_print_obj) },
    
};

MP_DEFINE_CONST_DICT(lcd_locals_dict, lcd_locals_dict_table);

const mp_obj_type_t grove_lcd_type = {
    {&mp_type_type},
    .name = MP_QSTR_grove_16x2_lcd,
    .make_new = lcd_make_new,
    .locals_dict = (mp_obj_t)&lcd_locals_dict,
    .attr = lcd_obj_attr,
};