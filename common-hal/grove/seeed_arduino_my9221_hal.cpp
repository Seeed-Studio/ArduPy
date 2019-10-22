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

#include "Seeed_Arduino_MY9221/Grove_LED_Bar.h"
extern "C"{
#include "py/objtype.h"
#include "shared-bindings/util.h"
}

#define bar (*(Grove_LED_Bar *)self->module)
void * operator new(size_t, void *); 

extern "C" {
    void common_hal_led_bar_construct(
        abstract_module_t * self, 
        uint32_t pin_clk, 
        uint32_t pin_dat){
        self->module = new(m_new_obj(Grove_LED_Bar)) Grove_LED_Bar(
            pin_clk,
            pin_dat,
            0,
            LED_BAR_10
        );
    }
    void common_hal_led_bar_deinit(abstract_module_t * self){
        bar.~Grove_LED_Bar();
    }
    void common_hal_led_bar_set_bits(abstract_module_t * self, uint32_t value){
        bar.setBits(value);
    }
    void common_hal_led_bar_set_level(abstract_module_t * self, float value){
        bar.setLevel(value);
    }
    void common_hal_led_bar_set_brightness(abstract_module_t * self, uint32_t led_no, float value){
        bar.setLed(led_no, value);
    }
    void common_hal_led_bar_set_is_reverse_show(abstract_module_t * self, bool value){
        bar.setGreenToRed(value);
    }
    void common_hal_led_bar_toggle(abstract_module_t * self, uint32_t led_no){
        bar.toggleLed(led_no);
    }
    uint32_t common_hal_led_bar_get_led_numbers(abstract_module_t * self){
        Origin::LedDevice * dev = (Origin::LedDevice *)self;
        return dev->countOfLed();
    }
    uint32_t common_hal_led_bar_get_bits(abstract_module_t * self){
        return bar.getBits();
    }
}