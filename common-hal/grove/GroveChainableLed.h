/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Scott Shawcroft for Adafruit Industries
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

#ifndef MICROPY_INCLUDED_ATMEL_SAMD_COMMON_HAL_GROVE_CHAINABLE_LED_H
#define MICROPY_INCLUDED_ATMEL_SAMD_COMMON_HAL_GROVE_CHAINABLE_LED_H

#include "common-hal/microcontroller/Pin.h"
#include "py/obj.h"

extern const mp_obj_type_t chainable_led_type;

typedef struct{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} chainable_led_rgb_t;

typedef struct{
    float h;
    float s;
    float b;
} chainable_led_hsb_t;

typedef struct{
    mp_obj_base_t base;
    const mcu_pin_obj_t * pin_clk;
    const mcu_pin_obj_t * pin_data;
    uint32_t number_of_leds;
    chainable_led_rgb_t * led;
} chainable_led_obj_t;

void common_hal_chainable_led_construct(
    chainable_led_obj_t *self, 
    const mcu_pin_obj_t *pin_clk, 
    const mcu_pin_obj_t *pin_data);
void common_hal_chainable_led_deinit(chainable_led_obj_t *self);
void common_hal_chainable_led_set_rgb(chainable_led_obj_t *self, uint32_t index, chainable_led_rgb_t value);
void common_hal_chainable_led_set_hsb(chainable_led_obj_t *self, uint32_t index, chainable_led_hsb_t value);
#endif