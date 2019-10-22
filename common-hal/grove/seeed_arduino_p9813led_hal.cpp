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

#include "Arduino.h"
#define private public
#include "Seeed_Arduino_P9813LED/ChainableLED.h"

extern "C" {
    #include "shared-bindings/util.h"
    #include "py/obj.h"
}

#define led     (*(ChainableLED *)self->module)
void * operator new (size_t, void *);

extern "C" {
    void common_hal_chainable_led_construct(
        abstract_module_t * self, 
        uint32_t pin_clk, 
        uint32_t pin_dat,
        uint32_t count_of_led) {
        self->module = new (m_new_obj(ChainableLED)) 
            ChainableLED(pin_clk, pin_dat, count_of_led);
    }

    void common_hal_chainable_led_deinit(abstract_module_t * self) {
        led.~ChainableLED();
    }

    uint32_t common_hal_chainable_led_get_led_numbers(abstract_module_t * self) {
        return led._num_leds;
    }

    void common_hal_chainable_led_set_rgb(abstract_module_t * self, uint32_t led_no, uint8_t r, uint8_t g, uint8_t b){
        led.setColorRGB(led_no - 1, r, g, b);
    }

    void common_hal_chainable_led_set_hsb(abstract_module_t * self, uint32_t led_no, uint8_t h, uint8_t s, uint8_t b){
        led.setColorHSB(led_no - 1, h, s, b);
    }
}