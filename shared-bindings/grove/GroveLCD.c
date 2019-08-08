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

void common_hal_lcd_construct(void ** get);
void common_hal_lcd_deinit(void * self);
void common_hal_lcd_clear(void * self);
void common_hal_lcd_set_cursor(void * self, uint32_t column, uint32_t row);
void common_hal_lcd_print_int(void * self, int32_t value);
void common_hal_lcd_print_float(void * self, float value);
void common_hal_lcd_print_string(void * self, const char * value);
void common_hal_lcd_show_cursor(void * self, uint32_t value);

typedef struct{
    mp_obj_base_t base;
    void *        module;
    bool          is_show_cursor;
}lcd_obj_t;

extern const mp_obj_type_t grove_lcd_type;

mp_obj_t lcd_make_new(
    const mp_obj_type_t *type, 
    size_t n_args, 
    size_t n_kw, 
    const mp_obj_t * args) {
    lcd_obj_t     * self = m_new_obj(lcd_obj_t);
    mp_obj_t      * device_type;
    self->base.type = &grove_lcd_type;
    self->is_show_cursor = false;
    assert_pin_free(&pin_SCL);
    assert_pin_free(&pin_SDA);
    common_hal_lcd_construct(&self->module);
    return (mp_obj_t)self;
}

mp_obj_t lcd_obj_deinit(mp_obj_t self_in) {
    lcd_obj_t * self = (lcd_obj_t *)(self_in);
    common_hal_lcd_deinit(self);
    return mp_const_none;
}

mp_obj_t lcd_obj___exit__(size_t n_args, const mp_obj_t *args) {
    lcd_obj_t * self = (lcd_obj_t *)(args[0]);
    common_hal_lcd_deinit(self);
    return mp_const_none;
}

mp_obj_t lcd_clear(mp_obj_t self_in){
    lcd_obj_t * self = (lcd_obj_t *)(self_in);
    common_hal_lcd_clear(self->module);
    return mp_const_none;
}

mp_obj_t lcd_set_cursor(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args){
    lcd_obj_t * self = (lcd_obj_t *)(pos_args[0]);
    uint32_t column = mp_obj_get_int(pos_args[1]);
    uint32_t row = mp_obj_get_int(pos_args[2]);
    common_hal_lcd_set_cursor(self->module, column, row);
    return mp_const_none;
}

mp_obj_t lcd_print(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args){
    lcd_obj_t * self = (lcd_obj_t *)(pos_args[0]);
    if (mp_obj_is_int(pos_args[1])){
        common_hal_lcd_print_int(self->module, mp_obj_get_int(pos_args[1]));
    }
    else if (mp_obj_is_float(pos_args[1])){
        common_hal_lcd_print_float(self->module, mp_obj_get_float(pos_args[1]));
    }
    else if (mp_obj_is_str(pos_args[1])){
        common_hal_lcd_print_string(self->module, mp_obj_str_get_str(pos_args[1]));
    }
    else{
        raise_error_if(true, "Unkown argument type.");
    }
    return mp_const_none;
}

void lcd_obj_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest){
    extern const mp_obj_type_t grove_datetime_type;
    lcd_obj_t * self = (lcd_obj_t *)self_in;

    if (dest[0] != MP_OBJ_NULL) {
        switch (attr) {
        case MP_QSTR_is_blink_cursor:
            common_hal_lcd_show_cursor(self->module, self->is_show_cursor = mp_obj_is_true(dest[1]));
            break;
        default:
            generic_method_lookup(self_in, attr, dest);
            break;
        }
        dest[0] = MP_OBJ_NULL;
    } else {
        switch (attr) {
        case MP_QSTR_is_blink_cursor:
            dest[0] = self->is_show_cursor ? mp_const_true : mp_const_false;
            break;
        default:
            generic_method_lookup(self_in, attr, dest);
            break;
        }
    }
}    

MP_DEFINE_CONST_FUN_OBJ_1(lcd_deinit_obj, lcd_obj_deinit);
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_obj___exit___obj, 4, 4, lcd_obj___exit__);
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