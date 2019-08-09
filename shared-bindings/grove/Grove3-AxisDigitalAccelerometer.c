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
#include "shared-bindings/util.h"
#include "shared-bindings/microcontroller/Pin.h"
#include "py/obj.h"

void common_hal_ada_construct(abstract_module_t * self);
void common_hal_ada_deinit(abstract_module_t * self);
void common_hal_ada_get_xyz(abstract_module_t * self, int8_t * values);
void common_hal_ada_get_xyz_acceleration(abstract_module_t * self, float * values);

extern const mp_obj_type_t grove_3_axis_digital_accelerometer_type;

m_generic_make(ada) {
    abstract_module_t * self = new_abstruct_module(type);
    assert_scl_sda(n_args);
    common_hal_ada_construct(self);
    return (mp_obj_t)self;
}

void ada_obj_attr(mp_obj_t self_in, qstr attr, mp_obj_t * dest){
    abstract_module_t * self = (abstract_module_t *)(self_in);
    uint32_t            index = (uint32_t)-1;
    int8_t              row_values[3];
    float               acc_values[3];
    bool                is_acceleration = false;

    if (dest[0] == MP_OBJ_NULL) {
        switch (attr) {
        case MP_QSTR_x: index = 0; break;
        case MP_QSTR_y: index = 1; break;
        case MP_QSTR_z: index = 2; break;
        case MP_QSTR_x_acceleration: index = 0; is_acceleration = true; break;
        case MP_QSTR_y_acceleration: index = 1; is_acceleration = true; break;
        case MP_QSTR_z_acceleration: index = 2; is_acceleration = true; break;
        }
    }
    if (index == -1){
        generic_method_lookup(self_in, attr, dest);
        return;
    } 
    if (is_acceleration){
        common_hal_ada_get_xyz_acceleration(self->module, acc_values);
        dest[0] = mp_obj_new_float(acc_values[index]);
    } 
    else {
        common_hal_ada_get_xyz(self->module, row_values);
        dest[0] = mp_obj_new_int(row_values[index]);
    }
}

const mp_rom_map_elem_t ada_locals_dict_table[] = {
    // instance methods
    { MP_ROM_QSTR(MP_QSTR_deinit),     MP_ROM_PTR(&ada_deinit_obj) },
    { MP_ROM_QSTR(MP_QSTR___enter__),  MP_ROM_PTR(&default___enter___obj) },
    { MP_ROM_QSTR(MP_QSTR___exit__),   MP_ROM_PTR(&ada_obj___exit___obj) },
};

MP_DEFINE_CONST_DICT(ada_locals_dict, ada_locals_dict_table);
const mp_obj_type_t grove_3_axis_digital_accelerometer_type = {
    {&mp_type_type},
    .name = MP_QSTR_grove_ada,
    .make_new = ada_make_new,
    .locals_dict = (mp_obj_t)&ada_locals_dict,
    .attr = &ada_obj_attr,
};