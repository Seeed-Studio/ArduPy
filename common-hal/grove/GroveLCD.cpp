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

#include <Arduino.h>
#include "submodule/rgb_lcd.h"

extern "C"{
#include "py/mphal.h"
#include "py/nlr.h"
#include "py/objtype.h"
#include "py/runtime.h"
#include "shared-bindings/microcontroller/Pin.h"
#include "shared-bindings/util.h"
}

#define lcd     (*(rgb_lcd *)self)
void * operator new(size_t, void *);

extern "C"{
    void common_hal_lcd_construct(void ** get){
        rgb_lcd * self;
        *get = self = new(m_new_obj(rgb_lcd)) rgb_lcd();
        lcd.begin(16, 2); //column row
    }
    void common_hal_lcd_deinit(void * self){

    }
    void common_hal_lcd_clear(void * self){
        lcd.clear();
    }
    void common_hal_lcd_set_cursor(void * self, uint32_t column, uint32_t row){
        lcd.setCursor(column, row);
    }
    void common_hal_lcd_print_int(void * self, int32_t value){
        lcd.print(value);
    }
    void common_hal_lcd_print_float(void * self, float value){
        lcd.print(value);
    }
    void common_hal_lcd_print_string(void * self, const char * value){
        lcd.print(value);
    }
    void common_hal_lcd_show_cursor(void * self, uint32_t value){
        value ? lcd.blink() : lcd.noBlink();
    }
}