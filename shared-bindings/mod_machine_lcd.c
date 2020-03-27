/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * Development of the code in this file was sponsored by Microbric Pty Ltd
 *
 * Author: Hontai Liu (hontai.liu@seeed.cc)
 *
 * Copyright (C) 2020  Seeed Technology Co.,Ltd.
 * The MIT License (MIT)
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
#include <stdio.h>

#include "py/nlr.h"
#include "py/runtime.h"
#include "modmachine.h"
#include "mphalport.h"

#include "wrapper_lcd.h"

extern const mp_obj_type_t machine_lcd_type;

m_generic_make(lcd)
{
    abstract_module_t *self = new_abstruct_module(type);
    mp_arg_check_num(n_args, n_kw, 0, 0, false);
    common_hal_lcd_construct(self);
    return self;
}

mp_obj_t lcd_fillScreen(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint16_t color = mp_obj_get_int(pos_args[1]);
    common_hal_lcd_fillScreen(self, color);
    return mp_const_none;
}

mp_obj_t lcd_setRotation(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint8_t r = mp_obj_get_int(pos_args[1]);
    common_hal_lcd_setRotation(self, r);
    return mp_const_none;
}

mp_obj_t lcd_invertDisplay(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    bool i = mp_obj_get_int(pos_args[1]);
    common_hal_lcd_invertDisplay(self, i);
    return mp_const_none;
}

void lcd_obj_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    abstract_module_t *self = (abstract_module_t *)(self_in);
    if (dest[0] == MP_OBJ_NULL)
    {
        if (attr == MP_QSTR_width)
        {
            dest[0] = mp_obj_new_int(common_hal_lcd_width(self));
            return;
        }
        else if (attr == MP_QSTR_height)
        {
            dest[0] = mp_obj_new_int(common_hal_lcd_height(self));
            return;
        }
    }
    generic_method_lookup(self_in, attr, dest);
}

MP_DEFINE_CONST_FUN_OBJ_KW(lcd_fillScreen_obj, 1, lcd_fillScreen);
MP_DEFINE_CONST_FUN_OBJ_KW(lcd_setRotation_obj, 1, lcd_setRotation);
MP_DEFINE_CONST_FUN_OBJ_KW(lcd_invertDisplay_obj, 1, lcd_invertDisplay);

#ifdef MICROPY_PY_LVGL
DEFINE_PTR_OBJ(common_hal_lcd_monitor_flush);
#endif

const mp_rom_map_elem_t lcd_locals_dict_table[] = {
    // instance methods
    {MP_ROM_QSTR(MP_QSTR_deinit), MP_ROM_PTR(&lcd_deinit_obj)},
    {MP_ROM_QSTR(MP_QSTR___enter__), MP_ROM_PTR(&default___enter___obj)},
    {MP_ROM_QSTR(MP_QSTR___exit__), MP_ROM_PTR(&lcd_obj___exit___obj)},
    {MP_ROM_QSTR(MP_QSTR_fillSreen), MP_ROM_PTR(&lcd_fillScreen_obj)},
    {MP_ROM_QSTR(MP_QSTR_setRotation), MP_ROM_PTR(&lcd_setRotation_obj)},
    {MP_ROM_QSTR(MP_QSTR_inverDisplay), MP_ROM_PTR(&lcd_invertDisplay)},
    #ifdef MICROPY_PY_LVGL
    { MP_ROM_QSTR(MP_QSTR_flush), MP_ROM_PTR(&PTR_OBJ(common_hal_lcd_monitor_flush))},
    #endif
};

MP_DEFINE_CONST_DICT(lcd_locals_dict, lcd_locals_dict_table);

const mp_obj_type_t machine_lcd_type = {
    {&mp_type_type},
    .name = MP_QSTR_LCD,
    .make_new = lcd_make_new,
    .locals_dict = (mp_obj_t)&lcd_locals_dict,
    .attr = lcd_obj_attr,
};
