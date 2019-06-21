/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Dan Halbert for Adafruit Industries
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

#ifndef MICROPY_INCLUDED_SHARED_BINDINGS_UTIL_H
#define MICROPY_INCLUDED_SHARED_BINDINGS_UTIL_H

#include "py/runtime.h"

#include "shared-bindings/util.h"
void normalize_buffer_bounds(int32_t* start, int32_t end, uint32_t* length) {
    if (end < 0) {
        end += *length;
    } else if (((uint32_t) end) > *length) {
        end = *length;
    }   
    if (*start < 0) {
        *start += *length;
    }   
    if (end < *start) {
        *length = 0;
    } else {
        *length = end - *start;
    }   
}     

NORETURN void mp_raise_RuntimeError(const char *msg) {
    mp_raise_msg(&mp_type_RuntimeError, msg);
}
NORETURN void mp_raise_AttributeError(const char *msg) {
    mp_raise_msg(&mp_type_AttributeError, msg);
}



// Check if pin is None. If so, deinit() has already been called on the object, so complain.
void raise_error_if_deinited(bool deinited) {
    if (deinited) {
        mp_raise_ValueError("Object has been deinitialized and can no longer be used. Create a new object.");
    }
}


STATIC mp_obj_t default___enter__(mp_obj_t self_in) {
   return self_in;
}
MP_DEFINE_CONST_FUN_OBJ_1(default___enter___obj, default___enter__);                                                                  



// *** Common functions
void generic_method_lookup(mp_obj_t obj, qstr attr, mp_obj_t *dest) {
    mp_obj_type_t *type = mp_obj_get_type(obj);
    if (type->locals_dict != NULL) {
         // generic method lookup
         // this is a lookup in the object (ie not class or type)
         assert(type->locals_dict->base.type == &mp_type_dict); // MicroPython restriction, for now
         mp_map_t *locals_map = &type->locals_dict->map;
         mp_map_elem_t *elem = mp_map_lookup(locals_map, MP_OBJ_NEW_QSTR(attr), MP_MAP_LOOKUP);
         if (elem != NULL) {
             mp_convert_member_lookup(obj, type, elem->value, dest);
         }
    }
}



#endif // MICROPY_INCLUDED_SHARED_BINDINGS_UTIL_H
