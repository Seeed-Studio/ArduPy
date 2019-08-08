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

#include "submodule/DHT.h"
extern "C"{
#include "py/mphal.h"
#include "py/nlr.h"
#include "py/objtype.h"
#include "py/runtime.h"
#include "shared-bindings/microcontroller/Pin.h"
#include "shared-bindings/util.h"
}

#define dht     (*(DHT *)self)
void * operator new(size_t, void *); 
extern const mp_obj_base_t ic_dht11_obj;
extern const mp_obj_base_t ic_dht21_obj;
extern const mp_obj_base_t ic_dht22_obj;

extern "C" {
    void common_hal_dht_construct(
        void ** get, 
        const mcu_pin_obj_t * pin_ctrl,
        mp_obj_t type){
        DHT * self;
        uint8_t device;

        if (MP_OBJ_TO_PTR(type) == MP_ROM_PTR(&ic_dht11_obj)) {
            device = DHT11;
        } 
        else if (MP_OBJ_TO_PTR(type) == MP_ROM_PTR(&ic_dht21_obj)){
            device = DHT21;
        }
        else{
            device = DHT22;
        }

        *get = self = new(m_new_obj(DHT)) DHT(
            pin_ctrl->number, device
        );

        dht.begin();
    }
    void common_hal_dht_deinit(void *self){

    }
    void common_hal_dht_get_humidity(void *self, float * value){
        *value = dht.readHumidity();
    }
    void common_hal_dht_get_temperature(void *self, float * value){
        *value = dht.readTemperature();
    }
}
