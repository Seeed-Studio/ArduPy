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

#include "Seeed_Arduino_TM1637/TM1637.h"
extern "C"{
#include "py/objtype.h"
#include "shared-bindings/util.h"
}

#define tube     (*(TM1637 *)self->module)
void * operator new(size_t, void *); 

extern "C" {
    void common_hal_nixie_tube_construct(
        abstract_module_t * self,
        uint32_t pin_clk, 
        uint32_t pin_dat){
        self->module = new(m_new_obj(TM1637)) TM1637(pin_clk, pin_dat);
        tube.clearDisplay();
        tube.set();
    }
    void common_hal_nixie_tube_deinit(abstract_module_t * self){
        tube.~TM1637();
    }
    void common_hal_nixie_tube_clear(abstract_module_t * self){
        tube.clearDisplay();
    }
    void common_hal_nixie_tube_display(abstract_module_t * self, uint32_t value){
        int8_t values [4];
        values[0] = value / 1000;
        value %= 1000;
        values[1] = value / 100;
        value %= 100;
        values[2] = value / 10;
        value %= 10;
        values[3] = value;
        tube.display(values);
    }
    void common_hal_nixie_tube_set_show_colon(abstract_module_t * self, bool confirm){
        tube.point(confirm ? POINT_ON : POINT_OFF);
    }
    bool common_hal_nixie_tube_get_show_colon(abstract_module_t * self){
        return tube._PointFlag;
    }
}