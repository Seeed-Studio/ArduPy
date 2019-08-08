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

#include "submodule/Grove_LED_Bar.h"
extern "C"{
#include "py/mphal.h"
#include "py/nlr.h"
#include "py/objtype.h"
#include "py/runtime.h"
#include "shared-bindings/microcontroller/Pin.h"
#include "shared-bindings/util.h"
}

#define bar (*(Grove_LED_Bar *)self)
void * operator new(size_t, void *); 

namespace {
    void * new_led_bar(
        void ** get, 
        const mcu_pin_obj_t * pin_clk, 
        const mcu_pin_obj_t * pin_dat){
        *get = new(m_new_obj(Grove_LED_Bar)) Grove_LED_Bar(
            pin_clk->number, 
            pin_dat->number, 
            0, 
            LED_BAR_10
        );
    }
}

extern "C" {
    void common_hal_led_bar_construct(
        void ** get, 
        const mcu_pin_obj_t * pin_clk, 
        const mcu_pin_obj_t * pin_dat){
        new_led_bar(get, pin_clk, pin_dat);
    }
    void common_hal_led_bar_deinit(void *self){

    }
    void common_hal_led_bar_get_led_numbers(void *self, uint32_t * value){
        Origin::LedDevice * dev = (Origin::LedDevice *)self;
        *value = dev->countOfLed();
    }
    void common_hal_led_bar_set_bits(void *self, uint32_t value){
        bar.setBits(value);
    }
    void common_hal_led_bar_get_bits(void *self, uint32_t * value){
        *value = bar.getBits();
    }
    void common_hal_led_bar_set_level(void *self, float value){
        bar.setLevel(value);
    }
    void common_hal_led_bar_set_brightness(void *self, uint32_t led_no, float value){
        bar.setLed(led_no, value);
    }
    void common_hal_led_bar_set_is_reverse_show(void *self, uint32_t value){
        bar.setGreenToRed(value != 0);
    }
    void common_hal_led_bar_toggle(void *self, uint32_t led_no){
        bar.toggleLed(led_no);
    }
}