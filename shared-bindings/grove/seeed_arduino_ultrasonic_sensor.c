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

#include "py/mphal.h"
#include "py/nlr.h"
#include "py/objtype.h"
#include "py/runtime.h"
#include "py/obj.h"
#include "shared-bindings/microcontroller/Pin.h"
#include "shared-bindings/util.h"

void common_hal_ultra_ranger_construct(abstract_module_t * self, const mcu_pin_obj_t * pin_ctrl);
void common_hal_ultra_ranger_deinit(abstract_module_t * self);
uint32_t common_hal_ultra_ranger_centimeters(abstract_module_t * self);
uint32_t common_hal_ultra_ranger_inches(abstract_module_t * self);

extern const mp_obj_type_t grove_ultra_ranger_type;

m_generic_make(ultra_ranger) {
    abstract_module_t * self = new_abstruct_module(type);
    mcu_pin_obj_t     * pin = (mcu_pin_obj_t *)args[0];
    assert_pin_free(pin);
    common_hal_ultra_ranger_construct(self, pin->number);
    return self;
}

void ultra_ranger_obj_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest){
    abstract_module_t * self = (abstract_module_t *)self_in;
    uint32_t value;

    if (dest[0] == MP_OBJ_NULL){
        if (attr == MP_QSTR_cm) {
            value = common_hal_ultra_ranger_centimeters(self);
            return;
        }
        else if (attr == MP_QSTR_inch){
            value = common_hal_ultra_ranger_inches(self);
            return;
        }
    }
    generic_method_lookup(self_in, attr, dest);
}

const mp_rom_map_elem_t ultra_ranger_locals_dict_table[] = {
    // instance methods
    { MP_ROM_QSTR(MP_QSTR_deinit),    MP_ROM_PTR(&ultra_ranger_deinit_obj) },
    { MP_ROM_QSTR(MP_QSTR___enter__), MP_ROM_PTR(&default___enter___obj) },
    { MP_ROM_QSTR(MP_QSTR___exit__),  MP_ROM_PTR(&ultra_ranger_obj___exit___obj) },
};

MP_DEFINE_CONST_DICT(ultra_ranger_locals_dict, ultra_ranger_locals_dict_table);

const mp_obj_type_t grove_ultra_ranger_type = {
    {&mp_type_type},
    .name = MP_QSTR_grove_ultra_ranger,
    .make_new = ultra_ranger_make_new,
    .locals_dict = (mp_obj_t)&ultra_ranger_locals_dict,
    .attr = &ultra_ranger_obj_attr,
};
