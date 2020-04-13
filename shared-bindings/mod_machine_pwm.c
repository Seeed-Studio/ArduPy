/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Development of the code in this file was sponsored by Seeed Studio
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

#include "wrapper_pwm.h"

// Forward dec'l
extern const mp_obj_type_t machine_pwm_type;

typedef struct _mp_pwm_obj_t
{
    mp_obj_base_t base;
    int32_t hardware_id;
    mp_hal_pin_obj_t id;
    uint32_t freq;
    uint32_t duty;
} mp_pwm_obj_t;

/******************************************************************************/

// MicroPython bindings for PWM

STATIC void mp_pwm_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind)
{
    mp_pwm_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_printf(print, "PWM(Arduino Pin(%u)", self->id);
    mp_printf(print, ", freq=%u, duty=%u", self->freq, self->duty);
    mp_printf(print, ")");
}

STATIC void mp_pwm_init_helper(mp_pwm_obj_t *self,
                               size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    enum
    {
        ARG_freq,
        ARG_duty
    };
    static const mp_arg_t allowed_args[] = {
        {MP_QSTR_freq, MP_ARG_INT, {.u_int = 1000}},
        {MP_QSTR_duty, MP_ARG_INT, {.u_int = 512}},
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args,
                     MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    // Maybe change PWM timer
    int tval = args[ARG_freq].u_int;
    // Set duty cycle?
    int dval = args[ARG_duty].u_int;
    self->freq = tval;
    self->duty = dval;

    wrapper_pwm(self->hardware_id, tval, dval);
}

STATIC mp_obj_t mp_pwm_make_new(const mp_obj_type_t *type,
                                size_t n_args, size_t n_kw, const mp_obj_t *args)
{
    mp_arg_check_num(n_args, n_kw, 1, MP_OBJ_FUN_ARGS_MAX, true);
    mp_hal_pin_obj_t wanted_pin = machine_pin_get_id(args[0]);
    mp_pwm_obj_t *self = m_new_obj(mp_pwm_obj_t);
    self->base.type = &machine_pwm_type;
    self->id = wanted_pin;
    self->hardware_id = machine_pin_get_hardware_id(wanted_pin);
    self->freq = 1000;
    self->duty = 512;
   
    // start the PWM running for this channel
    mp_map_t kw_args;
    mp_map_init_fixed_table(&kw_args, n_kw, args + n_args);
    mp_pwm_init_helper(self, n_args - 1, args + 1, &kw_args);

    return MP_OBJ_FROM_PTR(self);
}

STATIC mp_obj_t mp_pwm_init(size_t n_args,
                            const mp_obj_t *args, mp_map_t *kw_args)
{
    mp_pwm_init_helper(args[0], n_args - 1, args + 1, kw_args);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(mp_pwm_init_obj, 1, mp_pwm_init);

STATIC mp_obj_t mp_pwm_deinit(mp_obj_t self_in)
{
    mp_pwm_obj_t *self = MP_OBJ_TO_PTR(self_in);
    wrapper_noPwm(self->hardware_id);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(mp_pwm_deinit_obj, mp_pwm_deinit);

STATIC mp_obj_t mp_pwm_freq(size_t n_args, const mp_obj_t *args)
{
    mp_pwm_obj_t *self = MP_OBJ_TO_PTR(args[0]);
    if (n_args == 1)
    {
        // get
        return MP_OBJ_NEW_SMALL_INT(self->freq);
    }
    // set
    int tval = mp_obj_get_int(args[1]);
    self->freq = tval;
    wrapper_pwm(self->hardware_id, tval, self->duty);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_pwm_freq_obj, 1, 2, mp_pwm_freq);

STATIC mp_obj_t mp_pwm_duty(size_t n_args, const mp_obj_t *args)
{
    mp_pwm_obj_t *self = MP_OBJ_TO_PTR(args[0]);
    int duty;

    if (n_args == 1)
    {
        // get
        return MP_OBJ_NEW_SMALL_INT(self->duty);
    }

    // set
    duty = mp_obj_get_int(args[1]);
    self->duty = duty;
    wrapper_pwm(self->hardware_id, self->freq, self->duty);

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_pwm_duty_obj,
                                           1, 2, mp_pwm_duty);

STATIC const mp_rom_map_elem_t mp_pwm_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&mp_pwm_init_obj)},
    {MP_ROM_QSTR(MP_QSTR_deinit), MP_ROM_PTR(&mp_pwm_deinit_obj)},
    {MP_ROM_QSTR(MP_QSTR_freq), MP_ROM_PTR(&mp_pwm_freq_obj)},
    {MP_ROM_QSTR(MP_QSTR_duty), MP_ROM_PTR(&mp_pwm_duty_obj)},
};

STATIC MP_DEFINE_CONST_DICT(mp_pwm_locals_dict,
                            mp_pwm_locals_dict_table);

const mp_obj_type_t machine_pwm_type = {
    {&mp_type_type},
    .name = MP_QSTR_PWM,
    .print = mp_pwm_print,
    .make_new = mp_pwm_make_new,
    .locals_dict = (mp_obj_dict_t *)&mp_pwm_locals_dict,
};

