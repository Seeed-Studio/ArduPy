/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Scott Shawcroft for Adafruit Industries
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
#include <Arduino.h>
extern "C"{
#include "shared-bindings/util.h"
}

#define pwm   (*(pulseio_pwmout_data_t *)self->module)

typedef struct{
    uint8_t     pin;
    bool        variable_frequency;
    uint16_t    duty;
    uint32_t    frequency;
}pulseio_pwmout_data_t;

extern "C"{
    void common_hal_pulseio_pwmout_never_reset(abstract_module_t * self) {
        
    }

    void common_hal_pulseio_pwmout_reset_ok(abstract_module_t * self) {
        
    }

    void common_hal_pulseio_pwmout_construct(
        abstract_module_t * self,
        uint32_t pin,
        uint32_t duty,
        uint32_t frequency,
        bool variable_frequency) {
        self->module = m_new_obj(pulseio_pwmout_data_t);
        pwm.pin = pin;
        pwm.duty = duty;
        pwm.frequency = frequency;
        pwm.variable_frequency = variable_frequency;
    }

    bool common_hal_pulseio_pwmout_deinited(abstract_module_t * self) {
        return false;
    }

    void common_hal_pulseio_pwmout_deinit(abstract_module_t * self) {
        
    }
    void common_hal_pulseio_pwmout_set(abstract_module_t * self, uint32_t duty){
        uint32_t arduino_duty = duty >> 8; //arduino duty range is 0~255
        tone(pwm.pin, pwm.frequency, arduino_duty);
    }
    void common_hal_pulseio_pwmout_set_duty_cycle(abstract_module_t * self, uint32_t duty) {
        pwm.duty = duty;
        common_hal_pulseio_pwmout_set(self, duty);
    }

    void common_hal_pulseio_pwmout_set_frequency(abstract_module_t * self, uint32_t frequency) {
        pwm.frequency = frequency;
        common_hal_pulseio_pwmout_set(self, pwm.duty);
    }

    bool common_hal_pulseio_pwmout_get_variable_frequency(abstract_module_t * self) {
        return pwm.variable_frequency;
    }

    uint32_t common_hal_pulseio_pwmout_get_duty_cycle(abstract_module_t * self) {
        return pwm.duty;
    }

    uint32_t common_hal_pulseio_pwmout_get_frequency(abstract_module_t * self) {
        return pwm.frequency;
    }

}
