/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Damien P. George
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

#include <stdint.h>
#include "py/runtime.h"
#include "shared-bindings/microcontroller/Pin.h"
#include "shared-bindings/util.h"

void common_hal_pulseio_pwmout_never_reset(abstract_module_t * self);
void common_hal_pulseio_pwmout_reset_ok(abstract_module_t * self);
void common_hal_pulseio_pwmout_construct(
    abstract_module_t * self,
    uint32_t pin,
    uint32_t duty,
    uint32_t frequency,
    bool variable_frequency
);
bool common_hal_pulseio_pwmout_deinited(abstract_module_t * self);
void common_hal_pulseio_pwmout_deinit(abstract_module_t * self);
void common_hal_pulseio_pwmout_set_duty_cycle(abstract_module_t * self, uint32_t duty);
void common_hal_pulseio_pwmout_set_frequency(abstract_module_t * self, uint32_t frequency);
bool common_hal_pulseio_pwmout_get_variable_frequency(abstract_module_t * self);
uint32_t common_hal_pulseio_pwmout_get_duty_cycle(abstract_module_t * self);
uint32_t common_hal_pulseio_pwmout_get_frequency(abstract_module_t * self);

//| .. currentmodule:: pulseio
//|
//| :class:`PWMOut` -- Output a Pulse Width Modulated signal
//| ========================================================
//|
//| PWMOut can be used to output a PWM signal on a given pin.
//|
//| .. class:: PWMOut(pin, \*, duty_cycle=0, frequency=500, variable_frequency=False)
//|
//|   Create a PWM object associated with the given pin. This allows you to
//|   write PWM signals out on the given pin. Frequency is fixed after init
//|   unless ``variable_frequency`` is True.
//|
//|   .. note:: When ``variable_frequency`` is True, further PWM outputs may be
//|     limited because it may take more internal resources to be flexible. So,
//|     when outputting both fixed and flexible frequency signals construct the
//|     fixed outputs first.
//|
//|   :param ~microcontroller.Pin pin: The pin to output to
//|   :param int duty_cycle: The fraction of each pulse which is high. 16-bit
//|   :param int frequency: The target frequency in Hertz (32-bit)
//|   :param bool variable_frequency: True if the frequency will change over time
//|
//|   Simple LED fade::
//|
//|     import pulseio
//|     import board
//|
//|     pwm = pulseio.PWMOut(board.D13)     # output on D13
//|     pwm.duty_cycle = 2 ** 15            # Cycles the pin with 50% duty cycle (half of 2 ** 16) at the default 500hz
//|
//|   PWM at specific frequency (servos and motors)::
//|
//|     import pulseio
//|     import board
//|
//|     pwm = pulseio.PWMOut(board.D13, frequency=50)
//|     pwm.duty_cycle = 2 ** 15                  # Cycles the pin with 50% duty cycle (half of 2 ** 16) at 50hz
//|
//|   Variable frequency (usually tones)::
//|
//|     import pulseio
//|     import board
//|     import time
//|
//|     pwm = pulseio.PWMOut(board.D13, duty_cycle=2 ** 15, frequency=440, variable_frequency=True)
//|     time.sleep(0.2)
//|     pwm.frequency = 880
//|     time.sleep(0.1)
//|


m_generic_make(pulseio_pwmout) {
    extern const mp_obj_type_t pulseio_pwmout_type;
    enum { ARG_pin, ARG_duty_cycle, ARG_frequency, ARG_variable_frequency };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_pin,                MP_ARG_REQUIRED | MP_ARG_OBJ, },
        { MP_QSTR_duty_cycle,         MP_ARG_KW_ONLY  | MP_ARG_INT,  { .u_int = 0 } },
        { MP_QSTR_frequency,          MP_ARG_KW_ONLY  | MP_ARG_INT,  { .u_int = 500 } },
        { MP_QSTR_variable_frequency, MP_ARG_KW_ONLY  | MP_ARG_BOOL, { .u_bool = false } },
    };

    abstract_module_t * self = new_abstruct_module(&pulseio_pwmout_type);
    mp_arg_val_t        vals[MP_ARRAY_SIZE(allowed_args)];
    mcu_pin_obj_t *     pin;
    uint32_t            duty_cycle;
    uint32_t            frequency;
    bool                variable_frequency;
    mp_arg_parse_all_kw_array(n_args, n_kw, args, MP_ARRAY_SIZE(allowed_args), allowed_args, vals);
    assert_pin(vals[ARG_pin].u_obj, false);
    assert_pin_free(pin = m_get_pin(ARG_pin));
    duty_cycle = vals[ARG_duty_cycle].u_int;
    frequency = vals[ARG_frequency].u_int;
    variable_frequency = vals[ARG_variable_frequency].u_bool;
    common_hal_pulseio_pwmout_construct(self, pin->number, duty_cycle, frequency, variable_frequency);
    return self;
}

//|   .. attribute:: duty_cycle
//|
//|      16 bit value that dictates how much of one cycle is high (1) versus low
//|      (0). 0xffff will always be high, 0 will always be low and 0x7fff will
//|      be half high and then half low.

//|   .. attribute:: frequency
//|
//|     32 bit value that dictates the PWM frequency in Hertz (cycles per
//|     second). Only writeable when constructed with ``variable_frequency=True``.
//|
STATIC mp_obj_t pulseio_pwmout_obj_get_frequency(mp_obj_t self_in) {
    abstract_module_t * self = (abstract_module_t *)self_in;
    raise_error_if_deinited(common_hal_pulseio_pwmout_deinited(self));
    return MP_OBJ_NEW_SMALL_INT(common_hal_pulseio_pwmout_get_frequency(self));
}

STATIC mp_obj_t pulseio_pwmout_obj_set_frequency(mp_obj_t self_in, mp_obj_t frequency) {
    raise_error_if_deinited(common_hal_pulseio_pwmout_deinited((abstract_module_t *)self_in));
    return mp_const_none;
}

void pulseio_pwmout_obj_attr(mp_obj_t self_in, qstr attr, mp_obj_t * dest){
    abstract_module_t * self = (abstract_module_t *)self_in;
    raise_error_if_deinited(common_hal_pulseio_pwmout_deinited(self));

    if (dest[0] != MP_OBJ_NULL){
        dest[0] = MP_OBJ_NULL;
        if (attr == MP_QSTR_frequency){
            if (!common_hal_pulseio_pwmout_get_variable_frequency(self)) {
                raise_error_because(
                    "PWM frequency not writable when variable_frequency is False on "
                    "construction."
                );
            }
            common_hal_pulseio_pwmout_set_frequency(self, mp_obj_get_int(dest[1]));
            return;
        }
        else if (attr == MP_QSTR_duty_cycle){
            uint32_t duty = mp_obj_get_int(dest[1]);
            
            if (duty > 0xffff) {
                mp_raise_ValueError("PWM duty_cycle must be between 0 and 65535 inclusive (16 bit resolution)");
            }

            common_hal_pulseio_pwmout_set_duty_cycle(self, duty);
            return;
        }
    }
    else{
        if (attr == MP_QSTR_frequency){
            dest[0] =  MP_OBJ_NEW_SMALL_INT(common_hal_pulseio_pwmout_get_frequency(self));
            return;
        }
        else if (attr == MP_QSTR_duty_cycle){
            dest[0] = MP_OBJ_NEW_SMALL_INT(common_hal_pulseio_pwmout_get_duty_cycle(self));
            return;
        }
    }

    generic_method_lookup(self_in, attr, dest);
}

STATIC const mp_rom_map_elem_t pulseio_pwmout_locals_dict_table[] = {
    // Methods
    { MP_ROM_QSTR(MP_QSTR_deinit),     MP_ROM_PTR(&pulseio_pwmout_deinit_obj) },
    { MP_ROM_QSTR(MP_QSTR___enter__),  MP_ROM_PTR(&default___enter___obj) },
    { MP_ROM_QSTR(MP_QSTR___exit__),   MP_ROM_PTR(&pulseio_pwmout_obj___exit___obj) },
    // TODO(tannewt): Add enabled to determine whether the signal is output
    // without giving up the resources. Useful for IR output.
};
STATIC MP_DEFINE_CONST_DICT(pulseio_pwmout_locals_dict, pulseio_pwmout_locals_dict_table);

const mp_obj_type_t pulseio_pwmout_type = {
    { &mp_type_type },
    .name = MP_QSTR_PWMOut,
    .make_new = pulseio_pwmout_make_new,
    .locals_dict = (mp_obj_dict_t*)&pulseio_pwmout_locals_dict,
    .attr = &pulseio_pwmout_obj_attr,
};
