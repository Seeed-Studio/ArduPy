/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * Development of the code in this file was sponsored by Seeed Studio
 *
 * Author: Baozhu Zuo (baozhu.zuo@gmail.com)
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
#include <string.h>

#include "py/runtime.h"
#include "py/mphal.h"
#include "mphalport.h"
#include "extmod/virtpin.h"

#ifdef ARDUINO
#include "Arduino.h"
#endif

extern const mp_obj_type_t machine_pin_type;

typedef struct _machine_pin_obj_t
{
    mp_obj_base_t base;
    int32_t hardware_id;
    mp_hal_pin_obj_t id;
} machine_pin_obj_t;

typedef struct _machine_pin_irq_obj_t
{
    mp_obj_base_t base;
    int32_t hardware_id;
    mp_hal_pin_obj_t id;
} machine_pin_irq_obj_t;

STATIC const machine_pin_obj_t machine_pin_obj[] = {
#ifdef GPIO_NUM_0
    {{&machine_pin_type}, GPIO_NUM_0, 0},
#endif
#ifdef GPIO_NUM_1
    {{&machine_pin_type}, GPIO_NUM_1, 1},
#endif
#ifdef GPIO_NUM_2
    {{&machine_pin_type}, GPIO_NUM_2, 2},
#endif
#ifdef GPIO_NUM_3
    {{&machine_pin_type}, GPIO_NUM_3, 3},
#endif
#ifdef GPIO_NUM_4
    {{&machine_pin_type}, GPIO_NUM_4, 4},
#endif
#ifdef GPIO_NUM_5
    {{&machine_pin_type}, GPIO_NUM_5, 5},
#endif
#ifdef GPIO_NUM_6
    {{&machine_pin_type}, GPIO_NUM_6, 6},
#endif
#ifdef GPIO_NUM_7
    {{&machine_pin_type}, GPIO_NUM_7, 7},
#endif
#ifdef GPIO_NUM_8
    {{&machine_pin_type}, GPIO_NUM_8, 8},
#endif
#ifdef GPIO_NUM_9
    {{&machine_pin_type}, GPIO_NUM_9, 9},
#endif
#ifdef GPIO_NUM_10
    {{&machine_pin_type}, GPIO_NUM_10, 10},
#endif
#ifdef GPIO_NUM_11
    {{&machine_pin_type}, GPIO_NUM_11, 11},
#endif
#ifdef GPIO_NUM_12
    {{&machine_pin_type}, GPIO_NUM_12, 12},
#endif
#ifdef GPIO_NUM_13
    {{&machine_pin_type}, GPIO_NUM_13, 13},
#endif
#ifdef GPIO_NUM_14
    {{&machine_pin_type}, GPIO_NUM_14, 14},
#endif
#ifdef GPIO_NUM_15
    {{&machine_pin_type}, GPIO_NUM_15, 15},
#endif
#ifdef GPIO_NUM_16
    {{&machine_pin_type}, GPIO_NUM_16, 16},
#endif
#ifdef GPIO_NUM_17
    {{&machine_pin_type}, GPIO_NUM_17, 17},
#endif
#ifdef GPIO_NUM_18
    {{&machine_pin_type}, GPIO_NUM_18, 18},
#endif
#ifdef GPIO_NUM_19
    {{&machine_pin_type}, GPIO_NUM_19, 19},
#endif
#ifdef GPIO_NUM_20
    {{&machine_pin_type}, GPIO_NUM_20, 20},
#endif
#ifdef GPIO_NUM_21
    {{&machine_pin_type}, GPIO_NUM_21, 21},
#endif
#ifdef GPIO_NUM_22
    {{&machine_pin_type}, GPIO_NUM_22, 22},
#endif
#ifdef GPIO_NUM_23
    {{&machine_pin_type}, GPIO_NUM_23, 23},
#endif
#ifdef GPIO_NUM_24
    {{&machine_pin_type}, GPIO_NUM_24, 24},
#endif
#ifdef GPIO_NUM_25
    {{&machine_pin_type}, GPIO_NUM_25, 25},
#endif
#ifdef GPIO_NUM_26
    {{&machine_pin_type}, GPIO_NUM_26, 26},
#endif
#ifdef GPIO_NUM_27
    {{&machine_pin_type}, GPIO_NUM_27, 27},
#endif
#ifdef GPIO_NUM_28
    {{&machine_pin_type}, GPIO_NUM_28, 28},
#endif
#ifdef GPIO_NUM_29
    {{&machine_pin_type}, GPIO_NUM_29, 29},
#endif
#ifdef GPIO_NUM_30
    {{&machine_pin_type}, GPIO_NUM_30, 30},
#endif
#ifdef GPIO_NUM_31
    {{&machine_pin_type}, GPIO_NUM_31, 31},
#endif
#ifdef GPIO_NUM_32
    {{&machine_pin_type}, GPIO_NUM_32, 32},
#endif
#ifdef GPIO_NUM_33
    {{&machine_pin_type}, GPIO_NUM_33, 33},
#endif
#ifdef GPIO_NUM_34
    {{&machine_pin_type}, GPIO_NUM_34, 34},
#endif
#ifdef GPIO_NUM_35
    {{&machine_pin_type}, GPIO_NUM_35, 35},
#endif
#ifdef GPIO_NUM_36
    {{&machine_pin_type}, GPIO_NUM_36, 36},
#endif
#ifdef GPIO_NUM_37
    {{&machine_pin_type}, GPIO_NUM_37, 37},
#endif
#ifdef GPIO_NUM_38
    {{&machine_pin_type}, GPIO_NUM_38, 38},
#endif
#ifdef GPIO_NUM_39
    {{&machine_pin_type}, GPIO_NUM_39, 39},
#endif
#ifdef GPIO_NUM_40
    {{&machine_pin_type}, GPIO_NUM_40, 40},
#endif
#ifdef GPIO_NUM_41
    {{&machine_pin_type}, GPIO_NUM_41, 41},
#endif
#ifdef GPIO_NUM_42
    {{&machine_pin_type}, GPIO_NUM_42, 42},
#endif
#ifdef GPIO_NUM_43
    {{&machine_pin_type}, GPIO_NUM_43, 43},
#endif
#ifdef GPIO_NUM_44
    {{&machine_pin_type}, GPIO_NUM_44, 44},
#endif
#ifdef GPIO_NUM_45
    {{&machine_pin_type}, GPIO_NUM_45, 45},
#endif
#ifdef GPIO_NUM_46
    {{&machine_pin_type}, GPIO_NUM_46, 46},
#endif
#ifdef GPIO_NUM_47
    {{&machine_pin_type}, GPIO_NUM_47, 47},
#endif
#ifdef GPIO_NUM_48
    {{&machine_pin_type}, GPIO_NUM_48, 48},
#endif
#ifdef GPIO_NUM_49
    {{&machine_pin_type}, GPIO_NUM_49, 49},
#endif
#ifdef GPIO_NUM_50
    {{&machine_pin_type}, GPIO_NUM_50, 50},
#endif
#ifdef GPIO_NUM_51
    {{&machine_pin_type}, GPIO_NUM_51, 51},
#endif
#ifdef GPIO_NUM_52
    {{&machine_pin_type}, GPIO_NUM_52, 52},
#endif
#ifdef GPIO_NUM_53
    {{&machine_pin_type}, GPIO_NUM_53, 53},
#endif
#ifdef GPIO_NUM_54
    {{&machine_pin_type}, GPIO_NUM_54, 54},
#endif
#ifdef GPIO_NUM_55
    {{&machine_pin_type}, GPIO_NUM_55, 55},
#endif
#ifdef GPIO_NUM_56
    {{&machine_pin_type}, GPIO_NUM_56, 56},
#endif
#ifdef GPIO_NUM_57
    {{&machine_pin_type}, GPIO_NUM_57, 57},
#endif
#ifdef GPIO_NUM_58
    {{&machine_pin_type}, GPIO_NUM_58, 58},
#endif
#ifdef GPIO_NUM_59
    {{&machine_pin_type}, GPIO_NUM_59, 59},
#endif
#ifdef GPIO_NUM_60
    {{&machine_pin_type}, GPIO_NUM_60, 60},
#endif
#ifdef GPIO_NUM_61
    {{&machine_pin_type}, GPIO_NUM_61, 61},
#endif
#ifdef GPIO_NUM_62
    {{&machine_pin_type}, GPIO_NUM_62, 62},
#endif
#ifdef GPIO_NUM_63
    {{&machine_pin_type}, GPIO_NUM_63, 63},
#endif
#ifdef GPIO_NUM_64
    {{&machine_pin_type}, GPIO_NUM_64, 64},
#endif
};

// forward declaration
STATIC const machine_pin_irq_obj_t machine_pin_irq_object[];

STATIC void machine_pin_isr_handler(void *arg)
{
    // machine_pin_obj_t *self = arg;
    // mp_obj_t handler = MP_STATE_PORT(machine_pin_irq_handler)[self->id];
    // mp_sched_schedule(handler, MP_OBJ_FROM_PTR(self));
    // mp_hal_wake_main_task_from_isr();
}

int machine_pin_get_hardware_id(mp_hal_pin_obj_t pin)
{

    return machine_pin_obj[pin].hardware_id;
}

mp_hal_pin_obj_t machine_pin_get_id(mp_obj_t pin_in)
{
    if (mp_obj_get_type(pin_in) != &machine_pin_type)
    {
        mp_raise_ValueError("expecting a pin");
    }
    machine_pin_obj_t *self = pin_in;
    return self->id;
}

STATIC void machine_pin_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind)
{
    machine_pin_obj_t *self = self_in;
    mp_printf(print, "Pin(%u)", self->id);
}

// pin.init(mode, pull=None, *, value)
STATIC mp_obj_t machine_pin_obj_init_helper(const machine_pin_obj_t *self, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    enum
    {
        ARG_mode,
        ARG_pull,
        ARG_value
    };
    static const mp_arg_t allowed_args[] = {
        {MP_QSTR_mode, MP_ARG_OBJ, {.u_obj = mp_const_none}},
        {MP_QSTR_pull, MP_ARG_OBJ, {.u_obj = mp_const_none}},
        {MP_QSTR_value, MP_ARG_KW_ONLY | MP_ARG_OBJ, {.u_obj = MP_OBJ_NULL}},
    };

    // parse args
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    // set initial value (do this before configuring mode/pull)
    if (args[ARG_value].u_obj != MP_OBJ_NULL)
    {
        digitalWrite(self->hardware_id, mp_obj_is_true(args[ARG_value].u_obj));
    }

    // configure mode
    if (args[ARG_mode].u_obj != mp_const_none)
    {
        mp_int_t pin_io_mode = mp_obj_get_int(args[ARG_mode].u_obj);
        switch (pin_io_mode)
        {
        case INPUT:
        {
            if (args[ARG_pull].u_obj != mp_const_none)
            {
                mp_int_t pin_input_mode = mp_obj_get_int(args[ARG_pull].u_obj);

                switch (pin_input_mode)
                {
                case INPUT_PULLUP:
                    pinMode(self->hardware_id, INPUT_PULLUP);
                    break;
                case INPUT_PULLDOWN:
                    pinMode(self->hardware_id, INPUT_PULLDOWN);
                    break;
                default:
                    pinMode(self->hardware_id, INPUT);
                    break;
                }
            }
            else
            {
                pinMode(self->hardware_id, INPUT);
            }
        }
        break;
        case OUTPUT:
            pinMode(self->hardware_id, OUTPUT);
            if (args[ARG_pull].u_obj != mp_const_none)
            {
                mp_int_t default_value = mp_obj_get_int(args[ARG_pull].u_obj);
            }
            break;
        default:
            pinMode(self->hardware_id, INPUT);
            break;
        }
    }

    return mp_const_none;
}

// constructor(id, ...)
mp_obj_t mp_pin_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args)
{
    mp_arg_check_num(n_args, n_kw, 1, MP_OBJ_FUN_ARGS_MAX, true);

    // get the wanted pin object
    int wanted_pin = mp_obj_get_int(args[0]);
    const machine_pin_obj_t *self = NULL;
    int hardware_id = machine_pin_get_hardware_id(wanted_pin);

    if (hardware_id < 0)
    {
        mp_raise_ValueError("invalid pin");
    }

    if (0 <= wanted_pin && wanted_pin < MP_ARRAY_SIZE(machine_pin_obj))
    {
        self = (machine_pin_obj_t *)&machine_pin_obj[wanted_pin];
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
        machine_pin_obj_init_helper(self, n_args - 1, args + 1, &kw_args);
    }

    return MP_OBJ_FROM_PTR(self);
}

// fast method for getting/setting pin value
STATIC mp_obj_t machine_pin_call(mp_obj_t self_in, size_t n_args, size_t n_kw, const mp_obj_t *args)
{
    mp_arg_check_num(n_args, n_kw, 0, 1, false);
    machine_pin_obj_t *self = self_in;
    if (n_args == 0)
    {
        // get pin
        return MP_OBJ_NEW_SMALL_INT(digitalRead(self->hardware_id));
    }
    else
    {
        // set pin
        digitalWrite(self->hardware_id, mp_obj_is_true(args[0]));
        return mp_const_none;
    }
}

// pin.init(mode, pull)
STATIC mp_obj_t machine_pin_obj_init(size_t n_args, const mp_obj_t *args, mp_map_t *kw_args)
{
    return machine_pin_obj_init_helper(args[0], n_args - 1, args + 1, kw_args);
}
MP_DEFINE_CONST_FUN_OBJ_KW(machine_pin_init_obj, 1, machine_pin_obj_init);

// pin.value([value])
STATIC mp_obj_t machine_pin_value(size_t n_args, const mp_obj_t *args)
{
    return machine_pin_call(args[0], n_args - 1, 0, args + 1);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(machine_pin_value_obj, 1, 2, machine_pin_value);

// pin.off()
STATIC mp_obj_t machine_pin_off(mp_obj_t self_in)
{
    machine_pin_obj_t *self = MP_OBJ_TO_PTR(self_in);
    digitalWrite(self->hardware_id, 0);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(machine_pin_off_obj, machine_pin_off);

// pin.on()
STATIC mp_obj_t machine_pin_on(mp_obj_t self_in)
{
    machine_pin_obj_t *self = MP_OBJ_TO_PTR(self_in);
    digitalWrite(self->hardware_id, 1);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(machine_pin_on_obj, machine_pin_on);

STATIC const mp_rom_map_elem_t machine_pin_locals_dict_table[] = {
    // instance methods
    {MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&machine_pin_init_obj)},
    {MP_ROM_QSTR(MP_QSTR_value), MP_ROM_PTR(&machine_pin_value_obj)},
    {MP_ROM_QSTR(MP_QSTR_off), MP_ROM_PTR(&machine_pin_off_obj)},
    {MP_ROM_QSTR(MP_QSTR_on), MP_ROM_PTR(&machine_pin_on_obj)},
    {MP_ROM_QSTR(MP_QSTR_IN), MP_ROM_INT(INPUT)},
    {MP_ROM_QSTR(MP_QSTR_OUT), MP_ROM_INT(OUTPUT)},
    {MP_ROM_QSTR(MP_QSTR_PULL_UP), MP_ROM_INT(INPUT_PULLUP)},
    {MP_ROM_QSTR(MP_QSTR_PULL_DOWN), MP_ROM_INT(INPUT_PULLDOWN)},
    {MP_ROM_QSTR(MP_QSTR_IRQ_RISING), MP_ROM_INT(RISING)},
    {MP_ROM_QSTR(MP_QSTR_IRQ_FALLING), MP_ROM_INT(FALLING)},
    {MP_ROM_QSTR(MP_QSTR_IRQ_CHANGE), MP_ROM_INT(CHANGE)},
};

STATIC mp_uint_t pin_ioctl(mp_obj_t self_in, mp_uint_t request, uintptr_t arg, int *errcode)
{
    (void)errcode;
    machine_pin_obj_t *self = self_in;

    switch (request)
    {
    case MP_PIN_READ:
    {
        return digitalRead(self->hardware_id);
    }
    case MP_PIN_WRITE:
    {
        digitalWrite(self->hardware_id, arg);
        return 0;
    }
    }
    return -1;
}

STATIC MP_DEFINE_CONST_DICT(machine_pin_locals_dict, machine_pin_locals_dict_table);

STATIC const mp_pin_p_t pin_pin_p = {
    .ioctl = pin_ioctl,
};

const mp_obj_type_t machine_pin_type = {
    {&mp_type_type},
    .name = MP_QSTR_Pin,
    .print = machine_pin_print,
    .make_new = mp_pin_make_new,
    .call = machine_pin_call,
    .protocol = &pin_pin_p,
    .locals_dict = (mp_obj_t)&machine_pin_locals_dict,
};
