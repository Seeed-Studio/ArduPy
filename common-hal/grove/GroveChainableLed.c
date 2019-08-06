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

#include "Arduino.h"
#include "GroveChainableLed.h"

void common_hal_chainable_led_construct(
    chainable_led_obj_t *self, 
    const mcu_pin_obj_t *pin_clk, 
    const mcu_pin_obj_t *pin_data) {
    claim_pin(pin_clk);
    claim_pin(pin_data);
    self->pin_clk = pin_clk;
    self->pin_data = pin_data;
    pinMode(pin_clk->number, OUTPUT);
    pinMode(pin_data->number, OUTPUT);
}

void common_hal_chainable_led_deinit(chainable_led_obj_t *self) {
    if (self->pin_clk != mp_const_none) {
        reset_pin_number(self->pin_clk->number);
        self->pin_clk = mp_const_none;
    }
    if (self->pin_data != mp_const_none) {
        reset_pin_number(self->pin_data->number);
        self->pin_clk = mp_const_none;
    }
}

void common_hal_chainable_led_set_clock_value(chainable_led_obj_t *self, bool value) { 
    digitalWrite(self->pin_clk->number, value);
}

void common_hal_chainable_led_set_data_value(chainable_led_obj_t *self, bool value) { 
    digitalWrite(self->pin_data->number, value);
}

void common_hal_chainable_led_send_byte(chainable_led_obj_t *self, uint8_t bits){
    const uint32_t pause = 20;
    for (size_t i = 0; i < 8; i++, bits <<= 1) {
        common_hal_chainable_led_set_data_value(self, (bits & 0x80) != 0);
        common_hal_chainable_led_set_clock_value(self, LOW);
        delayMicroseconds(pause); 
        common_hal_chainable_led_set_clock_value(self, HIGH);
        delayMicroseconds(pause); 
    }
}

void common_hal_chainable_led_set_rgb(chainable_led_obj_t *self, uint32_t index, chainable_led_rgb_t value){
    self->led[index] = value;

    //dummy 32bit
    for (size_t i = 0; i < 4; i++) {
        common_hal_chainable_led_send_byte(self, 0x00);
    }

    //send grb color for led chain
    for (size_t i = 0; i < self->number_of_leds; i++) {
        value = self->led[i];
        uint8_t token = 0xc0 | (value.r >> 6) | ((value.g >> 6) << 2) | ((value.b >> 6) << 4);
        common_hal_chainable_led_send_byte(self, token);
        common_hal_chainable_led_send_byte(self, value.b);
        common_hal_chainable_led_send_byte(self, value.g);
        common_hal_chainable_led_send_byte(self, value.r);
    }

    //dummy 32bit
    for (size_t i = 0; i < 4; i++) {
        common_hal_chainable_led_send_byte(self, 0x00);
    }
}

float hue2rgb(uint32_t p, float q, float t) {
    if (t < 0.0)  t += 1.0;
    if (t > 1.0)  t -= 1.0;
    if (t < 1.0 / 6.0) 
        return p + (q - p) * 6.0 * t;
    if (t < 1.0 / 2.0) 
        return q;
    if (t < 2.0 / 3.0) 
        return p + (q - p) * (2.0 / 3.0 - t) * 6.0;
    return p;
}

void common_hal_chainable_led_set_hsb(chainable_led_obj_t *self, uint32_t index, chainable_led_hsb_t value){
    chainable_led_rgb_t rgb;
    float r, g, b;
    constrain(value.h, 0.0, 1.0);
    constrain(value.s, 0.0, 1.0);
    constrain(value.b, 0.0, 1.0);

    if (value.s == 0.0) {
        r = g = b = value.b;
    } else {
        float q = value.b < 0.5 ? 
            value.b * (1.0 + value.s) : 
            value.b + value.s - value.b * value.s;
        float p = 2.0 * value.b - q;
        r = hue2rgb(p, q, value.h + 1.0/3.0);
        g = hue2rgb(p, q, value.h);
        b = hue2rgb(p, q, value.h - 1.0/3.0);
    }

    rgb.r = (uint8_t)(r * 255);
    rgb.g = (uint8_t)(g * 255);
    rgb.b = (uint8_t)(b * 255);
    common_hal_chainable_led_set_rgb(self, index, rgb);
}
