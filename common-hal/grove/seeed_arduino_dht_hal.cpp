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

#include "Seeed_Arduino_DHT/DHT.h"
extern "C"{
#include "py/mphal.h"
#include "py/nlr.h"
#include "py/objtype.h"
#include "py/runtime.h"
#include "shared-bindings/microcontroller/Pin.h"
#include "shared-bindings/util.h"
}

#define dht     (*(DHT *)self->module)
void * operator new(size_t, void *); 
extern const mp_obj_base_t ic_dht11_obj;
extern const mp_obj_base_t ic_dht21_obj;
extern const mp_obj_base_t ic_dht22_obj;

extern "C" {
    void common_hal_dht_construct(
        abstract_module_t * self, 
        uint32_t pin_ctrl,
        mp_obj_t type){
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

        self->module = new(m_new_obj(DHT)) DHT(pin_ctrl, device);
        dht.begin();
    }
    void common_hal_dht_deinit(abstract_module_t * self){
        dht.~DHT();
    }
    float common_hal_dht_get_humidity(abstract_module_t * self){
        return dht.readHumidity();
    }
    float common_hal_dht_get_temperature(abstract_module_t * self){
        return dht.readTemperature();
    }
}
