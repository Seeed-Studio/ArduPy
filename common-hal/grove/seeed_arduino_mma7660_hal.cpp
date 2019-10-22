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
#include "Seeed_Arduino_MMA7660/MMA7660.h"
extern "C"{
#include "py/objtype.h"
#include "shared-bindings/util.h"
}
#define xyz3   (*(MMA7660 *)self->module)
void * operator new(size_t, void *); 

extern "C" {
    void common_hal_ada_construct(abstract_module_t * self){
        self->module = new(m_new_obj(MMA7660)) MMA7660;
        xyz3.init();
    }
    void common_hal_ada_deinit(abstract_module_t * self){
        xyz3.~MMA7660();
    }
    void common_hal_ada_get_xyz(abstract_module_t * self, int8_t * value){
        xyz3.getXYZ(value + 0, value + 1, value + 2);
    }
    void common_hal_ada_get_xyz_acceleration(abstract_module_t * self, float * value){
        xyz3.getAcceleration(value + 0, value + 1, value + 2);
    }
}
