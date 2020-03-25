/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Nick Moore
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
    mp_hal_pin_obj_t gpio_id;
} madc_obj_t;

STATIC const madc_obj_t madc_obj[] = {
#ifdef ADC_A0
    {{&machine_adc_type}, ADC_A0},
#endif
#ifdef ADC_A1
    {{&machine_adc_type}, ADC_A1},
#endif
#ifdef ADC_A2
    {{&machine_adc_type}, ADC_A2},
#endif
#ifdef ADC_A3
    {{&machine_adc_type}, ADC_A3},
#endif
#ifdef ADC_A4
    {{&machine_adc_type}, ADC_A4},
#endif
#ifdef ADC_A5
    {{&machine_adc_type}, ADC_A5},
#endif
#ifdef ADC_A6
    {{&machine_adc_type}, ADC_A6},
#endif
#ifdef ADC_A7
    {{&machine_adc_type}, ADC_A7},
#endif
#ifdef ADC_A8
    {{&machine_adc_type}, ADC_A8},
#endif
};

STATIC mp_obj_t madc_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw,
                              const mp_obj_t *args)
{
    mp_arg_check_num(n_args, n_kw, 1, MP_OBJ_FUN_ARGS_MAX, true);

    // get the wanted pin object
    int wanted_pin = mp_obj_get_int(args[0]);
    const madc_obj_t *self = NULL;

    for (uint8_t i = 0; i < MP_ARRAY_SIZE(madc_obj); i++)
    {
        if (wanted_pin == madc_obj[i].gpio_id)
        {
            self = (madc_obj_t *)&madc_obj[i];
            break;
        }
    }

    if (self == NULL || self->base.type == NULL)
    {
        mp_raise_ValueError("invalid pin");
    }

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
    mp_printf(print, "ADC(Pin(%u))", self->gpio_id);
}

STATIC mp_obj_t madc_read(mp_obj_t self_in)
{
    madc_obj_t *self = self_in;
    int val = analogRead(self->gpio_id);
    // if (val == -1) mp_raise_ValueError("Parameter Error");
    return MP_OBJ_NEW_SMALL_INT(val);
}

STATIC mp_obj_t mdac_width(mp_obj_t self_in, mp_obj_t value_in)
{
    madc_obj_t *self = self_in;
    int value = mp_obj_get_int(value_in);
    analogWrite(self->gpio_id, value);
    return mp_const_none;
}


MP_DEFINE_CONST_FUN_OBJ_1(madc_read_obj, madc_read);

STATIC const mp_rom_map_elem_t madc_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_read), MP_ROM_PTR(&madc_read_obj)},

//const
#ifdef ADC_A0
    {MP_ROM_QSTR(MP_QSTR_A0), MP_ROM_INT(ADC_A0)},
#endif
#ifdef ADC_A1
    {MP_ROM_QSTR(MP_QSTR_A1), MP_ROM_INT(ADC_A1)},
#endif
#ifdef ADC_A2
    {MP_ROM_QSTR(MP_QSTR_A2), MP_ROM_INT(ADC_A2)},
#endif
#ifdef ADC_A3
    {MP_ROM_QSTR(MP_QSTR_A3), MP_ROM_INT(ADC_A3)},
#endif
#ifdef ADC_A4
    {MP_ROM_QSTR(MP_QSTR_A4), MP_ROM_INT(ADC_A4)},
#endif
#ifdef ADC_A5
    {MP_ROM_QSTR(MP_QSTR_A5), MP_ROM_INT(ADC_A5)},
#endif
#ifdef ADC_A6
    {MP_ROM_QSTR(MP_QSTR_A6), MP_ROM_INT(ADC_A6)},
#endif
#ifdef ADC_A7
    {MP_ROM_QSTR(MP_QSTR_A7), MP_ROM_INT(ADC_A7)},
#endif
#ifdef ADC_A8
    {MP_ROM_QSTR(MP_QSTR_A8), MP_ROM_INT(ADC_A8)},
#endif
};


STATIC MP_DEFINE_CONST_DICT(madc_locals_dict, madc_locals_dict_table);

const mp_obj_type_t machine_adc_type = {
    {&mp_type_type},
    .name = MP_QSTR_ADC,
    .print = madc_print,
    .make_new = madc_make_new,
    .locals_dict = (mp_obj_t)&madc_locals_dict,
};
