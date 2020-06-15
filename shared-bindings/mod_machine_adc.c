/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * Development of the code in this file was sponsored by Seeed Studio
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

#include "py/runtime.h"
#include "py/mphal.h"
#include "modmachine.h"
#ifdef ARDUINO
#include "Arduino.h"
#endif

typedef struct _madc_obj_t
{
    mp_obj_base_t base;
    int32_t hardware_id;
    mp_hal_pin_obj_t id;
} madc_obj_t;

STATIC mp_obj_t madc_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw,
                              const mp_obj_t *args)
{
    mp_arg_check_num(n_args, n_kw, 1, MP_OBJ_FUN_ARGS_MAX, true);

    // get the wanted pin object
    mp_hal_pin_obj_t wanted_pin = machine_pin_get_id(args[0]);

    madc_obj_t *self = m_new_obj(madc_obj_t);
    self->base.type = &machine_adc_type;
    self->id = wanted_pin;
    self->hardware_id = machine_pin_get_hardware_id(wanted_pin);

    if (n_args > 1 || n_kw > 0)
    {
        // pin mode given, so configure this GPIO
        mp_map_t kw_args;
        mp_map_init_fixed_table(&kw_args, n_kw, args + n_args);
    }

    return MP_OBJ_FROM_PTR(self);
}

STATIC void madc_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind)
{
    madc_obj_t *self = self_in;
    mp_printf(print, "ADC(Pin(%u))", self->id);
}

STATIC mp_obj_t madc_read(mp_obj_t self_in)
{
    madc_obj_t *self = self_in;
    int val = analogRead(self->hardware_id);
    // if (val == -1) mp_raise_ValueError("Parameter Error");
    return MP_OBJ_NEW_SMALL_INT(val);
}

STATIC mp_obj_t mdac_width(mp_obj_t self_in, mp_obj_t value_in)
{
    madc_obj_t *self = self_in;
    int value = mp_obj_get_int(value_in);
    analogWrite(self->hardware_id, value);
    return mp_const_none;
}


MP_DEFINE_CONST_FUN_OBJ_1(madc_read_obj, madc_read);

STATIC const mp_rom_map_elem_t madc_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_read), MP_ROM_PTR(&madc_read_obj)},
};


STATIC MP_DEFINE_CONST_DICT(madc_locals_dict, madc_locals_dict_table);

const mp_obj_type_t machine_adc_type = {
    {&mp_type_type},
    .name = MP_QSTR_ADC,
    .print = madc_print,
    .make_new = madc_make_new,
    .locals_dict = (mp_obj_t)&madc_locals_dict,
};
