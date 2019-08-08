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
#include "py/obj.h"

typedef struct{
    mp_obj_base_t base;
    void *        module;
}ada_obj_t;

void common_hal_ada_construct(void ** get);
void common_hal_ada_deinit(void * self);
void common_hal_ada_get_xyz(void * self, int8_t * values);
void common_hal_ada_get_xyz_acceleration(void * self, float * values);

extern const mp_obj_type_t grove_3_axis_digital_accelerometer_type;

mp_obj_t ada_make_new(
    const mp_obj_type_t *type, 
    size_t n_args, 
    size_t n_kw, 
    const mp_obj_t * args) {
    ada_obj_t * self = m_new_obj(ada_obj_t);
    self->base.type = &grove_3_axis_digital_accelerometer_type;
    common_hal_ada_construct(&self->module);
    return (mp_obj_t)self;
}

mp_obj_t ada_obj_deinit(mp_obj_t self_in) {
    ada_obj_t *self = (ada_obj_t *)(self_in);
    common_hal_ada_deinit(self);
    return mp_const_none;
}

mp_obj_t ada_obj___exit__(size_t n_args, const mp_obj_t *args) {
    ada_obj_t *self = (ada_obj_t *)(args[0]);
    common_hal_ada_deinit(self);
    return mp_const_none;
}

mp_obj_t ada_get_x(mp_obj_t self_in){
    ada_obj_t *self = (ada_obj_t *)(self_in);
    int8_t value[3];
    common_hal_ada_get_xyz(self, value);
    return mp_obj_new_int(value[0]);
}
mp_obj_t ada_get_y(mp_obj_t self_in){
    ada_obj_t *self = (ada_obj_t *)(self_in);
    int8_t value[3];
    common_hal_ada_get_xyz(self, value);
    return mp_obj_new_int(value[1]);
}
mp_obj_t ada_get_z(mp_obj_t self_in){
    ada_obj_t *self = (ada_obj_t *)(self_in);
    int8_t value[3];
    common_hal_ada_get_xyz(self, value);
    return mp_obj_new_int(value[2]);
}
mp_obj_t ada_get_x_acceleration(mp_obj_t self_in){
    ada_obj_t *self = (ada_obj_t *)(self_in);
    float value[3];
    common_hal_ada_get_xyz_acceleration(self, value);
    return mp_obj_new_float(value[0]);
}
mp_obj_t ada_get_y_acceleration(mp_obj_t self_in){
    ada_obj_t *self = (ada_obj_t *)(self_in);
    float value[3];
    common_hal_ada_get_xyz_acceleration(self, value);
    return mp_obj_new_float(value[1]);
}
mp_obj_t ada_get_z_acceleration(mp_obj_t self_in){
    ada_obj_t *self = (ada_obj_t *)(self_in);
    float value[3];
    common_hal_ada_get_xyz_acceleration(self, value);
    return mp_obj_new_float(value[2]);
}

void ada_obj_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest){
    if (dest[0] != MP_OBJ_NULL) {
        generic_method_lookup(self_in, attr, dest);
    } else {
        switch (attr) {
        case MP_QSTR_x: dest[0] = ada_get_x(self_in); break;
        case MP_QSTR_y: dest[0] = ada_get_y(self_in); break;
        case MP_QSTR_z: dest[0] = ada_get_z(self_in); break;
        case MP_QSTR_x_acceleration: dest[0] = ada_get_x_acceleration(self_in); break;
        case MP_QSTR_y_acceleration: dest[0] = ada_get_y_acceleration(self_in); break;
        case MP_QSTR_z_acceleration: dest[0] = ada_get_z_acceleration(self_in); break;
        default:
            generic_method_lookup(self_in, attr, dest);
            break;
        }
    }
}

MP_DEFINE_CONST_FUN_OBJ_1(ada_deinit_obj, ada_obj_deinit);
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ada_obj___exit___obj, 4, 4, ada_obj___exit__);

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