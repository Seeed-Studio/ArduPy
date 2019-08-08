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

#include "submodule/Adafruit_NeoPixel.h"
extern "C"{
#include "py/mphal.h"
#include "py/nlr.h"
#include "py/objtype.h"
#include "py/runtime.h"
#include "shared-bindings/microcontroller/Pin.h"
#include "shared-bindings/util.h"
}

#define rgb_led_strip   (*(Adafruit_NeoPixel *)self)
void * operator new(size_t, void *); 

extern "C" {
    void common_hal_rgb_led_strip_construct(
        void ** get, 
        const mcu_pin_obj_t * pin_ctrl,
        uint32_t count_of_led){
        Adafruit_NeoPixel * self;
        *get = self = new(m_new_obj(Adafruit_NeoPixel)) Adafruit_NeoPixel(
            count_of_led,
            pin_ctrl->number,
            NEO_GRB + NEO_KHZ800 //notice current environment-------------------------------
        );
        rgb_led_strip.begin();
        rgb_led_strip.clear();
    }
    void common_hal_rgb_led_strip_deinit(void * self){
        rgb_led_strip.~Adafruit_NeoPixel();
    }
    void common_hal_rgb_led_strip_clear(void * self){
        rgb_led_strip.clear();
    }
    void common_hal_rgb_led_strip_update(void * self){
        rgb_led_strip.show();
    }
    void common_hal_rgb_led_strip_set_pix_color(void * self, uint32_t led_no, uint32_t color){
        rgb_led_strip.setPixelColor(led_no - 1, 
            (color >> 16) & 0xff, 
            (color >>  8) & 0xff,
            (color >>  0) & 0xff
        );
    }
    void common_hal_rgb_led_strip_set_brightness(void * self, uint32_t value){
        rgb_led_strip.setBrightness(value);
    }
}