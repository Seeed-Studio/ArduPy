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

#include <Arduino.h>
#define private public
#include "submodule/rgb_lcd.h"

extern "C"{
#include "py/objtype.h"
#include "shared-bindings/util.h"
}

#define lcd     (*(rgb_lcd *)self->module)
void * operator new(size_t, void *);

extern "C"{
    void common_hal_lcd_construct(abstract_module_t * self){
        self->module = new(m_new_obj(rgb_lcd)) rgb_lcd;
        lcd.begin(16, 2); //column row
    }
    void common_hal_lcd_deinit(abstract_module_t * self){
        lcd.~rgb_lcd();
    }
    void common_hal_lcd_clear(abstract_module_t * self){
        lcd.clear();
    }
    void common_hal_lcd_set_cursor(abstract_module_t * self, uint32_t column, uint32_t row){
        lcd.setCursor(column, row);
    }
    void common_hal_lcd_print_int(abstract_module_t * self, int32_t value){
        lcd.print(value);
    }
    void common_hal_lcd_print_float(abstract_module_t * self, float value){
        lcd.print(value);
    }
    void common_hal_lcd_print_string(abstract_module_t * self, const char * value){
        lcd.print(value);
    }
    void common_hal_lcd_set_is_blink_cursor(abstract_module_t * self, bool value){
        value ? lcd.blink() : lcd.noBlink();
    }
    bool common_hal_lcd_get_is_blink_cursor(abstract_module_t * self){
        return (lcd._displaycontrol & LCD_BLINKON) != 0;
    }
}